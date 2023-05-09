#ifndef DRAWAREASEND_H
#define DRAWAREASEND_H

#include "drawArea.h"

class DrawAreaSend : public DrawArea {
    Q_OBJECT

   public:
    DrawAreaSend(QWidget *parent = nullptr);

   signals:
    void sendSignal(type type, QPoint point);
    // void startLineSig(QPoint start);
    // void continueLineSig(QPoint next);

   protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    // void mouseReleaseEvent(QMouseEvent *event);
};

#endif  // DRAWAREASEND_H