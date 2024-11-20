#include "collision-event.h"

void CollisionEvent::accept(struct HandlerVisitor& visitor) const {
    visitor.visit(*this);
}
