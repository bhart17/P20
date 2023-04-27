#include "window.h"

Window::Window(QWidget* parent) : QMainWindow(parent) { resize(500, 500); }

Window::~Window() { delete drawArea; }
