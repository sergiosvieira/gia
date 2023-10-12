#include "include/physics/physics.h"

#include "raylib.h"

const Physics::Map Physics::m = {
    {Physics::Orientation::None, [](Vector2 pos, Vector2 vel){return pos;}},
    {Physics::Orientation::Left, [](Vector2 pos, Vector2 vel){return Vector2{pos.x - vel.x, pos.y};}},
    {Physics::Orientation::Right, [](Vector2 pos, Vector2 vel){return Vector2{pos.x + vel.x, pos.y};}},
    {Physics::Orientation::Up, [](Vector2 pos, Vector2 vel){return Vector2{pos.x, pos.y - vel.y};}},
    {Physics::Orientation::Down, [](Vector2 pos, Vector2 vel){return Vector2{pos.x, pos.y + vel.y};}},
    {Physics::Orientation::UpLeft, [](Vector2 pos, Vector2 vel){return Vector2{pos.x - vel.x, pos.y - vel.y};}},
    {Physics::Orientation::UpRight, [](Vector2 pos, Vector2 vel){return Vector2{pos.x + vel.x, pos.y - vel.y};}},
    {Physics::Orientation::DownLeft, [](Vector2 pos, Vector2 vel){return Vector2{pos.x - vel.x, pos.y + vel.y};}},
    {Physics::Orientation::DownRight, [](Vector2 pos, Vector2 vel){return Vector2{pos.x + vel.x, pos.y + vel.y};}}
};

Physics::Physics(Vector2 v): vel(v) {

}

Physics::Physics() {

}

Physics::~Physics(){}

Vector2 Physics::translate(const Vector2& pos, float speed, Orientation o) {
    auto it = m.find(o);
    if (it != m.end()) {
        return it->second(pos, {speed, speed});
    } else {
        return pos;
    }
}

Vector2 Physics::translate(const Vector2& pos, const Vector2& vel, Orientation o) {
    auto it = m.find(o);
    if (it != m.end()) {
        return it->second(pos, vel);
    } else {
        return pos;
    }
}

bool Physics::collides(const Rectangle& r1, const Rectangle& r2) {
    bool result = CheckCollisionRecs(r1, r2);
    return result;
}
