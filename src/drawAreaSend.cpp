#include "drawAreaSend.h"

DrawAreaSend::DrawAreaSend(QWidget* parent) : DrawArea(parent){
};

void DrawAreaSend::mousePressEvent(QMouseEvent* event) {
    emit startLineSig(event->position());
    startLine(event->position());
}

void DrawAreaSend::mouseMoveEvent(QMouseEvent* event) {
    emit continueLineSig(event->position());
    continueLine(event->position());
}

// void DrawAreaSend::mouseReleaseEvent(QMouseEvent* event) {
//     lines.last().append(QLine{last, event->position().toPoint()});
//     update();
// }