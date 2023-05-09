#include "drawAreaSend.h"

DrawAreaSend::DrawAreaSend(QWidget* parent) : DrawArea(parent){};

void DrawAreaSend::mousePressEvent(QMouseEvent* event) {
    emit sendSignal(START, event->pos());
    startLine(event->pos());
    event->accept();
}

void DrawAreaSend::mouseMoveEvent(QMouseEvent* event) {
    if ((event->pos() - last).manhattanLength() > 20) {
        emit sendSignal(CONTINUE, event->pos());
        continueLine(event->pos());
    }
    event->accept();
}

// void DrawAreaSend::mouseReleaseEvent(QMouseEvent* event) {
//     // emit continueLineSig(event->pos());
//     emit sendSignal(event->pos());
//     continueLine(event->pos());
//     event->accept();
// }