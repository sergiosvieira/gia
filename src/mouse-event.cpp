#include "../include/mouse-event.h"


void MouseEvent::accept(struct HandlerVisitor& visitor) {
    visitor.visit(*this);
}
