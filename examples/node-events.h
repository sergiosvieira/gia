#ifndef NODEEVENTS_H
#define NODEEVENTS_H

#include "../include/game.h"
#include "../include/node.h"
#include "../include/event-manager.h"
#include "../include/keyboard-event.h"

struct Circle : Node {
    Color color = RAYWHITE;
    Circle(const Vector2& pos, float radius, Color color):
        Node(pos, Vector2{radius, radius}), color(color){}
    void render() override {
        DrawText("Click to change the circle to green", 10, 10, 20, WHITE);
        DrawText("Press any ket to change the circle to blue", 10, 40, 20, WHITE);
        DrawCircle(pos.x, pos.y, width, color);
    }
    void visit(const KeyboardEvent& msg) override {
        color = BLUE;
    }
    void visit(const MouseEvent& msg) override {
        color = GREEN;
    }
};

using PtrCircle = std::shared_ptr<Circle>;

void start() {
    Game game("Exemplo 02 - Eventos");
    PtrNode ptr = std::make_shared<Circle>(Vector2{400, 300}, 20, RED);
    EventManager::instance().subscribe(EventType::KeyPressed, ptr);
    EventManager::instance().subscribe(EventType::MouseClick, ptr);
    game.add(GameState::MainScreen, ptr);
    game.run();
}

#endif // NODEEVENTS_H
