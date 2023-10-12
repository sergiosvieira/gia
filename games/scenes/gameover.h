#ifndef GAMEOVER_H
#define GAMEOVER_H

#include "raygui/src/raygui.h"
#include "include/node.h"
#include "include/game.h"

struct GameOver : Node {
    Color color;
    GameOver(Color color): Node({0.f, 0.f}, Node::Dimensions{Game::winWidth(), Game::winHeight() / 2.f}), color(color) {}
    void render() override {
        GuiSetStyle(DEFAULT, TEXT_SIZE, 150);
        GuiSetStyle(DEFAULT, TEXT_SPACING, 10);
        GuiSetStyle( DEFAULT, TEXT_COLOR_NORMAL, 0xFFFFFFFF);
        GuiSetStyle(LABEL, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
        ClearBackground(color);
        GuiSetStyle(DEFAULT, TEXT_SIZE, 100);
        GuiLabel({0, 0, dim.width, dim.height}, "GAME OVER");
    }
};

#endif // GAMEOVER_H
