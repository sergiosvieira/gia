#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include <memory>
#include "raylib.h"

#include "include/animation/frame.h"

struct AnimatedSprite {
    using Texture2DPtr = std::unique_ptr<Texture2D>;
    float elapsed = GetTime();
    Frame frame;
    Texture2DPtr texture = nullptr;
    AnimatedSprite(const std::string& filename = "", Frame frame = {});
    virtual ~AnimatedSprite();
    void update();
    void render(const Rectangle& dst);
};

using AnimatedSpritePtr = std::shared_ptr<AnimatedSprite>;

#endif // ANIMATEDSPRITE_H
