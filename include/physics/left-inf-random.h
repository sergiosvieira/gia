#ifndef LEFTINFRANDOM_H
#define LEFTINFRANDOM_H
#include "physics.h"
#include <raylib.h>
#include "include/utils/randomize.h"
#include "include/game.h"

struct LeftInfiniteRandom: Physics {
    Vector2 move(const Rectangle& rect, const Rectangle& grect, Orientation = Orientation::None) override {
        vel.x = vel.y;
        Vector2 result = Physics::translate({rect.x, rect.y}, vel.x, Orientation::Left);
        if (result.x < -rect.width) {
            result.x = Game::winWidth() + Randomize::gen(Game::winWidth()/2.f, Game::winWidth());
        }
        return result;
    }
};


#endif // LEFTINFRANDOM_H
