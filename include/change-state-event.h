#ifndef CHANGESTATEEVENT_H
#define CHANGESTATEEVENT_H

#include <raylib.h>
#include "event.h"
#include "game-state.h"

struct ChangeStateEvent : Event {
    GameState state = GameState::None;
    explicit ChangeStateEvent(GameState state): state(state){}
    ~ChangeStateEvent(){}
    EventType type() const override {
        return EventType::StateChanged;
    }
    void accept(struct HandlerVisitor& visitor) const override;
};

#endif // CHANGESTATEEVENT_H
