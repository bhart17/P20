#ifndef RECEIVEWINDOW_H
#define RECEIVEWINDOW_H

#include "window.h"
#include "drawArea.h"

class ReceiveWindow : public Window {
    Q_OBJECT

   public:
    explicit ReceiveWindow(QWidget *parent = 0);

   private:
    void createMenus();
    void createActions();
    QMenu *optionMenu;
    QAction *clearScreen;
};

#endif