#ifndef RANDOMIZE_H
#define RANDOMIZE_H

#include <vector>
#include <random>

struct Randomize {
    using DistInt = std::uniform_int_distribution<int>;
    using DistFlo = std::uniform_real_distribution<float>;
    static int gen(int min, int max);
    static float gen(float min, float max);
    static float genGAP(float max, float min);
    template <typename T>
    static T elements(const std::vector<T>& v) {
        if (v.empty()) return T();
        int randomIndex = gen(0, v.size() - 1);
        return v[randomIndex];
    }
};

#endif // RANDOMIZE_H
