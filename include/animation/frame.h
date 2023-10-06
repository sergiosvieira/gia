#ifndef FRAME_H
#define FRAME_H

struct Frame {
    struct Size {
        float width = 0.f, height = 0.f;
    };
    struct Index {
        int current = 0, first = 0, last = 0;
    };
    struct Spritesheet {
        int rows = 0, cols = 0;
    };
    Frame(){}
    Frame(Size size, Index indexes, Spritesheet ss, float interval);
    struct Rectangle getRect() const;
    void next();
    float width = 0, height = 0;
    int currentIndex = 0, firstIndex = 0, lastIndex = 0;
    int rows = 0, cols = 0;
    float interval = 0.0f, start = 0.f;
};

#endif // FRAME_H
