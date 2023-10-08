#include "include/animation/animated-sprite.h"


AnimatedSprite::AnimatedSprite(const std::string& filename, Frame frame): frame(frame) {
    texture = std::make_shared<Texture2D>(LoadTexture(filename.c_str()));
}

AnimatedSprite::~AnimatedSprite() {
    if (texture && texture.use_count() == 1) UnloadTexture(*texture);
}

void AnimatedSprite::update() {
    if (GetTime() - elapsed > frame.interval) {
        frame.next();
        elapsed = GetTime();
    }
}

void AnimatedSprite::render(const Rectangle& dst) {
    DrawTexturePro(*texture, frame.getRect(), dst, Vector2{0.f, 0.f}, 0.f, WHITE);
}
