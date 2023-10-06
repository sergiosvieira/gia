#ifndef LAYOUT_H
#define LAYOUT_H

struct Layout {
    static float center(float p1, float p2) {
        return (p1 - p2) / 2.f;
    }
};

#endif // LAYOUT_H
