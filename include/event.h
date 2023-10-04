#ifndef EVENT_H
#define EVENT_H

#include "event-type.h"
#include "node.h"


struct Event {
    PtrNode sender = nullptr;
    virtual ~Event() {}
    virtual EventType type() {
        return EventType::None;
    }
    virtual void accept(struct HandlerVisitor& visitor) = 0;
};

using EventPtr = std::shared_ptr<Event>;

#endif // EVENT_H
