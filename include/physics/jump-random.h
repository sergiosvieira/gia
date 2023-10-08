#ifndef JUMPRANDOM_H
#define JUMPRANDOM_H

#include "jump.h"
#include "include/utils/randomize.h"

struct JumpRandom: Jump {
    JumpRandom(Vector2 velocity): Jump(velocity) {
        gravity = std::make_shared<Gravity>(velocity);
    }
    Vector2 move(const Rectangle& rect, const Rectangle& grect, Orientation = Orientation::None) override {
        int flag = Randomize::gen(0, 1000);
        if (flag > 900) {
            jump();
        }
        return Jump::move(rect, grect);
    }
};

#endif // JUMPRANDOM_H
