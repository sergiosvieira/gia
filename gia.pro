TEMPLATE = app
CONFIG += console c++20
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -L/usr/local/lib64 -lraylib -ldl -lpthread

SOURCES += \
        main.cpp \
        src/event-manager.cpp \
        src/gia-math.cpp \
        src/game.cpp \
        src/keyboard-event.cpp \
        src/mouse-event.cpp \
        src/node.cpp

HEADERS += \
    examples/node-events.h \
    examples/squares.h \
    include/event-manager.h \
    include/event-type.h \
    include/event.h \
    include/game-state.h \
    include/game.h \
    include/gia-math.h \
    include/handler-visitor.h \
    include/handler.h \
    include/keyboard-event.h \
    include/mouse-event.h \
    include/node.h \
