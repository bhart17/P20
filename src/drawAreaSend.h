#ifndef DRAWAREASEND_H
#define DRAWAREASEND_H

#include <QWidget>

#include "drawArea.h"

class DrawAreaSend : public DrawArea {
    Q_OBJECT

   public:
    DrawAreaSend(QWidget *parent = nullptr);

   signals:
    void startLineSig(QPointF start);
    void continueLineSig(QPointF next);
    // void clearScreenSig();

   protected:
    void mousePressEvent(QMouseEvent *event);
    // void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
};

#endif  // DRAWAREASEND_H