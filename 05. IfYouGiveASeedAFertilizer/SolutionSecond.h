#pragma once

#include <utility>
#include <vector>
#include <set>

#include "ISolution.h"

typedef std::pair<seed_t, seed_t> SeedInterval;

struct SolutionSecond : public ISolution {
    std::set<SeedInterval> seedIntervals;
    std::set<SeedMap> seedMap[7];
    seed_t solve() override;
};

std::istream& operator>>(std::istream& input, SolutionSecond* solution);