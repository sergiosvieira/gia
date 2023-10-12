#ifndef JUMPRANDOM_H
#define JUMPRANDOM_H

#include "jump.h"
#include "include/utils/randomize.h"

struct JumpRandom: Jump {
    JumpRandom(Vector2 velocity): Jump(velocity) {
        gravity = std::make_shared<Gravity>(velocity);
    }
    Vector2 move(const Rectangle& rect, Orientation orientation = Orientation::None, const Rectangle& grect = {}) override {
        int flag = Randomize::instance().gen(0, 1000);
        if (flag > 900) {
            jump();
        }
        return Jump::move(rect, orientation, grect);
    }
};

#endif // JUMPRANDOM_H
