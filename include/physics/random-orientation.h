#ifndef RANDOMORIENTATION_H
#define RANDOMORIENTATION_H

#include "include/physics/physics.h"
#include "include/utils/randomize.h"

struct RandomOrientation: Physics {
    RandomOrientation(Vector2 velocity): Physics(velocity) {}
    Vector2 move(const Rectangle& rect, const Rectangle& grect, Orientation = Orientation::None) override {
        std::vector<Orientation> v = {Orientation::None, Orientation::Left, Orientation::Right, Orientation::Up, Orientation::Down};
        Orientation d = Randomize::elements<Orientation>(v);
        return Physics::m.at(d)({rect.x, rect.y}, vel.x);
    }
};

using RandomOrientationPtr = std::shared_ptr<RandomOrientation>;

#endif // RANDOMORIENTATION_H
