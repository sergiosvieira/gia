#ifndef LEFTINFRANDOM_H
#define LEFTINFRANDOM_H
#include "physics.h"
#include <raylib.h>
#include "include/utils/randomize.h"
#include "include/game.h"
#include "include/event-manager.h"
#include "include/score-up-event.h"

struct LeftInfiniteRandom: Physics {
    enum class Type {Horizontal, Vertical, Both};
    Type type = Type::Both;
    LeftInfiniteRandom(const Vector2& velocity, Type type = Type::Both): Physics(velocity), type(type) {}
    Vector2 move(const Rectangle& rect, Orientation = Orientation::None, const Rectangle& = {}) override {
        Vector2 result = Physics::translate({rect.x, rect.y}, vel, Orientation::Left);
        if (result.x < -rect.width) {
            result = randomize(rect);
            EventManager::instance().emmit(std::make_shared<ScoreUpEvent>());
        }
        return result;
    }
    Vector2 randomize(const Rectangle& rect) {
        Vector2 result = {rect.x, rect.y};
        if (type == Type::Both || type == Type::Horizontal) {
            result.x = Game::winWidth() + Randomize::instance().gen(Game::winWidth()/2.f, Game::winWidth() * 2.f);
        }
        if (type == Type::Both || type == Type::Vertical) {
            result.y = Randomize::instance().genGAP(Game::halfHeightRect().height, rect.height);
        }
        return result;
    }
};


#endif // LEFTINFRANDOM_H
