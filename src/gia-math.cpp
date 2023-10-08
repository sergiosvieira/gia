#include "../include/gia-math.h"

#include "raylib.h"

Vector2 operator-(const Vector2& v1, const Vector2& v2) {
    return {v1.x - v2.x, v1.y - v2.y};
}

Vector2 operator+(const Vector2& v1, const Vector2& v2) {
    return {v1.x + v2.x, v1.y + v2.y};
}

Rectangle padding(const Rectangle& rect, float paddingH, float paddingV) {
    return {rect.x + paddingH, rect.y + paddingV, rect.width - 2 * paddingH, rect.height - 2 * paddingV};
}
