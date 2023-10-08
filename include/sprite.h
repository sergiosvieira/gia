#ifndef SPRITE_H
#define SPRITE_H

#include <iostream>
#include <memory>
#include "raylib.h"

struct Sprite {
    using Texture2DPtr = std::shared_ptr<Texture2D>;
    Texture2DPtr texture = nullptr;
    Sprite();
    Sprite(const std::string& filename);
    virtual ~Sprite();
    void render(const Rectangle& rect);
    void renderRect(const Rectangle& src, const Rectangle& dst);
};

using SpritePtr = std::shared_ptr<Sprite>;

#endif // SPRITE_H
