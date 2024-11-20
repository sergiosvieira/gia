#ifndef NODETESTS_H
#define NODETESTS_H

#include <iostream>
#include <cassert>
#include "node.h"

struct ConcreteNode : Node {
    ConcreteNode(NodePtr parent = nullptr) {} // Construtor padrão
    void render() override {
    }
};

void testNodeAddChild() {
    ConcreteNode parent;
    ConcreteNode child1{std::make_shared<ConcreteNode>(parent)};

    assert(parent.children[0].get() == &child1);
}




void start() {
    testNodeAddChild();
    std::cout << "Todos os testes passaram!" << std::endl;
}



#endif // NODETESTS_H
