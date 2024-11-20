#ifndef GUI_H
#define GUI_H

#include "raygui/src/raygui.h"
#include "event-manager.h"
#include "change-state-event.h"
#include "game.h"

float center(float p1, float p2) {
    return (p1 - p2) / 2.f;
}

struct MainScreen : Node {
    MainScreen(): Node() {
        GuiSetStyle(DEFAULT, TEXT_SIZE, 50);
        GuiSetStyle(DEFAULT, TEXT_SPACING, 10);
        GuiSetStyle( DEFAULT, TEXT_COLOR_NORMAL, 0xFFFFFFFF);
        GuiSetStyle(LABEL, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
    }
    void render() override {
        ClearBackground(BLACK);
        GuiSetStyle(DEFAULT, TEXT_SIZE, 50);
        GuiLabel({0, 0, Game::winWidth(), Game::winHeight() / 3}, "SPACE IA");
        GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
        if (GuiButton({center(Game::winWidth(), 200), 200, 200, 50}, "INICIAR")) {
            EventManager::instance().emmit(std::make_shared<ChangeStateEvent>(GameState::GameOver));
        }
    }
};


struct GameOver : Node {
    GameOver(): Node() {
        GuiSetStyle(DEFAULT, TEXT_SIZE, 150);
        GuiSetStyle(DEFAULT, TEXT_SPACING, 10);
        GuiSetStyle( DEFAULT, TEXT_COLOR_NORMAL, 0xFFFFFFFF);
        GuiSetStyle(LABEL, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
    }
    void render() override {
        ClearBackground(RED);
        GuiSetStyle(DEFAULT, TEXT_SIZE, 100);
        GuiLabel({0, 0, Game::winWidth(), Game::winHeight()}, "GAME OVER");
    }
};


void start() {
    Game game("GUI");
    game.add(GameState::MainScreen, std::make_shared<MainScreen>());
    game.add(GameState::GameOver, std::make_shared<GameOver>());
    game.run();
}

#endif // GUI_H
