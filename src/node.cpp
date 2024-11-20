#include "../include/node.h"

#include <cstdlib>
#include "event.h"
#include "gia-math.h"

Node::Node(const Vector2& pos,
           const Dimensions& dim,
           NodeShared parent): pos(pos),  dim(dim), parent(parent) {

}

Node::~Node(){
    children.clear();
}

void Node::add(NodeShared node) {
    children.emplace_back(node);
}

void Node::handle(const struct Event& event) {
    event.accept(*this);
    for (auto node : children) {
        node->handle(event);
    }
}

Rectangle Node::getRect() const {
    return {pos.x, pos.y, dim.width, dim.height};
}

Node::NodeShared Node::getParent() {
    return parent;
}

void Node::update() {
    for (auto& node: children) {
        node->pos = node->pos + pos;
        node->update();
        node->pos = node->pos - pos;
    }
}

void Node::draw() {
    if (visible) render();
    for (auto& node: children) {
        node->pos = node->pos + pos;
        if (node->visible) node->draw();
        node->pos = node->pos - pos;
    }
}
