#ifndef DINOAI_H
#define DINOAI_H

#include "include/game.h"
#include "raygui/src/raygui.h"
#include "include/animation/animated-sprite.h"
#include "include/sprite.h"
#include "include/physics/left-infinite.h"
#include "include/physics/left-inf-random.h"
#include "include/physics/jump.h"
#include "include/keyboard-event.h"
#include "include/event-manager.h"
#include "include/physics/jump-random.h"
#include "include/gia-math.h"
#include "include/score-up-event.h"


enum class Action {
    None,
    Jump,
    Crounch
};

struct GameOver : Node {
    Color color;
    GameOver(Color color): Node(), color(color) {}
    void render() override {
        GuiSetStyle(DEFAULT, TEXT_SIZE, 150);
        GuiSetStyle(DEFAULT, TEXT_SPACING, 10);
        GuiSetStyle( DEFAULT, TEXT_COLOR_NORMAL, 0xFFFFFFFF);
        GuiSetStyle(LABEL, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
        ClearBackground(color);
        GuiSetStyle(DEFAULT, TEXT_SIZE, 100);
        GuiLabel({0, 0, width, height}, "GAME OVER");
    }
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
        pos.x = Game::winWidth();/*moviment.move(getRect(), {}, Physics::Orientation::Left);*/
    }
    ~Cactus(){}
    void update() override {
        pos = moviment.move(getRect(), {}, Physics::Orientation::Left);
        if (pos.x + width - moviment.speed < 0) {
            EventManager::instance().emmit(std::make_shared<ScoreUpEvent>());
        }
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
        pos = movement.move(getRect(), {}, Physics::Orientation::None);
    }
    void render() override {
        sprite.render(getRect());
    }
};

template<typename T>
struct BaseDino: Node {
    AnimatedSprite run{"./games/dino-ai/img/dino-01.png", Frame({48.f, 45.f}, {1, 1, 3}, {1, 5}, 0.1)};
    AnimatedSprite crounch{"./games/dino-ai/img/dino-02.png", Frame({57.f, 45.f}, {0, 0, 1}, {1, 2}, 0.1)};
    Rectangle groundRect;
    using Vector = std::vector<PhysicsPtr>;
    const Vector2 velocity = {0.f, 3.f};
    std::shared_ptr<T> movement = nullptr;
    explicit BaseDino(Rectangle ground): Node(), groundRect(ground) {
        width = run.frame.width;
        height = run.frame.height;
        groundRect.y += 8.f;
        movement = std::make_shared<T>(Vector2{0.f, 8.f});
    }
    ~BaseDino(){}
    void update() override {
        run.update();
        pos = movement->move(getRect(), groundRect);
        Node::update();
    }
    void render() override {
        ClearBackground(LIGHTGRAY);
        run.render(getRect());
    }
};

struct Human : BaseDino<Jump> {
    Human(Rectangle rect): BaseDino<Jump>(rect){}
    void visit(const KeyboardEvent& msg) override {
        if (msg.keyCode == KEY_SPACE && !movement->isJumping()) {
            movement->jump();
        }
    }
};

struct DinoAI: BaseDino<JumpRandom> {
    DinoAI(Rectangle rect): BaseDino<JumpRandom>(rect){
    }
};

template <typename Player>
struct GameScreen: Node {
    using PlayerPtr = std::shared_ptr<Player>;
    using CactusPtr = std::shared_ptr<Cactus>;
    using Vector = std::vector<CactusPtr>;
    PlayerPtr player = nullptr;
    NodePtr gameover = nullptr;
    Vector cactus = {
        std::make_shared<Cactus>("./games/dino-ai/img/cactus-big.png", Frame({25.f, 50.f}, {0, 0, 5}, {1, 6}, 0.f)),
        std::make_shared<Cactus>("./games/dino-ai/img/cactus-small.png", Frame({17.f, 35.f}, {0, 0, 5}, {1, 6}, 0.f)),
    };
    int score = 0.f;
    bool finished = false;
    NodePtr ground = nullptr;
    GameScreen(Color color): Node(),
        gameover(std::make_shared<GameOver>(color)),
        ground(std::make_shared<Ground>()) {
        width = Game::winWidth();
        height = Game::winHeight() / 2.f;
        makePlayer();
        children.emplace_back(ground);
        makeCacti();
        makeGameOver();
    }
    ~GameScreen(){}
    void makePlayer() {
        player = std::make_shared<Player>(ground->getRect());
        player->pos.x = player->width;
        player->pos.y = height - player->height * 1.3f;
        children.emplace_back(player);
    }
    void makeCacti() {
        for (auto& c: cactus) {
            children.emplace_back(c);
        }
    }
    void makeGameOver() {
        gameover->width = width;
        gameover->height = height;
        gameover->visible = false;
        children.emplace_back(gameover);
    }
    void finish() {
        player->visible = false;
        for (auto& e: cactus) {
            e->visible = false;
        }
        gameover->visible = true;
        ground->visible = false;
        finished = true;
    }
    void update() override {
        if (finished) return;
        for (auto& c: cactus) {
            if (Physics::collides(padding(player->getRect(), 10.f, 5.f), c->getRect())) {
                finish();
            }
        }
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
    game.add(GameState::MainScreen, std::make_shared<GameScreen<Human>>(RED));
    HandlerPtr human = game.get(GameState::MainScreen, 0);
    EventManager::instance().subscribe(EventType::KeyPressed, human);
    EventManager::instance().subscribe(EventType::ScoreIncreased, human);
    game.add(GameState::MainScreen, std::make_shared<GameScreen<DinoAI>>(MAROON));
    game.run();
}

#endif // DINOAI_H
