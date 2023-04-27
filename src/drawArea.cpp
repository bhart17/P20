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