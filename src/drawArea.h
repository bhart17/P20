#ifndef DRAWAREA_H
#define DRAWAREA_H

#include <QMouseEvent>
#include <QPainter>
#include <QWidget>

class DrawArea : public QWidget {
    Q_OBJECT

   public:
    DrawArea(QWidget *parent = nullptr);

   public slots:
    void clearScreen();

   protected:
    void paintEvent(QPaintEvent *event);
    void startLine(QPointF start);
    void continueLine(QPointF next);
    QPoint last;
    QList<QList<QLine>> lines;
};

#endif  // DRAWAREA_H