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
        int result = 0;
        std::unordered_map<int, int> frequencies = luckyMap;
        for (auto& number: numbers) {
            if (frequencies[number] > 0) {
                if (result == 0) {
                    result = 1;
                } else {
                    result <<= 1;
                }
                frequencies[number] --;
            }
        }
        return result;
    }

    Card() {}
    

private:
    std::unordered_map<int, int> luckyMap;
    std::vector<int> numbers;
    std::vector<int> luckyNumbers;

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


class Solution {
private:
    std::ifstream inputFile;

public:
    Solution(const std::string& filename): inputFile(filename) {}

    ~Solution() {}

    int solve() {
        Card card;
        CardList cards;

        while (inputFile >> card) {
            cards.push_back(card);
        }

        return std::accumulate(cards.begin(), cards.end(), 0, [](int x, Card& c) {
            return x + c.getScore();
        });
    }

};

int main() {
    Solution s("input.txt");
    std::cout << "Part 1: " << s.solve() << std::endl;
    return 0;
}