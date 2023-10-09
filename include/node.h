#ifndef NODE_H
#define NODE_H

#include <memory>
#include <vector>
#include "raylib.h"
#include "handler.h"
#include "handler-visitor.h"

struct Node;
using NodePtr = std::shared_ptr<Node>;
using Vector = std::vector<NodePtr>;

struct Node : std::enable_shared_from_this<Node>, Handler, HandlerVisitor {
    std::weak_ptr<Node> parent;
    Vector children;
    Vector2 pos;
    float width;
    float height;
    bool visible = true;
    Node();
    Node(const Vector2& pos, const Vector2& length);
    virtual ~Node();
    void add(NodePtr node);
    Rectangle getRect() const;
    void handle(const struct Event& event) override;
    virtual void update();
    virtual void render() = 0;
private:
    friend struct Game;
    void draw();
};

#endif // NODE_H
