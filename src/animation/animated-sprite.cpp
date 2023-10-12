#include "include/animation/animated-sprite.h"


AnimatedSprite::AnimatedSprite(const std::string& filename, Frame frame): frame(frame) {
    texture = std::make_unique<Texture2D>(LoadTexture(filename.c_str()));
}

AnimatedSprite::~AnimatedSprite() {
    if (texture) {
        UnloadTexture(*texture);
        texture.release();
    }
}

void AnimatedSprite::update() {
    if (GetTime() - elapsed > frame.interval) {
        frame.next();
        elapsed = GetTime();
    }
}

void AnimatedSprite::render(const Rectangle& dst) {
    const Rectangle& rect = frame.getRect();
    DrawTexturePro(*texture, rect, dst, Vector2{0.f, 0.f}, 0.f, WHITE);
}
