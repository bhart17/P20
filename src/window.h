#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QMouseEvent>
#include <QPainter>

#include "drawArea.h"

class Window : public QMainWindow {
    Q_OBJECT

   public:
    explicit Window(QWidget *parent = 0);
    ~Window();
    DrawArea *drawArea;
    void closeEvent(QCloseEvent *event);

   signals:
    void closed();
};

#endif  // WINDOW_H
