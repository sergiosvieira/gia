#include "../include/game.h"

#include <raylib.h>
#include "../include/node.h"
#include "../include/event-manager.h"
#include "../include/change-state-event.h"

struct GameHandler: Handler, HandlerVisitor {
    Game& game;
    explicit GameHandler(Game& g): game(g){}
    ~GameHandler(){}
    void handle(struct Event& event) override {
        event.accept(*this);
    }
    virtual void visit(const ChangeStateEvent& msg) override {
        game.currentState = msg.state;
    }
};

Game::Game(const std::string& title):
    title(title) {
    init();
}

Game::~Game() {
    for (size_t i = 0; i < textures.size(); ++i) {
        RenderTexturePtr scr = textures[i];
        if (scr && scr.use_count() == 1) {
            UnloadRenderTexture(*scr);
        }
    }
    CloseWindow();
}

void Game::add(GameState state, PtrNode node) {
    states[state].push_back(node);
}

HandlerPtr Game::get(GameState state, size_t index) {
    return states[state][index];
}

Rectangle Game::getRect() const {
    return {0.f, 0.f, winWidth(), winHeight()};
}

void Game::init() {
    InitWindow(
        static_cast<int>(winWidth()),
        static_cast<int>(winHeight()),
        title.c_str()
    );
    SetTargetFPS(60);
    gameHandler = std::make_shared<GameHandler>(*this);
    EventManager::instance().subscribe(EventType::StateChanged, gameHandler);
}

void Game::addScreens() {
    if (states.find(currentState) == states.end()) return;
    size_t size = states[currentState].size();
    for (size_t i = 0; i < size; ++i) {
        int w = Game::winWidth();
        int h = Game::winHeight();
        auto renderTexture = std::make_shared<RenderTexture2D>(LoadRenderTexture(w, h));
        textures.push_back(renderTexture);
    }
}

void Game::update() {
    if (states.find(currentState) == states.end()) return;
    for (size_t i = 0; i <  states[currentState].size(); ++i) {
        states[currentState][i]->update();
    }
}

void Game::draw() {
    if (states.find(currentState) == states.end()) return;
    for (size_t i = 0; i < states[currentState].size(); ++i) {
        RenderTexturePtr scr = textures[i];
        BeginTextureMode(*scr);
            states[currentState][i]->draw();
        EndTextureMode();
    }
}

void Game::drawScreens() {
    for (size_t i = 0; i < textures.size(); ++i) {
        RenderTexturePtr scr = textures[i];
        Rectangle src = {
            0.f,
            0.f,
            static_cast<float>(scr->texture.width),
            -static_cast<float>(scr->texture.height)
        };
        float height = scr->texture.height / textures.size();
        Vector2 dst = {
            0.f,
            i * height
        };
        DrawTextureRec(scr->texture, src, dst, WHITE);
    }
}

void Game::run() {
    addScreens();
    while (!WindowShouldClose()) {
        EventManager::instance().systemEvents();
        EventManager::instance().processEvents();
        update();
        draw();
        BeginDrawing();
            drawScreens();
        EndDrawing();
    }
}

float Game::winWidth() {
    return 800.f;
}

float Game::winHeight() {
    return 600.f;
}
