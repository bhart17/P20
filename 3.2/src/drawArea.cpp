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
    emit send(serialise(CLEAR, QPoint{0, 0}));
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
        qDebug() << "⚠️ Continue received before start";
        startLine(next);
        return;
    }
    lines.last().append(QLine{last, next});
    last = next;
    update();
}

void DrawArea::receiveHandler(type type, QPoint point) {
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

void DrawArea::deserialise(unsigned int data) {
    receiveHandler((type)(data & 3),
                   QPoint{(int)(data >> 12), (int)((data >> 2) & 1023)});
}

void DrawArea::receive(unsigned int data) { deserialise(data); }

unsigned int DrawArea::serialise(type type, QPoint point) {
    // bits:
    // 1-2: command (START, CONTINUE)
    // 3-12: y coord
    // 13-22: x coord
    // 0b1010101001001100110001
    return type | (std::clamp((int)point.y(), 0, 1023) << 2) |
           (std::clamp((int)point.x(), 0, 1023) << 12);
}