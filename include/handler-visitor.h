#ifndef HANDLERVISITOR_H
#define HANDLERVISITOR_H

struct HandlerVisitor {
    virtual void visit(const struct KeyboardEvent&) {}
    virtual void visit(const struct MouseEvent&) {}
    virtual void visit(const struct ChangeStateEvent&) {}
    virtual void visit(const struct ScoreUpEvent&) {}
    virtual void visit(const struct ScoreDownEvent&) {}
    virtual void visit(const struct CollisionEvent&) {}
    virtual ~HandlerVisitor(){}
};

#endif // HANDLERVISITOR_H
