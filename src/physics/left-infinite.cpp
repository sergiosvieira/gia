#include "include/physics/left-infinite.h"
#include "include/game.h"

#include <cmath>

Vector2 LeftInfinite::move(const Rectangle& rect, const Rectangle& grect = {}, Orientation o = Orientation::None) {
    Vector2 result = Physics::translate({rect.x, rect.y}, speed, Orientation::Left);
    float diff = std::fabs(rect.width - Game::winWidth());
    if (result.x < -diff) {
        result.x = 0.f;
    }
    return result;
}

