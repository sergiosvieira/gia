#include "../include/game.h"

#include <raylib.h>
#include "../include/event-manager.h"

Game::Game(const std::string& title):
    title(title) {
    init();
}

Game::~Game() {
    CloseWindow();
}

void Game::add(GameState state, PtrNode node) {
    states[state] = node;
}

void Game::init() {
    InitWindow(
        static_cast<int>(winWidth()),
        static_cast<int>(winHeight()),
        title.c_str()
    );
    SetTargetFPS(60);
}

void Game::update() {
    for (auto& [state, node]: states) {
        node->update();
    }
}

void Game::draw() {
    for (auto& [state, node]: states) {
        node->draw();
    }
}

void Game::run() {
    while (!WindowShouldClose()) {
        EventManager::instance().systemEvents();
        EventManager::instance().processEvents();
        update();
        BeginDrawing();
        draw();
        ClearBackground(BLACK);
        EndDrawing();
    }
}

float Game::winWidth() {
    return 800.f;
}

float Game::winHeight() {
    return 600.f;
}
