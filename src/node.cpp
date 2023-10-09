#include "../include/node.h"

#include <cstdlib>
#include "include/event.h"
#include "include/gia-math.h"

Node::Node(){}

Node::Node(const Vector2& pos, const Vector2& length)
    : pos(pos), width(length.x), height(length.y) {}

Node::~Node(){
    children.clear();
}

void Node::add(NodePtr node) {
    node->parent = shared_from_this();
    children.emplace_back(node);
}

void Node::handle(const struct Event& event) {
    event.accept(*this);
    for (const NodePtr& node : children) {
        node->handle(event);
    }
}

Rectangle Node::getRect() const {
    return {pos.x, pos.y, width, height};
}

void Node::update() {
    for (NodePtr& node: children) {
        node->pos = node->pos + pos;
        node->update();
        node->pos = node->pos - pos;
    }
}

void Node::draw() {
    if (visible) render();
    for (NodePtr& node: children) {
        node->pos = node->pos + pos;
        if (node->visible) node->draw();
        node->pos = node->pos - pos;
    }
}
