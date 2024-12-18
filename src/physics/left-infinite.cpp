#include "physics/left-infinite.h"
#include "game.h"

#include <cmath>

Vector2 LeftInfinite::move(const Rectangle& rect, Orientation, const Rectangle&) {
    Vector2 result = Physics::translate({rect.x, rect.y}, speed, Orientation::Left);
    float diff = std::fabs(rect.width - Game::winWidth());
    if (result.x < -diff) {
        result.x = 0.f;
    }
    return result;
}

