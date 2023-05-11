#include "window.h"

//set beginning size of window to be 512x512
Window::Window(QWidget* parent) : QMainWindow(parent) { resize(512, 512); }

Window::~Window() { delete drawArea; }

void Window::closeEvent(QCloseEvent* event) {
    emit closed();
    event->accept();
}

//Window can be closed by pressing Q key on keyboard
void Window::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Q) {
        emit closed();
        event->accept();    
    }
}
