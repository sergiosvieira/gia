#ifndef RANDOMIZE_H
#define RANDOMIZE_H

#include <vector>
#include <random>

struct Randomize {
    using Distribution = std::uniform_int_distribution<int>;
    static int gen(int min, int max);
    template <typename T>
    static T elements(const std::vector<T>& v) {
        if (v.empty()) return T();
        std::random_device rd;
        std::mt19937 gen(rd());
        Distribution distribution(0, v.size() - 1);
        int randomIndex = distribution(gen);
        return v[randomIndex];
    }
};

#endif // RANDOMIZE_H
