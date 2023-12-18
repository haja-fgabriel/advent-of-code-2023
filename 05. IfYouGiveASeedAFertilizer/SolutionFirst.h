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

#include "ISolution.h"


struct SolutionFirst : public ISolution {
    std::vector<seed_t> seeds;
    std::set<SeedMap> seedMap[7];
    seed_t solve() override;
};

std::istream& operator>>(std::istream& input, SolutionFirst* solution);