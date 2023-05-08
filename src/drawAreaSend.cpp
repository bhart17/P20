#include "drawAreaSend.h"

DrawAreaSend::DrawAreaSend(QWidget* parent) : DrawArea(parent){};

void DrawAreaSend::mousePressEvent(QMouseEvent* event) {
    emit startLineSig(event->pos());
    startLine(event->pos());
}

void DrawAreaSend::mouseMoveEvent(QMouseEvent* event) {
    if ((event->pos() - last).manhattanLength() > 25) {
        emit continueLineSig(event->pos());
        continueLine(event->pos());
    }
}

// void DrawAreaSend::mouseReleaseEvent(QMouseEvent* event) {
//     lines.last().append(QLine{last, event->position().toPoint()});
//     update();
// }