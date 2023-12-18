#pragma once

#include <memory>

// Customizable data type for seeds;
typedef int64_t seed_t;


class ISolution {
public:

    virtual seed_t solve() = 0;

    virtual ~ISolution() {}
};

struct SeedMap {
    seed_t target;
    seed_t source;
    seed_t length;

    bool operator<(const SeedMap& other) const {
        if (source == other.source) {
            return length < other.length;
        }
        return source < other.source;
    }
};