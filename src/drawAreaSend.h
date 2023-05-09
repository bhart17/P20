#ifndef DRAWAREASEND_H
#define DRAWAREASEND_H

#include "drawArea.h"

class DrawAreaSend : public DrawArea {
    Q_OBJECT

   public:
    DrawAreaSend(QWidget *parent = nullptr);

   protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    // void mouseReleaseEvent(QMouseEvent *event);
};

#endif  // DRAWAREASEND_H