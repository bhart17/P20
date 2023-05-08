#include "window.h"

Window::Window(QWidget* parent) : QMainWindow(parent) { resize(512, 512); }

Window::~Window() { delete drawArea; }

void Window::closeEvent(QCloseEvent* event) {
    emit closed();
    event->accept();
}

void Window::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Q) {
        emit closed();
        event->accept();    
    }
}
