#include "include/utils/randomize.h"

#include <random>


int Randomize::gen(int min, int max) {
    static std::mt19937 generator;
    Distribution distribution(min, max);
    int result = distribution(generator);
    return result;
}

