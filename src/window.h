#ifndef WINDOW_H
#define WINDOW_H

#include <QPainter>
#include <QMainWindow>
#include <QMouseEvent>

#include "drawArea.h"

// namespace Ui {
// class Window;
// }


class Window : public QMainWindow {
    Q_OBJECT

   public:
    explicit Window(QWidget *parent = 0);
    ~Window();

//    protected:
//     void paintEvent(QPaintEvent* event);
//     void mouseReleaseEvent(QMouseEvent * event);
//     void mouseMoveEvent(QMouseEvent *event);
//     QPoint last;
//     QList<QLine> lines;

   private:
    DrawArea *drawArea;
    // Ui::Window *ui;
};

#endif  // WINDOW_H
