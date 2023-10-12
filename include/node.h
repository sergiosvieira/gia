#ifndef NODE_H
#define NODE_H

#include <memory>
#include <vector>
#include "raylib.h"
#include "handler.h"
#include "handler-visitor.h"

struct Node : std::enable_shared_from_this<Node>, Handler, HandlerVisitor {
    using NodeShared = std::shared_ptr<Node>;
    using Vector = std::vector<NodeShared>;
    struct Dimensions {
        float width = 0.f;
        float height = 0.f;
    };
    Vector2 pos = {};
    Dimensions dim ;
    bool visible = true;
    Node(const Vector2& pos = {}, const Dimensions& dim = {0.f, 0.f}, NodeShared parent = nullptr);
    virtual ~Node();
    virtual void add(NodeShared node);
    Rectangle getRect() const;
    NodeShared getParent();
    void handle(const struct Event& event) override;
    virtual void update();
    virtual void render() = 0;
protected:
    Vector children;
    NodeShared parent = nullptr;
    friend struct Game;
    void draw();
};

#endif // NODE_H
