#ifndef RANDOMORIENTATION_H
#define RANDOMORIENTATION_H

#include "physics/physics.h"
#include "utils/randomize.h"

struct RandomOrientation: Physics {
    RandomOrientation(Vector2 velocity): Physics(velocity) {}
    Vector2 move(const Rectangle& rect = {}, Orientation = Orientation::None, const Rectangle& ground = {}) override {
        std::vector<Orientation> v = {Orientation::None, Orientation::Left, Orientation::Right, Orientation::Up, Orientation::Down};
        Orientation d = Randomize::instance().elements<Orientation>(v);
        return Physics::m.at(d)({rect.x, rect.y}, vel);
    }
};


#endif // RANDOMORIENTATION_H
