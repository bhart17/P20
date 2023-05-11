#include "drawArea.h"

DrawArea::DrawArea(QWidget* parent) : QWidget(parent) {
    setAttribute(Qt::WA_StaticContents);
    setAutoFillBackground(true);
    setPalette(QPalette{Qt::white});
}

// Handles paintEvents on the DrawArea
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

// Clear the screen
void DrawArea::clearScreen() {
    emit sendSignal(CLEAR, QPoint{0, 0});
    for (QList<QList<QLine>>::iterator line = lines.begin();
         line != lines.end(); ++line) {
        // Each sublist needs to be cleared individually
        (*line).clear();
    }
    lines.clear();
    update();
}

// Save the first point of a line and setup sublist
void DrawArea::startLine(QPoint start) {
    if (lines.isEmpty()) {
        lines.append(QList<QLine>{});
    } else if (!lines.last().isEmpty()) {
        lines.append(QList<QLine>{});
    }
    last = start;
}

// Append the next point of a line to its sublist
void DrawArea::continueLine(QPoint next) {
    if (lines.isEmpty()) {
        // If we receive an invalid CONTINUE, we use it as the start of a new
        // line
        qDebug() << "⚠️ Continue received before start";
        startLine(next);
        return;
    }
    lines.last().append(QLine{last, next});
    last = next;
    update();
}

// This function handles all signals sent to DrawArea
void DrawArea::receiveHandler(int type, QPoint point) {
    switch (type) {
        case START:
            startLine(point);
            break;
        case CONTINUE:
            continueLine(point);
            break;
        case CLEAR:
            clearScreen();
            break;
        default:
            qDebug() << "⚠️ Invalid type";
            break;
    }
}
