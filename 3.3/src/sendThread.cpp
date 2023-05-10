#include "sendThread.h"

unsigned int SendThread::serialise(type type, QPoint point) {
    // bits:
    // 1-2: command (START, CONTINUE)
    // 3-12: y coord
    // 13-22: x coord
    // 0b1010101001001100110001
    return type | (std::clamp((int)point.y(), 0, 1023) << 2) |
                (std::clamp((int)point.x(), 0, 1023) << 12);
}

void SendThread::sendHandler(int type_, QPoint point) {
    queue.enqueue(serialise((type)type_, point));
}