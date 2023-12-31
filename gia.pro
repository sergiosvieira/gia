TEMPLATE = app
CONFIG += console c++20 -g
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -L/usr/local/lib64 -lraylib -ldl -lpthread -lGL
LIBS += -lraygui
#LIBS += -L/usr/local/lib64 -lraylib -fpic -lGL -lm -ldl -lrt -lX11 -lpthread
#DEFINES +== RAYGUI_IMPLEMENTATION

SOURCES += \
        main.cpp \
        src/animation/animated-sprite.cpp \
        src/animation/frame.cpp \
        src/change-state-event.cpp \
        src/collision-event.cpp \
        src/event-manager.cpp \
        src/gia-math.cpp \
        src/game.cpp \
        src/keyboard-event.cpp \
        src/mouse-event.cpp \
        src/node.cpp \
        src/physics/left-infinite.cpp \
        src/physics/movement-limiter.cpp \
        src/physics/physics.cpp \
        src/score-down-event.cpp \
        src/score-up-event.cpp \
        src/sprite.cpp \
        src/utils/layout.cpp \
        src/utils/randomize.cpp

HEADERS += \
    examples/gui.h \
    examples/node-events.h \
    examples/split-screens.h \
    examples/squares.h \
    games/dino-ai/dino-ai.h \
    games/scenes/gameover.h \
    games/space-ai/space-ai.h \
    include/animation/animated-sprite.h \
    include/animation/frame.h \
    include/change-state-event.h \
    include/collision-event.h \
    include/event-manager.h \
    include/event-type.h \
    include/event.h \
    include/game-state.h \
    include/game.h \
    include/gia-math.h \
    include/handler-visitor.h \
    include/handler.h \
    include/physics/jump-random.h \
    include/keyboard-event.h \
    include/mouse-event.h \
    include/node.h \
    include/physics/gravity.h \
    include/physics/jump.h \
    include/physics/keyboard.h \
    include/physics/left-inf-random.h \
    include/physics/left-infinite.h \
    include/physics/movement-limiter.h \
    include/physics/physics.h \
    include/physics/random-orientation.h \
    include/score-down-event.h \
    include/score-up-event.h \
    include/sprite.h \
    include/tests/node-tests.h \
    include/utils/data-time.h \
    include/utils/layout.h \
    include/utils/randomize.h \

