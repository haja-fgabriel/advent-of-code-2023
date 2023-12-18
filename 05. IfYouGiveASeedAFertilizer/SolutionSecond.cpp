#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <utility>
#include <functional>
#include <chrono>
#include <iomanip>
#include <map>
#include <set>
#include <string>
#include <algorithm>
#include <exception>

#include "SolutionSecond.h"

using namespace std;

seed_t SolutionSecond::solve() {
    set<SeedInterval> initial = seedIntervals;

    for (int i = 0; i < 7; i++) {
        set<SeedInterval> mapped;
        set<SeedInterval> merged;
        SeedMap firstMap = *seedMap[i].begin();
        SeedMap lastMap = *prev(seedMap[i].end());
        seed_t mapFirst = firstMap.source;
        seed_t  mapLast = lastMap.source + lastMap.length - 1;
        int index = 0;

        for (const SeedInterval& seeds: initial) {
            index++;
            seed_t intervalFirst = seeds.first;
            seed_t intervalLast = seeds.first + seeds.second - 1;

            seed_t previousLast = -1;
            
            if (intervalLast < mapFirst || intervalFirst > mapLast) {
                mapped.insert(seeds);
                continue;
            }

            for (const SeedMap& currentMap: seedMap[i]) {
                seed_t first = currentMap.source;
                seed_t last = currentMap.source + currentMap.length - 1;
                if (last < intervalFirst) {
                    continue;
                }

                if (intervalFirst < first) {
                    previousLast = intervalFirst;
                }

                first = max(first, intervalFirst);

                if (previousLast != -1 && previousLast < first) {
                    mapped.insert({previousLast, first - previousLast});
                }

                const seed_t end = min(last, intervalLast);
                mapped.insert({first - currentMap.source + currentMap.target, end - first + 1});

                if (intervalLast <= last) {
                    break;
                }

                previousLast = last + 1;
            }
            if (intervalLast > mapLast) {
                mapped.insert({mapLast + 1, intervalLast - mapLast});
            }
        }
        
        auto it = mapped.begin();
        seed_t first = it->first;
        seed_t last = first + it->second - 1;
        int zeroCount = 0;
        for (it = next(it); it != mapped.end(); it++) {
            if (it->first > last) {
                if (first != -1) {
                    merged.insert({first, last - first});
                }
                first = it->first;
            }
            last = it->first + it->second;
        }
        if (first != -1) {
            merged.insert({first, last - first});
        }
        initial = merged;
    }

    return initial.begin()->first;
}

std::istream& operator>>(std::istream& input, SolutionSecond* solution) {
    std::stringstream ss;
    std::string row, seedsWord;

    std::getline(input, row);
    ss.str(row);
    
    seed_t seedNumber, seedLength;
    ss >> seedsWord;
    while (ss >> seedNumber >> seedLength) {
        solution->seedIntervals.insert({seedNumber, seedLength});
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