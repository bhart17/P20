#include <QApplication>

#include "receiveThread.h"
#include "receiveWindow.h"
#include "sendThread.h"
#include "sendWindow.h"

int main(int argc, char* argv[]) {
    // setup GPIO interface - uncomment when needed
    // needs to run with root via sudo in terminal.
    // wiringPiSetup();
    // pinMode(SEND_DATA, OUTPUT);
    // pinMode(SEND_CLOCK, OUTPUT);
    // pinMode(REC_DATA, INPUT);
    // pinMode(REC_CLOCK, INPUT);
    // pullUpDnControl(REC_DATA, PUD_DOWN);
    // pullUpDnControl(REC_CLOCK, PUD_DOWN);
    // digitalWrite(SEND_CLOCK, true);

    QApplication app(argc, argv);
    SendWindow send;
    ReceiveWindow receive;

    QObject::connect(&send, &Window::closed, &app,
                     &QApplication::closeAllWindows);
    QObject::connect(&receive, &Window::closed, &app,
                     &QApplication::closeAllWindows);

    QThread::currentThread()->setObjectName("Main Thread");

    // To start the receiver thread:
    auto recThread = new ReceiveThread;
    QThread threadR;
    threadR.setObjectName("Receive Thread");
    recThread->moveToThread(&threadR);
    QObject::connect(&threadR, &QThread::started, recThread,
                     &ReceiveThread::run);
    threadR.start();

    // To start the sender thread:
    auto sendThread = new SendThread;
    QThread threadS;
    threadS.setObjectName("Send Thread");
    sendThread->moveToThread(&threadS);
    QObject::connect(&threadS, &QThread::started, sendThread, &SendThread::run);
    threadS.start();

    QObject::connect((DrawAreaSend*)send.drawArea, &DrawAreaSend::sendSignal,
                     sendThread, &SendThread::sendHandler);
    QObject::connect(recThread, &ReceiveThread::receiveSignal, receive.drawArea,
                     &DrawArea::receiveHandler);

    send.show();
    receive.show();

    qDebug() << "Starting event loop...";
    auto ret = app.exec();
    qDebug() << "Event loop stopped.";

    recThread->finished = true;
    sendThread->finished = true;
    threadR.quit();
    threadS.quit();
    threadR.wait();
    threadS.wait();

    return ret;
}