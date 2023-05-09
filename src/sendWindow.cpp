#include "sendWindow.h"

SendWindow::SendWindow(QWidget* parent) : Window(parent) {
    drawArea = new DrawAreaSend(this);
    setCentralWidget(drawArea);
    setWindowTitle(tr("Send"));
    createActions();
    createMenus();
}

void SendWindow::createMenus() {
    optionMenu = new QMenu(tr("&Options"), this);
    optionMenu->addAction(clearScreen);
    menuBar()->addMenu(optionMenu);
}

void SendWindow::createActions() {
    clearScreen = new QAction(tr("&Clear Screen"), this);
    clearScreen->setShortcut(tr("Ctrl+L"));
    connect(clearScreen, &QAction::triggered, drawArea, &DrawArea::clearScreen);
}