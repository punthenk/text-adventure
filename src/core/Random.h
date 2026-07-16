/*
 * Copyright (c) 2026, Michiel Nijenhuis <contact@michielnijenhuis.com>
 *
 */

#pragma once
#include <vector>
#include <random>

class Random {
public:
    template<typename T>
    static const T& pick(const std::vector<T>& items) {
        std::uniform_int_distribution<size_t> dist(0, items.size() - 1);
        return items[dist(getEngine())];
    }

    static int range(int min, int max) {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(getEngine());
    }

private:
    static std::mt19937& getEngine() {
        static std::mt19937 engine(std::random_device{}());
        return engine;
    }
};
