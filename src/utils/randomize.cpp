#include "include/utils/randomize.h"

#include <random>
#include <cmath>
#include "raylib.h"


int Randomize::gen(int min, int max) {
    static std::mt19937 generator;
    DistInt distribution(min, max);
    int result = distribution(generator);
    return result;
}

float Randomize::gen(float min, float max) {
    static std::mt19937 generator;
    DistFlo distribution(min, max);
    float result = distribution(generator);
    return result;
}

float Randomize::genGAP(float max, float min) {
    float gap = std::ceil(max / min);
    float val = std::floor(gen(0.f, gap));
    return val * min;
}
