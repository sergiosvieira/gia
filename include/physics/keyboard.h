#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "physics.h"

struct Keyboard: Physics {
    explicit Keyboard(Vector2 velocity): Physics(velocity){}
    Vector2 move(const Rectangle& rect = {}, Orientation orient= Orientation::None, const Rectangle& ground = {}) override {
        return Physics::translate({rect.x, rect.y}, vel, orient);
    }
    static Orientation keyCodeToOrientation(int keycode) {
        static Orientation map[] = {
            Orientation::Right,
            Orientation::Left,
            Orientation::Down,
            Orientation::Up
        };
        if (keycode < 262 || keycode > 265) return Orientation::None;
        return map[keycode - KEY_RIGHT];
    }
};

#endif // KEYBOARD_H
