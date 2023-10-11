#ifndef SQUARES_H
#define SQUARES_H

#include <cmath>
#include <sstream>
#include "../include/game.h"
#include "../include/node.h"
#include "../include/gia-math.h"

struct Square : Node {
    Vector2 vel = {};
    Color color = WHITE;
    Square(const Vector2& pos = {0.f, 0.f},
           const Node::Dimensions& dim = {0.f, 0.f},
           Node::NodeShared parent = nullptr,
           const Vector2& vel = {0.f, 0.f},
           Color color = BLACK): Node(pos, dim, parent), vel(vel), color(color){}
    void render() override {
        ClearBackground(BLACK);
        DrawRectangleRec(getRect(), color);
    }
    void update() override {
        pos = pos + vel;
        NodeShared parent = getParent();
        if (parent == nullptr) return;
        if ((pos.x + dim.width)  > (parent->pos.x + parent->dim.width)
                || pos.x < parent->pos.x) {
            vel.x *= -1.0;
        }
        if ((pos.y + dim.height)  > (parent->pos.y + parent->dim.height)
                || pos.y < parent->pos.y) {
            vel.y *= -1.0;
        }
        Node::update();
    }
};

void start() {    
    Game game("Exemplo 01 - Quadrados");
    std::vector<Color> colors = {
        {255, 153, 204, 255},
        {153, 255, 204, 255},
        {153, 204, 255, 255},
        {204, 255, 153, 255}
    };
    Node::NodeShared ptr = std::make_shared<Square>(
        Vector2{0.0, 0.0},
        Node::Dimensions{Game::winWidth(), Game::winHeight()}
    );

    size_t size = 10;
    auto previous = ptr;
    float d = 1.1, vel = 1.f;
    for (size_t i = 1; i < size ; ++i) {
        Node::NodeShared node = std::make_shared<Square>(
            Vector2{10.0, 10.0},
            Node::Dimensions{Game::winWidth()/d, Game::winHeight()/d},
            previous,
            Vector2{vel, vel},
            colors[(i - 1) % 4]
        );
        previous->add(node);
        previous = node;
        d *= 1.1f;
        vel *= 1.1;
    }
    game.add(GameState::MainScreen, ptr);
    game.add(GameState::MainScreen, ptr);
    game.run();
}

#endif // SQUARES_H
