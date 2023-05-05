#include "serial.h"

Serial::Serial() {}

void Serial::receive(unsigned int data) {
    // real recieve code here
    deserialise(data);
}

void Serial::send(unsigned int data) {
    // real send code here
    receive(data);
}

unsigned int Serial::serialise(type type, QPointF data) {
    // bits:
    // 1-2: command (START, CONTINUE)
    // 3-12: y coord
    // 13-22: x coord
    // 0b1010101001001100110001
    return type | (std::clamp((int)data.y(), 0, 1024) << 2) |
           (std::clamp((int)data.x(), 0, 1024) << 12);
}

unsigned int Serial::serialise(type type) {
    // only for CLEAR
    return type;
}

void Serial::deserialise(unsigned int data) {
    switch (data & 3) {
        case START:
            emit startLineSig(
                QPointF{(qreal)(data >> 12), (qreal)((data >> 2) & 1023)});
            break;
        case CONTINUE:
            emit continueLineSig(
                QPointF{(qreal)(data >> 12), (qreal)((data >> 2) & 1023)});
            break;
        case CLEAR:
            emit clearScreenSig();
            break;
        default:
            qDebug() << "fell through";
            break;
    }
}

void Serial::sendStartLine(QPointF start) { send(serialise(START, start)); }
void Serial::sendContinueLine(QPointF next) { send(serialise(CONTINUE, next)); }
void Serial::sendClearScreen() { send(serialise(CLEAR)); }