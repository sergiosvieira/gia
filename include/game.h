#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <unordered_map>
#include "game-state.h"
#include "node.h"

using StateMap = std::unordered_map<GameState, PtrNode>;

struct Game {
    Game(const std::string&);
    virtual ~Game();
    void run();
    static float winWidth();
    static float winHeight();
    void add(GameState, PtrNode);
private:
    void init();
    void update();
    void draw();
    GameState currentState = GameState::MainScreen;
    StateMap states;
    std::string title = "";
};

#endif // GAME_H
