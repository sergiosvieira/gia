#include "../include/keyboard-event.h"
#include "../include/handler-visitor.h"

void KeyboardEvent::accept(struct HandlerVisitor& visitor) {
    visitor.visit(*this);
}
