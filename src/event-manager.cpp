#include "../include/event-manager.h"

#include <memory>
#include "raylib.h"
#include "include/keyboard-event.h"
#include "include/mouse-event.h"
#include "include/node.h"

void EventManager::subscribe(EventType type, PtrNode node) {
    map[type].insert(node);
}

void EventManager::subscribe(EventType type, HandlerPtr handler) {
    map[type].insert(handler);
}

void EventManager::emmit(EventPtr event) {
    events.push(event);
}

void EventManager::systemEvents() {
    KeyboardKey code = static_cast<KeyboardKey>(GetKeyDown());
    if (code != KEY_NULL) {
        events.push(std::make_shared<KeyboardEvent>(code));
    }
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        events.push(std::make_shared<MouseEvent>(MOUSE_BUTTON_LEFT, GetMousePosition()));
    }
}

void EventManager::processEvents() {
    while (!events.empty()) {
        EventType type = events.front()->type();
        for (HandlerPtr ptr: map[type]) {
            ptr->handle(*events.front());
        }
        events.pop();
    }
}
