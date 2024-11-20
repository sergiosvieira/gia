#include "physics/movement-limiter.h"

#include "raylib.h"

Vector2 MovementLimiter::limit(const Rectangle& r1, const Rectangle& r2) {
   Vector2 r = {r1.x, r1.y};
   if ((r1.x + r1.width) > r2.width) {
       r.x = r2.width - r1.width;
   }
   if (r1.x < r2.x) {
       r.x = r2.x;
   }
   if ((r1.y + r1.height) > r2.height) {
       r.y = r2.height - r1.height;
   }
   if (r1.y < r2.y) {
       r.y = r2.y;
   }
   return r;
}
