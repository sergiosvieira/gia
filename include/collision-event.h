#ifndef COLLISIONEVENT_H
#define COLLISIONEVENT_H

#include "event.h"

struct CollisionEvent : Event {
    ~CollisionEvent(){}
    EventType type() override {
        return EventType::Collision;
    }
    void accept(struct HandlerVisitor& visitor) override;
};


#endif // COLLISIONEVENT_H
