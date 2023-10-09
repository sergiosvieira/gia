#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include "game-state.h"
#include "node.h"

using StateMap = std::unordered_map<GameState, std::vector<NodePtr>>;

struct GameHandler;

struct Game {
    explicit Game(const std::string&);
    virtual ~Game();
    void run();
    static float winWidth();
    static float winHeight();
    void add(GameState, NodePtr);
    HandlerPtr get(GameState, size_t index);
    Rectangle getRect() const;
private:
    using RenderTexturePtr = std::shared_ptr<RenderTexture2D>;
    using Vector = std::vector<RenderTexturePtr>;
    std::shared_ptr<GameHandler> gameHandler = nullptr;
    void init();
    void addScreens();
    void update();
    void draw();
    void drawScreens();
    void updateScreens();
    StateMap states;
    std::string title = "";
    Vector textures;
    friend GameHandler;
    GameState currentState = GameState::MainScreen;
};

#endif // GAME_H
