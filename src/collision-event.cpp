#include "include/collision-event.h"

void CollisionEvent::accept(struct HandlerVisitor& visitor) {
    visitor.visit(*this);
}
