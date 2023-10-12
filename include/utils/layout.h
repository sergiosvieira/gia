#ifndef LAYOUT_H
#define LAYOUT_H

struct Layout {
    static float center(float p1, float p2);
    static struct Vector2 center(const struct Rectangle& rect1, const struct Rectangle& rect2);
    static struct Rectangle min(const struct Rectangle& rect1, const struct Rectangle& rect2);
    static struct Rectangle max(const struct Rectangle& rect1, const struct Rectangle& rect2);
};

#endif // LAYOUT_H
