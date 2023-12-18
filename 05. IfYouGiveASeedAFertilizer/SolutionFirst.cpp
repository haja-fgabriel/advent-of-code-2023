#include "SolutionFirst.h"

using namespace std;

seed_t SolutionFirst::solve() {
    std::vector<seed_t> mapped = seeds;
    const int n = mapped.size();

    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < n; j++) { 
            const seed_t currentSeed = mapped[j];
            std::set<SeedMap>::iterator it = std::find_if(seedMap[i].begin(), seedMap[i].end(), [&](const SeedMap& current) {
                return (current.source <= currentSeed && currentSeed < current.source + current.length);
            });
            if (it != seedMap[i].end()) {
                mapped[j] = it->target - it->source + currentSeed; 
            }
        }
    }

    seed_t result = mapped.front();
    for (auto& lastSeed: mapped) {
        result = std::min(result, lastSeed);
    }
    return result;
}

std::istream& operator>>(std::istream& input, SolutionFirst* solution) {
    std::stringstream ss;
    std::string row, seedsWord;

    std::getline(input, row);
    ss.str(row);
    
    seed_t seedNumber;
    ss >> seedsWord;
    while (ss >> seedNumber) {
        solution->seeds.push_back(seedNumber);
    }

    std::getline(input, row);
    for (int i = 0; i < 7; i++) {
        seed_t source, target, length;
        std::getline(input, row);
        std::getline(input, row);
        do {
            ss.clear();
            ss.str(row);
            ss >> target >> source >> length;
            solution->seedMap[i].insert({target, source, length});
            std::getline(input, row);
        } while (input && row.size());
    }

    return input;
}