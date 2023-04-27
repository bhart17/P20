#include "window.h"

Window::Window(QWidget* parent)
    : QMainWindow(parent), drawArea(new DrawArea(this)) {
    setCentralWidget(drawArea);
    setWindowTitle(tr("Send"));
    resize(500, 500);
}

Window::~Window() { delete drawArea; }
