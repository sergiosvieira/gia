#ifndef PHYSICS_H
#define PHYSICS_H

#include <raylib.h>
#include <unordered_map>
#include <functional>
#include <memory>

struct Physics {
    enum class Orientation {
        None,
        Left,
        Right,
        Up,
        Down,
        UpLeft,
        UpRight,
        DownLeft,
        DownRight
    };
    Vector2 vel = {0.f, 0.f};
    using Map = std::unordered_map<Orientation, std::function<Vector2(Vector2, float)>>;
    static const Map m;
    explicit Physics(Vector2);
    Physics();
    virtual ~Physics();
    static Vector2 translate(const Vector2&, float, Orientation);
    static bool collides(const Rectangle& r1, const Rectangle& r2);
    virtual Vector2 move(const Rectangle&, const Rectangle&, Orientation = Orientation::None) = 0;
};

using PhysicsPtr = std::shared_ptr<Physics>;


#endif // PHYSICS_H
