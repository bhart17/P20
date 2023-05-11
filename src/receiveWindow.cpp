#include "receiveWindow.h"

ReceiveWindow::ReceiveWindow(QWidget* parent) : Window(parent) {
    drawArea = new DrawArea(this);
    setCentralWidget(drawArea);
    setWindowTitle(tr("Receive"));
}