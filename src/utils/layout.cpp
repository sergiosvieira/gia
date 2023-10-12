#include "include/utils/layout.h"

#include "raylib.h"

float Layout::center(float p1, float p2) {
    return (p1 - p2) / 2.f;
}

Vector2 Layout::center(const Rectangle& r1, const Rectangle& r2) {
    Rectangle smallRect = Layout::min(r1, r2);
    Rectangle bigRect = Layout::max(r1, r2);
    float centerX = bigRect.x + (bigRect.width - smallRect.width) / 2;
    float centerY = bigRect.y + (bigRect.height - smallRect.height) / 2;
    return {centerX, centerY};
}

Rectangle Layout::min(const Rectangle& rect1, const Rectangle& rect2) {
    float area1 = rect1.width * rect1.height;
    float area2 = rect2.width * rect2.height;
    return (area1 < area2) ? rect1 : rect2;
}

Rectangle Layout::max(const Rectangle& rect1, const Rectangle& rect2) {
    float area1 = rect1.width * rect1.height;
    float area2 = rect2.width * rect2.height;
    return (area1 > area2) ? rect1 : rect2;
}
