#ifndef LEFTINFINITE_H
#define LEFTINFINITE_H

#include "physics.h"
#include <raylib.h>

struct LeftInfinite: Physics {
    float speed = 5.f;
    Vector2 move(const Rectangle& pos = {}, Orientation = Orientation::Left, const Rectangle& = {}) override;
};

#endif // LEFTINFINITE_H
