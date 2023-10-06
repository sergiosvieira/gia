#ifndef SPACEAI_H
#define SPACEAI_H

#include <unordered_map>
#include <functional>
#include "raygui/src/raygui.h"
#include "include/game.h"
#include "include/animation/frame.h"
#include "include/keyboard-event.h"
#include "include/event-manager.h"
#include "include/utils/layout.h"
#include "include/utils/randomize.h"

enum class Direction {
    None,
    Left,
    Right,
    Up,
    Down
};

struct Movement {
    const float speed = 5.f;
    PtrNode node = nullptr;
    virtual Vector2 move(Vector2, Direction) = 0;
    virtual ~Movement(){}
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
    using Map = std::unordered_map<Direction, std::function<Vector2()>>;
    Vector2 move(Vector2 pos, Direction dir) override {
        static Map map = {
            {Direction::None, [&](){return pos;}},
            {Direction::Left, [&](){pos.x -= speed; return pos;}},
            {Direction::Right, [&](){pos.x += speed; return pos;}},
            {Direction::Up, [&](){pos.y -= speed; return pos;}},
            {Direction::Down, [&](){pos.y += speed; return pos;}},
        };
        return map[dir]();
    }
};

struct ByIA: Movement {
    using Map = std::unordered_map<Direction, std::function<Vector2()>>;
    Vector2 move(Vector2 pos, Direction dir) override {
        static Map map = {
            {Direction::None, [&](){return pos;}},
            {Direction::Left, [&](){pos.x -= speed; return pos;}},
            {Direction::Right, [&](){pos.x += speed; return pos;}},
            {Direction::Up, [&](){pos.y -= speed; return pos;}},
            {Direction::Down, [&](){pos.y += speed; return pos;}},
        };
        std::vector<Direction> v = {Direction::None, Direction::Left, Direction::Right, Direction::Up, Direction::Down};
        Direction d = Randomize::elements<Direction>(v);
        return map[d]();
    }
};

template <typename T>
struct BaseSpaceship: Node {
    Texture2D texture;
    Frame frame;
    T movement;
    Direction direction = Direction::None;
    BaseSpaceship(const std::string& filename) {
        texture = LoadTexture(filename.c_str());
        initFrame();
    }
    void initFrame() {
        width = 64;
        height = 29;
        frame.cols = 1; frame.rows = 4;
        frame.width = 64;
        frame.height = 29;
        frame.firstIndex = 0; frame.lastIndex = 3;
        frame.interval = 0.1;
    }
    void limiter() {
         PtrNode parent = getParent();
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
        frame.next();
        pos = movement.move(pos, direction);
        limiter();
        Node::update();
        direction = Direction::None;
    }
    void render() override {
        DrawTexturePro(texture, frame.getRect(), getRect(), {0.f, 0.f}, 0.f, WHITE);
    }
};

struct Spaceship: BaseSpaceship<ByKeyboard> {
    Spaceship(): BaseSpaceship("./games/space-ai/img/spaceship.png"){}
    void visit(const KeyboardEvent& msg) override {
        direction = Movement::KeyCodeToDirection(msg.keyCode);
    }
};

struct SpaceshipIA: BaseSpaceship<ByIA> {
    SpaceshipIA(): BaseSpaceship("./games/space-ai/img/spaceshipia.png"){}
};


template<typename T>
struct GameScreen: Node {
    using SpaceshipPtr = std::shared_ptr<T>;
    SpaceshipPtr spaceship = nullptr;
    float progressValue = 1.0f;
    GameScreen() {
        width = Game::winWidth();
        height = Game::winHeight() / 2;
        spaceship = std::make_shared<T>();
        float px = Layout::center(width, spaceship->width);
        float py = Layout::center(height, spaceship->height);
        spaceship->pos = {px, py};
        add(spaceship);
    }
    void render() override {
        ClearBackground(BLACK);
        GuiProgressBar((Rectangle){ 10, 10, Game::winWidth() - 40, 20 }, NULL, TextFormat("%i%%", (int)(progressValue*100)), &progressValue, 0.0f, 1.0f);
    }
};


void start() {
    Game spaceAI("Space Artificial Intelligence");
    spaceAI.add(GameState::MainScreen, std::make_shared<GameScreen<Spaceship>>());
    spaceAI.add(GameState::MainScreen, std::make_shared<GameScreen<SpaceshipIA>>());
    HandlerPtr node = spaceAI.get(GameState::MainScreen, 0);
    EventManager::instance().subscribe(EventType::KeyPressed, node);
    spaceAI.run();
}

#endif // SPACEAI_H
