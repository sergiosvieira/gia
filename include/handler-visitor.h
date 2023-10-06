#ifndef HANDLERVISITOR_H
#define HANDLERVISITOR_H

struct HandlerVisitor {
    virtual void visit(const struct KeyboardEvent&) {}
    virtual void visit(const struct MouseEvent&) {}
    virtual void visit(const struct ChangeStateEvent&) {}
};

#endif // HANDLERVISITOR_H
