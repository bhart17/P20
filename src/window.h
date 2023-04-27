#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPainter>
#include <QMenu>
#include <QMenuBar>

#include "drawArea.h"

class Window : public QMainWindow {
    Q_OBJECT

   public:
    explicit Window(QWidget *parent = 0);
    ~Window();

   protected:
    DrawArea *drawArea;

};

#endif  // WINDOW_H
