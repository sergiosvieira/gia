#ifndef SPLITSCREENS_H
#define SPLITSCREENS_H

#include <sstream>
#include "include/game.h"
#include "include/node.h"

struct Level1 : Node {
    Level1(): Node() {
        width = 50;
        height = 50;
    }
    void render() override {
        ClearBackground(YELLOW);
        DrawRectangleRec({pos.x, pos.y, width, height}, MAROON);
        DrawText("Screen 01", 10, 10, 20, WHITE);
    }
};

struct Level2 : Node {
    Level2(): Node() {
        width = 50;
        height = 50;
    }    
    void render() override {
        ClearBackground(GREEN);
        DrawRectangleRec({pos.x, pos.y, width, height}, BLUE);
        DrawText("Screen 02", 10, 10, 20, WHITE);
    }
};

void start() {
    Game splscr{"Split screen sample"};
    splscr.add(GameState::MainScreen, std::make_shared<Level1>());
    splscr.add(GameState::MainScreen, std::make_shared<Level2>());
    splscr.run();
}

#endif // SPLITSCREENS_H
