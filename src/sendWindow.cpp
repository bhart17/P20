#include "sendWindow.h"

SendWindow::SendWindow(QWidget* parent) : Window(parent) {
    drawArea = new DrawAreaSend(this);
    setCentralWidget(drawArea);
    setWindowTitle(tr("Send"));
    createActions();
    createMenus();
}

// Adds an 'options' menu from which the screen can be cleared
void SendWindow::createMenus() {
    optionMenu = new QMenu(tr("&Options"), this);
    optionMenu->addAction(clearScreen);
    menuBar()->addMenu(optionMenu);
}

// Screen can alsop be cleared by pressing CTRL and L keys
void SendWindow::createActions() {
    clearScreen = new QAction(tr("&Clear Screen"), this);
    clearScreen->setShortcut(tr("Ctrl+L"));
    connect(clearScreen, &QAction::triggered, drawArea, &DrawArea::clearScreen);
}