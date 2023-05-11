#ifndef DRAWAREA_H
#define DRAWAREA_H

#include <QColorDialog>
#include <QDebug>
#include <QMouseEvent>
#include <QPainter>
#include <QWidget>

#include "consts.h"

class DrawArea : public QWidget {
    Q_OBJECT

   public:
    DrawArea(QWidget *parent = nullptr);

   public slots:
    void receiveHandler(int type, QPoint point);
    void clearScreen();
    void pickPenColour();

   signals:
    void sendSignal(int type, QPoint point);

   protected:
    void startLine(QPoint start);
    void continueLine(QPoint next);
    void paintEvent(QPaintEvent *event);
    QPoint last;
    QList<QList<QLine>> lines;
    QColor penColour{Qt::black};
};

#endif  // DRAWAREA_H