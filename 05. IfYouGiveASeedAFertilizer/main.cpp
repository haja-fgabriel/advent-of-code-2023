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

#include "SolutionFirst.h"
#include "SolutionSecond.h"

using namespace std;


template<typename T>
using TimePoint = chrono::time_point<T>;

using SteadyClock = chrono::steady_clock;


inline void solveFirst(const char* name) {
    ifstream f(name);
    shared_ptr<ISolution> s1 = make_shared<SolutionFirst>();

    f >> (SolutionFirst*)s1.get();
    cout << "Part 1: " << s1->solve() << endl;
}


inline void solveSecond(const char* name) {
    ifstream f(name);
    shared_ptr<ISolution> s2 = make_shared<SolutionSecond>();
    f >> (SolutionSecond*)s2.get();
    cout << "Part 2: " << s2->solve() << endl;
}


int main() {
    const char* filename = "input.txt";
    
    const TimePoint<SteadyClock> timeBegin = SteadyClock::now(); 

    solveFirst(filename);
    solveSecond(filename);

    const TimePoint<SteadyClock> timeEnd = SteadyClock::now(); 
    cout << "Time elapsed: " << fixed << setprecision(7) 
        << 1.0 * chrono::duration_cast<chrono::microseconds>(timeEnd - timeBegin).count() / 1000000 << std::endl;
    return 0;
}