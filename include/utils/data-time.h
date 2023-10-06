#ifndef DATATIME_H
#define DATATIME_H

bool timer(float currentTime, float& lastTime, float interval) {
    if (currentTime - lastTime > interval) {
        return true;
    }
    return false;
}

#endif // DATATIME_H
