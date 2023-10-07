#include "include/score-up-event.h"

void ScoreUpEvent::accept(struct HandlerVisitor& visitor) {
    visitor.visit(*this);
}
