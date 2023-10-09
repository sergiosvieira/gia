#include "../include/mouse-event.h"


void MouseEvent::accept(struct HandlerVisitor& visitor) const {
    visitor.visit(*this);
}
