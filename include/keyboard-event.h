#ifndef KEYPRESSED_H
#define KEYPRESSED_H

#include <raylib.h>
#include "event.h"

struct KeyboardEvent : Event {
    KeyboardKey keyCode = KEY_NULL;
    KeyboardEvent(KeyboardKey code): keyCode(code){}
    EventType type() override {
        return EventType::KeyPressed;
    }
    void accept(struct HandlerVisitor& visitor) override;
};



#endif // KEYPRESSED_H
