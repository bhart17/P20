#ifndef SENDWINDOW_H
#define SENDWINDOW_H

#include "window.h"
#include "drawAreaSend.h"

class SendWindow : public Window {
    Q_OBJECT

   public:
    explicit SendWindow(QWidget *parent = 0);

   private:
    void createMenus();
    void createActions();
    QMenu *optionMenu;
    QAction *clearScreen;
};

#endif