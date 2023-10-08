#ifndef DINOAI_H
#define DINOAI_H

#include "include/game.h"
#include "raygui/src/raygui.h"
#include "include/animation/animated-sprite.h"
#include "include/sprite.h"
#include "include/physics/left-infinite.h"
#include "include/physics/left-inf-random.h".h"


enum class Action {
    None,
    Jump,
    Crounch
};

struct Cactus: Node {
    SpritePtr sprite = nullptr;
    Frame frame;
    LeftInfiniteRandom moviment;
    explicit Cactus(const std::string& filename, const Frame& frame): Node(),
        sprite(std::make_shared<Sprite>(filename)), frame(frame){
        width = frame.width;
        height = frame.height;
        pos.y = (Game::winHeight() / 2.f) - frame.height - 12;
        pos = moviment.move(getRect(), Physics::Orientation::Left);
    }
    ~Cactus(){}
    void update() override {
        pos = moviment.move(getRect(), Physics::Orientation::Left);
        Node::update();
    }
    void render() override {
        sprite->renderRect(frame.getRect(), getRect());
    }
};

struct Ground: Node {
    Sprite sprite = Sprite{"./games/dino-ai/img/ground.png"};
    LeftInfinite movement;
    Ground(): Node() {
        width = sprite.texture->width;
        height = sprite.texture->height;
        pos.y = (Game::winHeight() / 2.f) - height * 2;
    }
    ~Ground(){}
    void update() override {
        pos = movement.move(getRect(), Physics::Orientation::None);
    }
    void render() override {
        sprite.render(getRect());
    }
};

struct BaseDino: Node {
    AnimatedSprite run{"./games/dino-ai/img/dino-01.png", Frame({48.f, 45.f}, {1, 1, 3}, {1, 5}, 0.1)};
    AnimatedSprite crounch{"./games/dino-ai/img/dino-02.png", Frame({57.f, 45.f}, {0, 0, 1}, {1, 2}, 0.1)};
    BaseDino(): Node() {
        width = run.frame.width;
        height = run.frame.height;
    }
    ~BaseDino(){}
    void update() override {
        run.update();
        Node::update();
    }
    void render() override {
        ClearBackground(LIGHTGRAY);
        run.render(getRect());
    }
};

template <typename Player>
struct GameScreen: Node {
    using PlayerPtr = std::shared_ptr<Player>;
    using CactusPtr = std::shared_ptr<Cactus>;
    using Vector = std::vector<CactusPtr>;
    PlayerPtr player = nullptr;
    Vector cactus = {
        std::make_shared<Cactus>("./games/dino-ai/img/cactus-big.png", Frame({25.f, 50.f}, {0, 0, 5}, {1, 6}, 0.f)),
        std::make_shared<Cactus>("./games/dino-ai/img/cactus-small.png", Frame({17.f, 35.f}, {0, 0, 5}, {1, 6}, 0.f)),
    };
    PtrNode gameover = nullptr;
    int score = 0.f;
    bool finished = false;

    GameScreen() {
        width = Game::winWidth();
        height = Game::winHeight() / 2.f;
        add(std::make_shared<Ground>());
        player = std::make_shared<Player>();
        player->pos.x = player->width;
        player->pos.y = height - player->height * 1.3f;
        add(player);
        for (auto& c: cactus) {
            add(c);
        }
    }
    ~GameScreen(){}
    void update() override {
        if (finished) return;
        Node::update();
    }
    void render() override {
        DrawText(TextFormat("Pontos: %i", score), 10, 10, 20, BLACK);
    }
    void visit(const ScoreUpEvent&) override {
        if (finished) return;
        score += 1;
    }
};

void start() {
    Game game("Dino Artificial Intelligence");
    game.add(GameState::MainScreen, std::make_shared<GameScreen<BaseDino>>());
    game.add(GameState::MainScreen, std::make_shared<GameScreen<BaseDino>>());
    game.run();
}

#endif // DINOAI_H
