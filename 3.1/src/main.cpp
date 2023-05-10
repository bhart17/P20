#include <QApplication>

#include "receiveWindow.h"
#include "sendWindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    SendWindow send;
    ReceiveWindow receive;

    QObject::connect(&send, &Window::closed, &app,
                     &QApplication::closeAllWindows);
    QObject::connect(&receive, &Window::closed, &app,
                     &QApplication::closeAllWindows);

    QObject::connect(send.drawArea, &DrawArea::send, receive.drawArea,
                     &DrawArea::receive);

    send.show();
    receive.show();

    qDebug() << "Starting event loop...";
    auto ret = app.exec();
    qDebug() << "Event loop stopped.";

    return ret;
}