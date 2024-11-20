#include "../include/event-manager.h"

#include <memory>
#include "raylib.h"
#include "keyboard-event.h"
#include "mouse-event.h"
#include "node.h"

void EventManager::subscribe(EventType type, Node::NodeShared node) {
    map[type].insert(node);
}

void EventManager::subscribe(EventType type, HandlerPtr handler) {
    map[type].insert(handler);
}

void EventManager::emmit(EventPtr event) {
    events.push(event);
}

int GetKeyDown() {
    int latestPKey=0;
    int PKey=0;//ig the keyupdate is too fast...
    // void inputKeyTest(){PKey=GetKeyPressed();
    if(PKey)latestPKey=PKey;
    if(IsKeyDown(latestPKey))printf("keyDown:(%i)\n",latestPKey);    
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
        if (type == EventType::ScoreIncreased) {
            size_t s = map[type].size();
            std::cout << s << '\n';
        }
        for (HandlerPtr ptr: map[type]) {
            ptr->handle(*events.front());
        }
        events.pop();
    }
}
