#include "../include/node.h"

#include <cstdlib>
#include "../include/gia-math.h"
#include "../include/event.h"
#include "../include/game.h"

Node::Node(const Vector2& pos,
           const Vector2& length):
    pos(pos), width(length.x), height(length.y) {
}

void Node::add(PtrNode node) {
    node->parent = std::shared_ptr<Node>(this);
    children.push_back(node);
}

Rectangle Node::getRect() const {
    return {pos.x, pos.y, width, height};
}

void Node::update() {
    for (PtrNode node: children) {
        node->pos = node->pos + pos;
        node->update();
        node->pos = node->pos - pos;
    }
}

const PtrNode Node::getParent() {
    return parent;
}

void Node::draw() {
    render();
    for (PtrNode node: children) {
        node->pos = node->pos + pos;
        node->draw();
        node->pos = node->pos - pos;
    }
}

void Node::handle(struct Event& event) {
    event.accept(*this);
    for (PtrNode node: children) {
        node->handle(event);
    }
}
