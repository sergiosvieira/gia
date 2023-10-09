#ifndef SCOREUPEVENT_H
#define SCOREUPEVENT_H

#include "event.h"

struct ScoreUpEvent : Event {
    EventType type() override {
        return EventType::ScoreIncreased;
    }
    ~ScoreUpEvent(){}
    void accept(struct HandlerVisitor& visitor) override;
};

#endif // SCOREUPEVENT_H
