#ifndef LEFTINFRANDOM_H
#define LEFTINFRANDOM_H
#include "physics.h"
#include <raylib.h>
#include "include/utils/randomize.h"
#include "include/game.h"

struct LeftInfiniteRandom: Physics {
    float speed = 5.f;
    Vector2 move(const Rectangle& rect, Orientation) override {
        Vector2 result = Physics::translate({rect.x, rect.y}, speed, Orientation::Left);
        if (result.x < -rect.width) {
            result.x = Game::winWidth() + Randomize::gen(Game::winWidth()/2.f, Game::winWidth());
        }
        return result;
    }
};


#endif // LEFTINFRANDOM_H
