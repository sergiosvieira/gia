#ifndef PHYSICS_H
#define PHYSICS_H

#include <unordered_map>
#include <functional>

struct Vector2;
struct Rectangle;

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
    using Map = std::unordered_map<Orientation, std::function<Vector2(Vector2, float)>>;
    static const Map m;
    virtual ~Physics();
    static Vector2 translate(const Vector2&, float, Orientation);
    virtual Vector2 move(const Rectangle&, Orientation = Orientation::None) = 0;
};

#endif // PHYSICS_H
