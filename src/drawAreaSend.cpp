#include "drawAreaSend.h"

DrawAreaSend::DrawAreaSend(QWidget* parent) : DrawArea(parent){};

void DrawAreaSend::mousePressEvent(QMouseEvent* event) {
    lines.append(QList<QLine>{});
    last = event->position().toPoint();
}

void DrawAreaSend::mouseMoveEvent(QMouseEvent* event) {
    // min distance between points
    if ((event->position() - last).manhattanLength() > 10) {
        lines.last().append(QLine{last, event->position().toPoint()});
        last = event->position().toPoint();
        update();
    }
}

void DrawAreaSend::mouseReleaseEvent(QMouseEvent* event) {
    lines.last().append(QLine{last, event->position().toPoint()});
    update();
}