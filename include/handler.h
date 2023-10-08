#ifndef HANDLER_H
#define HANDLER_H

#include <memory>

struct Handler {
    virtual void handle(struct Event& msg) = 0;
    virtual ~Handler(){}
};

using HandlerPtr = std::shared_ptr<Handler>;

#endif // HANDLER_H
