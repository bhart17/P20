#include "drawArea.h"

DrawArea::DrawArea(QWidget* parent) : QWidget(parent) {
    setAttribute(Qt::WA_StaticContents);
}

void DrawArea::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    QPen pen(Qt::black, 3);
    painter.setPen(pen);
    for (QList<QList<QLine>>::const_iterator line = lines.begin();
         line != lines.end(); ++line) {
        painter.drawLines(*line);
    }
    event->accept();
}

void DrawArea::mousePressEvent(QMouseEvent* event) {
    lines.append(QList<QLine>{});
    last = event->position().toPoint();
    // this->update();
}

void DrawArea::mouseMoveEvent(QMouseEvent* event) {
    // min distance between points
    if ((event->position() - last).manhattanLength() > 10) {
        lines.last().append(QLine{last, event->position().toPoint()});
        last = event->position().toPoint();
        this->update();
    }
}

void DrawArea::mouseReleaseEvent(QMouseEvent* event) {
    lines.last().append(QLine{last, event->position().toPoint()});
    this->update();
}