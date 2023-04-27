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

void DrawArea::clearScreen() {
    // potentially this is a memory leak
    lines.clear();
    update();
}

void DrawArea::startLine(QPointF start) {
    lines.append(QList<QLine>{});
    last = start.toPoint();
}

void DrawArea::continueLine(QPointF next) {
    if ((next - last).manhattanLength() > 10) {
        lines.last().append(QLine{last, next.toPoint()});
        last = next.toPoint();
        update();
    }
}