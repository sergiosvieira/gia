#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <unordered_map>
#include <unordered_set>
#include <queue>
#include "event.h"
#include "game.h"

struct EventManager {
    using Queue = std::queue<EventPtr>;
    using Map = std::unordered_map<EventType, std::unordered_set<HandlerPtr>>;
    EventManager(){}
    EventManager(EventManager const&) = delete;
    void operator=(EventManager const&) = delete;
    static EventManager& instance() {
        static EventManager self;
        return self;
    }
    void subscribe(EventType, std::shared_ptr<struct Node>);
private:
    Map map = {
        {EventType::KeyPressed, {}},
        {EventType::MouseClick, {}},
        {EventType::ChangeState, {}},
    };
    Queue events;
    friend Game;
    void systemEvents();
    void processEvents();
};

#endif // EVENTMANAGER_H
