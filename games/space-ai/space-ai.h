#ifndef SPACEAI_H
#define SPACEAI_H

#include "raygui/src/raygui.h"
#include "include/game.h"
#include "include/animation/animated-sprite.h"
#include "include/physics/keyboard.h"
#include "include/keyboard-event.h"
#include "include/event-manager.h"
#include "include/game.h"
#include "include/physics/movement-limiter.h"
#include "include/physics/random-orientation.h"
#include "include/utils/layout.h"
#include "include/physics/left-inf-random.h"
#include "games/scenes/gameover.h"

template<typename T>
struct Spaceship: Node {
    AnimatedSprite& sprite;
    T input{{5.f, 5.f}};
    Spaceship(AnimatedSprite& sprite): Node({10.f, 10.f}, {64.f, 29.f}), sprite(sprite){
        center();
    }
    virtual void update() override {
        sprite.update();
        Node::update();
    }
    virtual void render() override {
        ClearBackground(BLACK);
        sprite.render(getRect());
    }
    void center() {
        pos = Layout::center(getRect(), Game::halfHeightRect());
    }
};

struct Player: Spaceship<Keyboard> {
    Player(AnimatedSprite& sprite): Spaceship(sprite) {}
    void visit(const KeyboardEvent& msg) override {
        pos = input.move(getRect(), Keyboard::keyCodeToOrientation(msg.keyCode));
        pos = MovementLimiter::limit(getRect(), Game::halfHeightRect());
    }
};

struct Computer: Spaceship<RandomOrientation> {
    Computer(AnimatedSprite& sprite): Spaceship(sprite) {}
    void update() override {
        pos = input.move(getRect());
        pos = MovementLimiter::limit(getRect(), Game::halfHeightRect());
    }
};

struct UFO: Node {
    AnimatedSprite& sprite;
    LeftInfiniteRandom input{{5.f, 5.f}};
    UFO(AnimatedSprite& sprite): Node({100.f, 100.f}, {40.f, 30.f}), sprite(sprite){
        input.randomize(getRect());
    }
    virtual void update() override {
        sprite.update();
        pos = input.move(getRect());
        Node::update();
    }
    virtual void render() override {
        ClearBackground(BLACK);
        sprite.render(getRect());
    }
};

struct Scene: Node {
    int scores = 0;
    float energy = 1.f;
    Node::NodeShared gameover = nullptr;
    bool done = false;
    Scene(): Node() {
        gameover = std::make_shared<GameOver>(RED);
    }
    void finish() {
        Node::NodeShared player = *children.begin();
        player->visible = false;
        for (auto& e: children) {
            e->visible = false;
        }
        gameover->visible = true;
        done = true;
    }
    void update() override {
        if (!done) {
            Node::NodeShared player = *children.begin();
            for (std::size_t i = 1; i < children.size(); ++i) {
                if (CheckCollisionRecs(player->getRect(), children[i]->getRect())) {
                    std::shared_ptr<UFO> ufo = std::dynamic_pointer_cast<UFO>(children[i]);
                    ufo->pos = ufo->input.randomize(ufo->getRect());
                    energy -= 0.1f;
                    if (energy < 0.0f) {
                        finish();
                    }
                }
            }
        } else {
            gameover->render();
        }
        Node::update();
    }
    void render() override {
        GuiSetStyle(DEFAULT, TEXT_SIZE, GetFontDefault().baseSize);
        GuiProgressBar((Rectangle){ 10, 10, Game::winWidth() - 40, 20 }, NULL, TextFormat("%i%%", (int)(energy*100)), &energy, 0.0f, 1.0f);
        DrawText(TextFormat("Pontos: %i", scores), 10, Game::halfHeightRect().height - 20, 20, RAYWHITE);
        if (done) {
            gameover->render();
        }
    }
    void visit(const ScoreUpEvent&) override {
        if (!done) scores += 1;
    }
};

void start() {
    std::size_t enemies_count = 20;
    Game game("Space Artificial Intelligence");
    AnimatedSprite ufoSprite = AnimatedSprite{"./games/space-ai/img/ufo.png",
            Frame({40.f, 30.f}, {0, 0, 5}, {6, 1}, 0.2)};
    AnimatedSprite playerSprite = AnimatedSprite{"./games/space-ai/img/spaceship.png",
            Frame({64.f, 29.f}, {0, 0, 3}, {4, 1}, 0.1)};
    // Cria a nava do jogador
    Node::NodeShared player = std::make_shared<Player>(playerSprite);
    EventManager::instance().subscribe(EventType::KeyPressed, player);
    Node::NodeShared playerScene = std::make_shared<Scene>();
    playerScene->add(player);
    // Cria inimigos
    for (size_t i = 0; i < enemies_count; ++i) {
        Node::NodeShared ufo = std::make_shared<UFO>(ufoSprite);
        playerScene->add(ufo);
    }
    EventManager::instance().subscribe(EventType::ScoreIncreased, playerScene);
    game.add(GameState::MainScreen, playerScene);
    // Cria a nava controlado pela IA
    AnimatedSprite computerSprite = AnimatedSprite{"./games/space-ai/img/spaceshipia.png",
            Frame({64.f, 29.f}, {0, 0, 3}, {4, 1}, 0.1)};
    Node::NodeShared computerScene = std::make_shared<Scene>();
    Node::NodeShared computer = std::make_shared<Computer>(computerSprite);
    computerScene->add(computer);
    // Cria inimigos
    for (size_t i = 0; i < enemies_count; ++i) {
        Node::NodeShared ufo = std::make_shared<UFO>(ufoSprite);
        computerScene->add(ufo);
    }
    EventManager::instance().subscribe(EventType::ScoreIncreased, computerScene);
    game.add(GameState::MainScreen, computerScene);
    game.run();
}

#endif // SPACEAI_H
