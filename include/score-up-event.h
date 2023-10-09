#ifndef SCOREUPEVENT_H
#define SCOREUPEVENT_H

#include "event.h"

struct ScoreUpEvent : Event {
    EventType type() const override {
        return EventType::ScoreIncreased;
    }
    ~ScoreUpEvent(){}
    void accept(struct HandlerVisitor& visitor) const override;
};

#endif // SCOREUPEVENT_H
