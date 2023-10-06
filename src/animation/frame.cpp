#include "include/animation/frame.h"

#include "raylib.h"
#include "include/utils/data-time.h"

Rectangle Frame::getRect() const {
    int row = currentIndex / cols;
    int col = currentIndex % cols;
    float x = static_cast<float>(col * width);
    float y = static_cast<float>(row * height);
    return {x, y, width, height};
}

void Frame::next() {
    if (currentIndex < lastIndex) {
        float now = GetTime();
        if (timer(now, start, interval)) {
            start = now;
            ++currentIndex;
        }
    }
    else {
        currentIndex = firstIndex;
    }
}

Frame::Frame(Size size, Index indexes, Spritesheet ss, float interval):
    width(size.width), height(size.height), currentIndex(indexes.current),
    firstIndex(indexes.first), lastIndex(indexes.last), rows(ss.rows),
    cols(ss.cols), interval(interval){}
