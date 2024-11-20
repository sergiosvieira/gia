#include "sprite.h"

Sprite::Sprite(){}

Sprite::Sprite(const std::string& filename) {
    texture = std::make_shared<Texture2D>(LoadTexture(filename.c_str()));
}

Sprite::~Sprite() {
    if (texture != nullptr && texture.use_count() == 1) UnloadTexture(*texture);
}

void Sprite::render(const Rectangle& rect) {
    if (texture == nullptr) return;
    DrawTexture(*texture, rect.x, rect.y, WHITE);
}

void Sprite::renderRect(const Rectangle& src, const Rectangle& dst){
    if (texture == nullptr) return;
    DrawTexturePro(*texture, src, dst, {0.f, 0.f}, 0.f, WHITE);
}
