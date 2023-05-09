#include "drawArea.h"

DrawArea::DrawArea(QWidget* parent) : QWidget(parent) {
    setAttribute(Qt::WA_StaticContents);
    setAutoFillBackground(true);
    setPalette(QPalette{Qt::white});
}

void DrawArea::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QPen pen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pen);
    for (QList<QList<QLine>>::const_iterator line = lines.begin();
         line != lines.end(); ++line) {
        painter.drawLines((*line).toVector());
    }
    event->accept();
}

void DrawArea::clearScreen() {
    for (QList<QList<QLine>>::iterator line = lines.begin();
         line != lines.end(); ++line) {
        (*line).clear();
    }
    lines.clear();
    update();
}

void DrawArea::startLine(QPoint start) {
    if (lines.isEmpty()) {
        lines.append(QList<QLine>{});
    } else if (!lines.last().isEmpty()) {
        lines.append(QList<QLine>{});
    }
    last = start;
}

void DrawArea::continueLine(QPoint next) {
    if (lines.isEmpty()) {
        qDebug() << "Continue received before start";
        return;
    }
    lines.last().append(QLine{last, next});
    last = next;
    update();
}