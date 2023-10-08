#ifndef SPACEAI_H
#define SPACEAI_H

#include <unordered_map>
#include <functional>
#include "raygui/src/raygui.h"
#include "include/game.h"
#include "include/animation/frame.h"
#include "include/keyboard-event.h"
#include "include/event-manager.h"
#include "include/score-up-event.h"
#include "include/utils/layout.h"
#include "include/utils/randomize.h"
#include "include/animation/animated-sprite.h"

enum class Direction {
    None,
    Left,
    Right,
    Up,
    Down
};

struct Movement {
    using Map = std::unordered_map<Direction, std::function<Vector2(Vector2, float)>>;
    float speed = 5.f;
    PtrNode node = nullptr;
    virtual Vector2 move(Vector2, Direction d = Direction::None) = 0;
    virtual ~Movement(){}
    Map map = {
        {Direction::None, [](Vector2 pos, float speed){return pos;}},
        {Direction::Left, [](Vector2 pos, float speed){pos.x -= speed; return pos;}},
        {Direction::Right, [](Vector2 pos, float speed){pos.x += speed; return pos;}},
        {Direction::Up, [](Vector2 pos, float speed){pos.y -= speed; return pos;}},
        {Direction::Down, [](Vector2 pos, float speed){pos.y += speed; return pos;}},
    };
    static Direction KeyCodeToDirection(const KeyboardKey& code) {
        static std::unordered_map<KeyboardKey, Direction> map = {
            {KEY_LEFT, Direction::Left},
            {KEY_RIGHT, Direction::Right},
            {KEY_UP, Direction::Up},
            {KEY_DOWN, Direction::Down},
        };
        if (map.find(code) == map.end()) return Direction::None;
        return map[code];
    }
};

struct ByKeyboard: Movement {
    Vector2 move(Vector2 pos, Direction dir) override {
        return map[dir](pos, speed);
    }
};

struct RandomMove: Movement {
    using Map = std::unordered_map<Direction, std::function<Vector2()>>;
    Vector2 move(Vector2 pos, Direction dir) override {
        std::vector<Direction> v = {Direction::None, Direction::Left, Direction::Right, Direction::Up, Direction::Down};
        Direction d = Randomize::elements<Direction>(v);
        return map[d](pos, speed);
    }
};

template <typename T>
struct BaseSpaceship: Node {
    AnimatedSpritePtr sprite = nullptr;
    T movement;
    Direction direction = Direction::None;
    BaseSpaceship(const std::string& filename) {
        sprite = std::make_shared<AnimatedSprite>(filename.c_str(), Frame({64.f, 29.f}, {0, 0, 3}, {1, 4}, 0.1));
        initFrame();
    }
    void initFrame() {
        width = 64;
        height = 29;
    }
    void limiter() {
        const Node* parent = getParent();
        if (parent != nullptr) {
            if ((pos.x + width)  > (parent->pos.x + parent->width)) {
                pos.x = parent->width - width;
            }
            if (pos.x < parent->pos.x) {
                pos.x = parent->pos.x;
            }
            if ((pos.y + height) > (parent->pos.y + parent->height)) {
                pos.y = parent->height - height;
            }
            if (pos.y < parent->pos.y) {
                pos.y = parent->pos.y;
            }
        }
    }
    virtual void update() override {
        sprite->update();
        pos = movement.move(pos, direction);
        limiter();
        Node::update();
        direction = Direction::None;
    }
    void render() override {
        sprite->render(getRect());
    }
};

struct Spaceship: BaseSpaceship<ByKeyboard> {
    Spaceship(): BaseSpaceship("./games/space-ai/img/spaceship.png"){}
    void visit(const KeyboardEvent& msg) override {
        direction = Movement::KeyCodeToDirection(msg.keyCode);
    }
};

struct SpaceshipIA: BaseSpaceship<RandomMove> {
    SpaceshipIA(): BaseSpaceship("./games/space-ai/img/spaceshipia.png"){}
};

struct RightToLeft: Movement {
    Vector2 move(Vector2 pos, Direction dir = Direction::None) override {
        std::vector<Direction> v = {Direction::None, Direction::Left, Direction::Right, Direction::Up, Direction::Down};
        return map[dir](pos, speed);
    }
};

struct Enemy: Node {
    Texture2D texture = LoadTexture("./games/space-ai/img/ufo.png");
    RightToLeft movement;
    Frame frame;
    float wwidth = 0.f, wheight = 0.f;
    Enemy(float w, float h): wwidth(w), wheight(h) {
        initFrame();
    }
    void initFrame() {
        width = 40;
        height = 30;
        frame.cols = 1; frame.rows = 6;
        frame.width = 40;
        frame.height = 30;
        frame.firstIndex = 0; frame.lastIndex = 5;
        frame.interval = Randomize::gen(0.1f, 0.3f);
    }
    void update() override {
        frame.next();
        pos = movement.move(pos, Direction::Left);
        checkPosition();
        Node::update();
    }
    void randomize() {;
        float vwidth = wwidth * 2;
        pos.x = wwidth + Randomize::genGAP(vwidth, width);
        pos.y = Randomize::genGAP(wheight, height);
        frame.interval = Randomize::gen(0.1f, 0.3f);
        movement.speed = Randomize::gen(2.5f, 6.5f);
    }
    void checkPosition() {
        if (pos.x + width < 0) {
            randomize();
            EventManager::instance().emmit(std::make_shared<ScoreUpEvent>());
        }
    }
    void render() override {
        DrawTexturePro(texture, frame.getRect(), getRect(), {0.f, 0.f}, 0.f, WHITE);
    }
};

struct GameOver : Node {
    Color color;
    GameOver(Color color): Node(), color(color) {
    }
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


template<typename T>
struct GameScreen: Node {
    using SpaceshipPtr = std::shared_ptr<T>;
    using EnemyPtr = std::shared_ptr<Enemy>;
    using Vector = std::vector<EnemyPtr>;
    PtrNode gameover = nullptr;
    SpaceshipPtr spaceship = nullptr;
    float progressValue = 1.0f;
    int score = 0;
    size_t enemiesCount = 20;
    Vector enemies;
    bool finished = false;
    GameScreen(Color gameoverColor) {
        GuiSetStyle(PROGRESSBAR, BASE_COLOR_PRESSED, 0xCDFAD5FF);
        GuiSetStyle(PROGRESSBAR, BORDER_COLOR_NORMAL, 0xCDFAD5FF);
        GuiSetStyle(PROGRESSBAR, BORDER_COLOR_FOCUSED, 0xCDFAD5FF);
        width = Game::winWidth();
        height = Game::winHeight() / 2;
        spaceship = std::make_shared<T>();
        float px = Layout::center(width, spaceship->width);
        float py = Layout::center(height, spaceship->height);
        spaceship->pos = {px, py};
        add(spaceship);
        enemies.reserve(enemiesCount);
        for (size_t i = 0; i < enemiesCount; ++i) {
            EnemyPtr e = std::make_shared<Enemy>(width, height);
            e->randomize();
            add(e);
            enemies.push_back(e);
        }
        gameover = std::make_shared<GameOver>(gameoverColor);
        gameover->width = width;
        gameover->height = height;
        gameover->visible = false;
        add(gameover);
    }
    void hide() {
        spaceship->visible = false;
        for (auto& e: enemies) {
            e->visible = false;
        }
        gameover->visible = true;
    }
    void update() override {
        if (finished) return;
        for (auto& e: enemies) {
            if (CheckCollisionRecs(spaceship->getRect(), e->getRect())) {
                if (progressValue > 0.f) {
                    progressValue -= 0.05f;
                } else {
                    progressValue -= 0.0f;
                    finished = true;
                    hide();
                }
                e->randomize();
            }
        }
        Node::update();
    }
    void render() override {
        ClearBackground(BLACK);
        GuiSetStyle(DEFAULT, TEXT_SIZE, GetFontDefault().baseSize);
        GuiProgressBar((Rectangle){ 10, 10, Game::winWidth() - 40, 20 }, NULL, TextFormat("%i%%", (int)(progressValue*100)), &progressValue, 0.0f, 1.0f);
        DrawText(TextFormat("Pontos: %i", score), 10, height - 20, 20, RAYWHITE);
    }
    void visit(const ScoreUpEvent&) override {
        if (finished) return;
        score += 1;
    }
};

void start() {
    Game game("Space Artificial Intelligence");
    game.add(GameState::MainScreen, std::make_shared<GameScreen<Spaceship>>(RED));
    game.add(GameState::MainScreen, std::make_shared<GameScreen<SpaceshipIA>>(MAROON));
    HandlerPtr human = game.get(GameState::MainScreen, 0);
    HandlerPtr artif = game.get(GameState::MainScreen, 1);
    EventManager::instance().subscribe(EventType::KeyPressed, human);
    EventManager::instance().subscribe(EventType::ScoreUp, human);
    EventManager::instance().subscribe(EventType::ScoreUp, artif);
    game.run();
}

#endif // SPACEAI_H
