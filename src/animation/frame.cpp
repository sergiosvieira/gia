#include "include/animation/frame.h"

#include "raylib.h"

Rectangle Frame::getRect() const {
    int row = currentIndex / cols;
    int col = currentIndex % cols;
    float x = static_cast<float>(col * width);
    float y = static_cast<float>(row * height);
    return {x, y, width, height};
}

void Frame::next() {
    if (currentIndex + 1 > lastIndex) {
        currentIndex = firstIndex;
    } else {
        ++currentIndex;
    }
}

Frame::Frame(Size size, Index indexes, Spritesheet ss, float interval):
    width(size.width), height(size.height), currentIndex(indexes.current),
    firstIndex(indexes.first), lastIndex(indexes.last), rows(ss.rows),
    cols(ss.cols), interval(interval){}
