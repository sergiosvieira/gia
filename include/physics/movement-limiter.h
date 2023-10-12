#ifndef MOVEMENTLIMITER_H
#define MOVEMENTLIMITER_H

struct MovementLimiter {
    static struct Vector2 limit(const struct Rectangle& r1, const struct Rectangle& r2);
};

#endif // MOVEMENTLIMITER_H
