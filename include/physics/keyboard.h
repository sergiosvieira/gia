#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "physics.h"

struct Keyboard: Physics {
    explicit Keyboard(Vector2 v): Physics(v){}
    Vector2 move(const Rectangle& rect, const Rectangle& grect, Orientation orient= Orientation::None) override {
        return Physics::translate({rect.x, rect.y}, vel.x, orient);
    }
};

using KeyboardPtr = std::shared_ptr<Keyboard>;

#endif // KEYBOARD_H
