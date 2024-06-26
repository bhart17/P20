#ifndef SENDWINDOW_H
#define SENDWINDOW_H

#include <QMenu>
#include <QMenuBar>

#include "drawAreaSend.h"
#include "window.h"

class SendWindow : public Window {
    Q_OBJECT

   public:
    explicit SendWindow(QWidget *parent = 0);
    QAction *clearScreen;

   private:
    void createMenus();
    void createActions();
    QMenu *optionMenu;
};

#endif  // SENDWINDOW_H