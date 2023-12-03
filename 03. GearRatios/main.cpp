#include <iostream>
#include <fstream>
#include <cstring>
#include <set>

using namespace std;

// Rename to "input.txt" for full input
ifstream f("input_small.txt");

char rows[3][150];
int stars[3][150];
int prod[3][150];

int di[] = {-1, -1, 0, 1, 1,  1,  0, -1};
int dj[] = { 0,  1, 1, 1, 0, -1, -1, -1};

int i = 0, j = 0, jj = 0, k;
int m;
int sum1 = 0;
int sum2 = 0;

void checkRow(int j, int n=-1) {
    int currentNum = 0;
    int hasSymbols = 0;
    set< pair<int, int> > starPositions;
    for (int k = 0; k < m; k++) {
        if (isdigit(rows[j%3][k])) {
            currentNum = currentNum * 10 + rows[j%3][k] - '0';
            
            for (int dir = 0; dir < 8; dir++) {
                int ii = j + di[dir];
                int jj = k + dj[dir];
                if (ii >= 0 && jj >= 0 && jj < m && (n < 0 || ii < n)) {
                    if (strchr("*=/%&-#+@$", rows[ii%3][jj])) {
                        hasSymbols = 1;
                    }
                    if (rows[ii%3][jj] == '*') {
                        starPositions.insert(make_pair(ii, jj));
                    }
                }
            }

        } else {
            if (hasSymbols) {
                sum1 += currentNum;
            }
            for (auto& pos: starPositions) {
                stars[pos.first%3][pos.second]++;
                prod[pos.first%3][pos.second] *= currentNum;
            }
            hasSymbols = 0;
            currentNum = 0;
            starPositions.clear();
        }
    }
    if (hasSymbols) {
        sum1 += currentNum;
    }
    for (auto& pos: starPositions) {
        stars[pos.first%3][pos.second]++;
        prod[pos.first%3][pos.second] *= currentNum;
    }
}

void addStars(int j) {
    for (int k = 0; k < m; k++) {
        if (stars[j%3][k] == 2) {
            sum2 += prod[j%3][k];
        }
    }
}

int main() {
    // Hack that reads and processes only three lines at once
    for (; f.getline(rows[i % 3], 150); i++) {
        if (i == 0) {
            m = strlen(rows[0]);
            cout << "Length of row: " << m << endl;
        }

        // We prepare the stars to be counted used in multiplication
        for (int k = 0; k < m; k++) {
            if (rows[i%3][k] == '*') {
                stars[i%3][k] = 0;
                prod[i%3][k] = 1;
            } else {
                stars[i%3][k] = -1;
                prod[i%3][k] = 0;
            }
        }

        // We will assume that we will have all neighbors for the first two
        // rows only when the first three rows have been read
        if (i >= 2) {
            for (; j < i; j++) {
                checkRow(j);
            }
            // We will need the last row to be accessed too (3rd row in the first run of the if)
            // statement; only first row will contain the full result at first
            for (; jj < i - 1; jj++) {
                addStars(jj);
            }
        }
    }

    // Process the remainder
    checkRow(i-1, i);
    addStars(i-2);
    addStars(i-1);
    
    cout << "Part 1: " << sum1 << endl;
    cout << "Part 2: " << sum2 << endl;
    return 0;
}