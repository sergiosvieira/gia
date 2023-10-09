#ifndef EVENTTYPE_H
#define EVENTTYPE_H

enum class EventType {
    None,
    MouseClicked,
    KeyPressed,
    StateChanged,
    ScoreIncreased,
    ScoreDecreased,
    Collision
};

#endif // EVENTTYPE_H
