#include "../include/keyboard-event.h"
#include "../include/handler-visitor.h"

void KeyboardEvent::accept(struct HandlerVisitor& visitor) const {
    visitor.visit(*this);
}
