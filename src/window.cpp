#include "window.h"

Window::Window(QWidget* parent) : QMainWindow(parent) { resize(512, 512); }

Window::~Window() { delete drawArea; }
