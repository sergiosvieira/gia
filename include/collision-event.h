#ifndef COLLISIONEVENT_H
#define COLLISIONEVENT_H

#include "event.h"

struct CollisionEvent : Event {
    ~CollisionEvent(){}
    EventType type() const override {
        return EventType::Collision;
    }
    void accept(struct HandlerVisitor& visitor) const override;
};


#endif // COLLISIONEVENT_H
