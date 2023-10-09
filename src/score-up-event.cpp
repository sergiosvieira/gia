#include "include/score-up-event.h"

void ScoreUpEvent::accept(struct HandlerVisitor& visitor) const {
    visitor.visit(*this);
}
