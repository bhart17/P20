#ifndef DRAWAREA_H
#define DRAWAREA_H

#include <QPainter>
#include <QMouseEvent>
#include <QWidget>

class DrawArea : public QWidget {
    Q_OBJECT

   public:
    DrawArea(QWidget *parent = nullptr);

   protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    QPoint last;
    QList<QList<QLine>> lines;
};

#endif  // DRAWAREA_H