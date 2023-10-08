#include "../include/node.h"

#include <cstdlib>
#include "../include/gia-math.h"
#include "../include/event.h"

Node::Node(const Vector2& pos,
           const Vector2& length):
    pos(pos), width(length.x), height(length.y) {
}

Node::~Node(){
    children.erase(children.begin(), children.end());
}

void Node::add(PtrNode node) {
    node->parent = this;
    children.emplace_back(node);
}

Rectangle Node::getRect() const {
    return {pos.x, pos.y, width, height};
}

void Node::update() {
    for (PtrNode& node: children) {
        node->pos = node->pos + pos;
        node->update();
        node->pos = node->pos - pos;
    }
}

const Node* Node::getParent() {
    return parent;
}

void Node::draw() {
    if (visible) render();
    for (PtrNode node: children) {
//        node->pos = node->pos + pos;
        if (node->visible) node->draw();
//        node->pos = node->pos - pos;
    }
}

void Node::handle(struct Event& event) {
    event.accept(*this);
    for (PtrNode node: children) {
        node->handle(event);
    }
}
