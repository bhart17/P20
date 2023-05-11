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
    QPen pen(penColour, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pen);
    QList<QList<QLine>>::const_iterator line = lines.begin();
    QList<QColor>::const_iterator colour = colours.begin();
    for (; line != lines.end() && colour != colours.end(); ++line, ++colour) {
        pen.setColor(*colour);
        painter.setPen(pen);
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
    colours.clear();
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
    colours.append(penColour);
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
        case COLOUR: {
            auto red = (point.x() & 0b111111) << 2;
            auto green = (((point.x() & 0b1111000000) >> 4) | ((point.y() & 0b11) << 4));
            auto blue = (point.y() & 0b11111100) >> 2;
            penColour = QColor{qRgb(qRed(red), qGreen(green), qBlue(blue))};
            qDebug() << red << green << blue << penColour;
            break;
        }
        default:
            qDebug() << "⚠️ Invalid type";
            break;
    }
}

void DrawArea::pickPenColour() {
    QColor newColour = QColorDialog::getColor(penColour);
    if (newColour.isValid()) {
        penColour = newColour;
        emit sendSignal(
            COLOUR,
            QPoint{(penColour.red() >> 2) | ((penColour.green() >> 2) << 6),
                   (penColour.green() >> 6) | ((penColour.blue() >> 2) << 2)});
    }
}