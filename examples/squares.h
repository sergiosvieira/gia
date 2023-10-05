#ifndef SQUARES_H
#define SQUARES_H

#include <cmath>
#include <sstream>
#include "../include/game.h"
#include "../include/node.h"
#include "../include/gia-math.h"

struct Square : Node {
    Vector2 vel;
    Color color;
    Square(
        const Vector2 pos,
        const Vector2 length,
        const Vector2 vel = {0.0f, 0.f},
        Color color = BLACK): Node(pos, length), vel(vel), color(color){}
    void render() override {
        DrawRectangleRec(getRect(), color);
    }
    void update() override {
        pos = pos + vel;
        PtrNode parent = getParent();
        if (parent != nullptr) {
            if ((pos.x + width)  > (parent->pos.x + parent->width)
                    || pos.x < parent->pos.x) {
                vel.x *= -1.0;
            }
            if ((pos.y + height)  > (parent->pos.y + parent->height)
                    || pos.y < parent->pos.y) {
                vel.y *= -1.0;
            }
        }
        Node::update();
    }
};

using PtrSquare = std::shared_ptr<Square>;
using Vector = std::vector<PtrSquare>;

void start() {
    Game game("Exemplo 01 - Quadrados");
    std::vector<Color> colors = {
        {255, 153, 204, 255},
        {153, 255, 204, 255},
        {153, 204, 255, 255},
        {204, 255, 153, 255}
    };
    PtrSquare fase1 = std::make_shared<Square>(
        Vector2{0.0, 0.0},
        Vector2{Game::winWidth(), Game::winHeight()}
    );

    size_t size = 10;
    Vector v = Vector(size + 1, nullptr);
    v[0] = fase1;
    float d = 1.1, vel = 1.f;
    for (size_t i = 1; i <= size; ++i) {
        PtrSquare node = std::make_shared<Square>(
            Vector2{10.0, 10.0},
            Vector2{Game::winWidth()/d, Game::winHeight()/d},
            Vector2{vel, vel},
            colors[(i - 1) % 4]
        );
        v[i] = node;
        PtrNode pred = v[i - 1];
        if (pred != nullptr) {
            pred->add(v[i]);
        }
        d *= 1.1f;
        vel *= 1.1;
    }
    game.add(GameState::MainScreen, fase1);
    game.add(GameState::MainScreen, fase1);
    game.run();
}

#endif // SQUARES_H
