#ifndef HANDLERVISITOR_H
#define HANDLERVISITOR_H

struct HandlerVisitor {
    virtual void visit(const struct KeyboardEvent&) {}
    virtual void visit(const struct MouseEvent&) {}
};

#endif // HANDLERVISITOR_H
