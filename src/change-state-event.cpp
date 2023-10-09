#include "include/change-state-event.h"
#include "include/handler-visitor.h"

void ChangeStateEvent::accept(HandlerVisitor& visitor) const {
    visitor.visit(*this);
}
