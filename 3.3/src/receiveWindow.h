#ifndef RECEIVEWINDOW_H
#define RECEIVEWINDOW_H

#include "drawArea.h"
#include "window.h"

class ReceiveWindow : public Window {
    Q_OBJECT

   public:
    explicit ReceiveWindow(QWidget *parent = 0);
};

#endif  // RECEIVEWINDOW_H