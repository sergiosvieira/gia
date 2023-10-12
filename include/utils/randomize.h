#ifndef RANDOMIZE_H
#define RANDOMIZE_H

#include <vector>
#include <random>

struct Randomize {
    Randomize(){}
    virtual ~Randomize(){}
    Randomize(Randomize const&) = delete;
    void operator=(Randomize const&) = delete;
    static Randomize& instance() {
        static Randomize self;
        return self;
    }
    int gen(int min, int max);
    float gen(float min, float max);
    float genGAP(float max, float min);
    template <typename T>
    T elements(const std::vector<T>& v) {
        if (v.empty()) return T();
        int randomIndex = gen(0, v.size() - 1);
        return v[randomIndex];
    }
private:
    std::random_device rd;
};

#endif // RANDOMIZE_H
