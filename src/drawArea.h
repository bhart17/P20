#ifndef DRAWAREA_H
#define DRAWAREA_H

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
    void receiveHandler(type type, QPoint point);
    void clearScreen();

   protected:
    void startLine(QPoint start);
    void continueLine(QPoint next);
    void paintEvent(QPaintEvent *event);
    QPoint last;
    QList<QList<QLine>> lines;
};

#endif  // DRAWAREA_H