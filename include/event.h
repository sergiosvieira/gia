#ifndef EVENT_H
#define EVENT_H

#include "event-type.h"
#include "node.h"


struct Event {
    NodePtr sender = nullptr;
    virtual ~Event() {}
    virtual EventType type() const {
        return EventType::None;
    }
    virtual void accept(struct HandlerVisitor& visitor) const = 0;
};

using EventPtr = std::shared_ptr<Event>;

#endif // EVENT_H
