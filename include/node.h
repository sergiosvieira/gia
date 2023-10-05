#ifndef NODE_H
#define NODE_H

#include <memory>
#include <vector>
#include "raylib.h"
#include "handler.h"
#include "handler-visitor.h"

struct Node;
using PtrNode = std::shared_ptr<Node>;
using Children = std::vector<PtrNode>;

struct Node: Handler, HandlerVisitor {
    Vector2 pos = {};
    float width = 0.f, height = 0.f;
    Node(){}
    Node(const Vector2& pos, const Vector2& length);
    virtual ~Node(){}
    void add(PtrNode);
    Rectangle getRect() const;
    virtual void update();
    virtual void render() = 0;
    const PtrNode getParent();
    virtual void handle(struct Event& msg) override;
private:
    PtrNode parent = nullptr;
    Children children;
    friend struct Game;
    void draw();
};

#endif // NODE_H
