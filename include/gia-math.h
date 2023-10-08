#ifndef GIAMATH_H
#define GIAMATH_H

//#include <raylib.h>

struct Vector2 operator-(const struct Vector2& v1, const struct Vector2& v2);
struct Vector2 operator+(const struct Vector2& v1, const struct Vector2& v2);

struct Rectangle padding(const struct Rectangle& rect, float paddingH = 0.f, float paddingV = 0.f);

#endif // GIAMATH_H
