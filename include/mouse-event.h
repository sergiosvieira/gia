#ifndef MOUSECLICKED_H
#define MOUSECLICKED_H

#include <raylib.h>
#include "event.h"

struct MouseEvent: Event {
    MouseButton code = MOUSE_BUTTON_LEFT;
    Vector2 pos = {};
    MouseEvent(MouseButton btn, Vector2 pos):
        code(btn), pos(pos){}
    EventType type() override {
        return EventType::MouseClick;
    }
    void accept(struct HandlerVisitor& visitor) override;
};

#endif // MOUSECLICKED_H
