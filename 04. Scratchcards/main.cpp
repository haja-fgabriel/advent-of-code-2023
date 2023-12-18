// Compile with `g++ --std=c++17 -O2 -Wall main.cpp`
// Run with `a.exe` (on Windows) or `./a.out` (on UNIX systems)
// Deliberately made to be complicated and to use modern C++

#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cstring>
#include <cstddef>
#include <numeric>
#include <optional>
#include <ctime>
#include <iomanip>
#include <chrono>


class Card {
public:
    static Card fromRow(std::string& row) {
        std::stringstream rowStream;
        std::string number, cardWord;
        std::vector<int> luckyNumbers;
        char colon;
        int cardId;

        rowStream.str(row);
        
        rowStream >> cardWord >> cardId >> colon;
        rowStream >> number;

        while (number != "|") {
            luckyNumbers.push_back(std::atoi(number.c_str()));
            rowStream >> number;
        }

        std::vector<int> numbers;
        while (rowStream >> number) {
            numbers.push_back(std::atoi(number.c_str()));
        }
        
        return Card(numbers, luckyNumbers);
    }

    int getScore() {
        if (memoScore.has_value()) {
            return memoScore.value();
        }
        int result = 0;
        int count = 0;
        std::unordered_map<int, int> frequencies = luckyMap;
        for (auto& number: numbers) {
            if (frequencies[number] > 0) {
                count ++;
                if (result == 0) {
                    result = 1;
                } else {
                    result <<= 1;
                }
                frequencies[number] --;
            }
        }
        memoScore.emplace(result);
        luckyCount.emplace(count);
        return result;
    }

    int getLuckyCount() {
        if (luckyCount.has_value()) {
            return luckyCount.value();
        }

        int count = 0;
        std::unordered_map<int, int> frequencies = luckyMap;
        for (auto& number: numbers) {
            if (frequencies[number] > 0) {
                count ++;
                frequencies[number] --;
            }
        }
        luckyCount.emplace(count);
        return count;
    }

    Card() {}
    
private:
    std::unordered_map<int, int> luckyMap;
    std::vector<int> numbers;
    std::vector<int> luckyNumbers;
    std::optional<int> memoScore;
    std::optional<int> luckyCount;

    Card(std::vector<int>& numbers, std::vector<int>& luckyNumbers) {
        this->numbers = std::move(numbers);
        for (auto& lucky: luckyNumbers) {
            luckyMap[lucky] ++;
        }
        this->luckyNumbers = std::move(luckyNumbers);
    }
};


std::istream& operator>>(std::istream& inputFile, Card& c) {
    std::string row;
    std::istream& stream = std::getline(inputFile, row);
    if (stream) {
        c = Card::fromRow(row);
    }
    return stream;
}


using CardList = std::vector<Card>;


struct Solution {
    CardList cards;
    std::vector<int> scores;

    int solveFirst() {
        return std::accumulate(scores.begin(), scores.end(), 0);
    }

    int solveSecond() {
        std::vector<int> copies(scores.size(), 1);
        const int n = copies.size();
        int result = 0;

        for (int i = 0; i < n; i++) {
            const int m = cards[i].getLuckyCount();
            for (int j = i + 1; j <= i + m && j < n; j++) {
                copies[j] += copies[i];
            }
            result += copies[i];
        }
        return result;
    }
};

std::istream& operator>>(std::istream& f, Solution& s) {
    Card card;
    while (f >> card) {
        s.cards.push_back(card);
        s.scores.push_back(card.getScore());
    }
    return f;
}

int main() {

    using namespace std::literals::chrono_literals;

    const std::chrono::time_point<std::chrono::steady_clock> timeBegin = std::chrono::steady_clock::now(); 
    std::ifstream f("input.txt");
    Solution s;

    f >> s;
    std::cout << "Part 1: " << s.solveFirst() << std::endl;
    std::cout << "Part 2: " << s.solveSecond() << std::endl;
    
    const std::chrono::time_point<std::chrono::steady_clock> timeEnd = std::chrono::steady_clock::now(); 
    std::cout << "Time elapsed: " << std::fixed << std::setprecision(7) 
        << 1.0 * std::chrono::duration_cast<std::chrono::microseconds>(timeEnd - timeBegin).count() / 1000000 << std::endl;
        
    return 0;
}