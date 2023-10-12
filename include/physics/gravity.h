#ifndef GRAVITY_H
#define GRAVITY_H

#include "physics.h"

struct Gravity: Physics {
    Vector2 accel = {0.f, 0.f};
    float accelInc = 0.5;
    float maxAccel = 10.f;
    explicit Gravity(Vector2 v): Physics(v){}
    Vector2 move(const Rectangle& rect, Orientation = Orientation::None, const Rectangle& ground = {}) override {
        return Physics::translate({rect.x, rect.y}, vel.y + accelInc, Orientation::Down);
    }
};

using GravityPtr = std::shared_ptr<Gravity>;

#endif // GRAVITY_H
