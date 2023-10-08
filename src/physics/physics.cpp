#include "include/physics/physics.h"

#include "raylib.h"

const Physics::Map Physics::m = {
    {Physics::Orientation::None, [](Vector2 pos, float speed){return pos;}},
    {Physics::Orientation::Left, [](Vector2 pos, float speed){return Vector2{pos.x - speed, pos.y};}},
    {Physics::Orientation::Right, [](Vector2 pos, float speed){return Vector2{pos.x + speed, pos.y};}},
    {Physics::Orientation::Up, [](Vector2 pos, float speed){return Vector2{pos.x, pos.y - speed};}},
    {Physics::Orientation::Down, [](Vector2 pos, float speed){return Vector2{pos.x, pos.y + speed};}},
    {Physics::Orientation::UpLeft, [](Vector2 pos, float speed){return Vector2{pos.x - speed, pos.y - speed};}},
    {Physics::Orientation::UpRight, [](Vector2 pos, float speed){return Vector2{pos.x + speed, pos.y - speed};}},
    {Physics::Orientation::DownLeft, [](Vector2 pos, float speed){return Vector2{pos.x - speed, pos.y + speed};}},
    {Physics::Orientation::DownRight, [](Vector2 pos, float speed){return Vector2{pos.x + speed, pos.y + speed};}}
};

Physics::~Physics(){}

Vector2 Physics::translate(const Vector2& pos, float speed, Orientation o) {
    auto it = m.find(o);
    if (it != m.end()) {
        return it->second(pos, speed);
    } else {
        return pos;
    }
}
