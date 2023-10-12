#ifndef JUMP_H
#define JUMP_H

#include "include/physics/physics.h"
#include "include/physics/gravity.h"

struct Jump: Physics {
    enum class Action {
        None,
        Jumping,
        Stand
    };
    Action currentAction = Action::None;
    GravityPtr gravity = nullptr;
    Jump(Vector2 velocity): Physics(velocity) {
        gravity = std::make_shared<Gravity>(velocity);
    }
    ~Jump(){}
    float max = 8.f;
    float accel = max;
    virtual Vector2 move(const Rectangle& rect, Orientation = Orientation::None, const Rectangle& grect = {}) override {
        Vector2 pos = {rect.x, rect.y};
        if (currentAction == Action::Jumping) {
            pos.y -= gravity->vel.y + accel;
            accel -= 0.4f;
        }
        if (Physics::collides({pos.x, pos.y, rect.width, rect.height}, grect)) {
            pos.y = grect.y - (rect.height - 2.f);
            reset();
            accel = max;
        } else pos = gravity->move({pos.x, pos.y, rect.width, rect.height}, Orientation::None, grect);
        return pos;
    }
    void reset() {
        currentAction = Jump::Action::Stand;
    }
    void jump() {
        currentAction = Jump::Action::Jumping;
    }
    bool isJumping() {
        return (currentAction == Jump::Action::Jumping);
    }
};

using JumpPtr = std::shared_ptr<Jump>();

#endif // JUMP_H
