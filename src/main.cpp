// #include <wiringPi.h>

#include <QApplication>
#include <QDebug>
#include <QObject>
#include <QThread>

#include "receiveThread.h"
#include "receiveWindow.h"
#include "sendThread.h"
#include "sendWindow.h"

int main(int argc, char* argv[]) {
    // setup GPIO interface - uncomment when needed
    // needs to run with root via sudo in terminal.
    // wiringPiSetup();
    // pinMode(0, OUTPUT);

    // setup Qt GUI
    QApplication a(argc, argv);
    SendWindow send;
    ReceiveWindow receive;

    QObject::connect(&send, &Window::closed, &a,
                     &QApplication::closeAllWindows);
    QObject::connect(&receive, &Window::closed, &a,
                     &QApplication::closeAllWindows);

    // also my thread code vv
    QThread::currentThread()->setObjectName("Main Thread");
    qDebug() << "Starting" << QThread::currentThread();

    // To start the receiver thread:
    ReceiveThread* recThread = new ReceiveThread();
    QThread threadR;
    threadR.setObjectName("Receive Thread :)");
    recThread->moveToThread(&threadR);
    QObject::connect(&threadR, &QThread::started, recThread,
                     &ReceiveThread::run);  // when the thread is started,
                                            // recThread calls the run function
                                            // from the ReceiveThread class
    // QObject::connect(&threadR, &QThread::finished, recThread,
    //                  &QObject::deleteLater);
    // QObject::connect(&receive, &Window::closed, recThread,
    //                  &QObject::deleteLater);
    threadR.start();

    // To start the sender thread:
    SendThread* sendThread = new SendThread();
    QThread threadS;
    threadS.setObjectName("Send Thread :)");
    sendThread->moveToThread(&threadS);
    QObject::connect(
        &threadS, &QThread::started, sendThread,
        &SendThread::run);  // when the thread is started, recThread calls
    // the run function from the ReceiveThread class
    // QObject::connect(&threadS, &QThread::finished, sendThread,
    //                  &QObject::deleteLater);
    // QObject::connect(&send, &Window::closed, sendThread,
    // &QObject::deleteLater);
    threadS.start();

    // for troubleshooting and testing purposes on main thread:
    // qDebug() << "Doing prep work" << QThread::currentThread();
    // for (int i = 0; i < 10; i++) {
    //     qDebug() << "Working Hard" << QString::number(i)
    //              << QThread::currentThread();
    //     QThread::currentThread()->msleep(500);
    // }
    // qDebug() << "Finished at 1am" << QThread::currentThread();

    // my thread code segment ends here ˆˆ

    QObject::connect(send.drawArea, SIGNAL(startLineSig(QPointF)), sendThread,
                     SLOT(sendStartLine(QPointF)));
    QObject::connect(send.drawArea, SIGNAL(continueLineSig(QPointF)),
                     sendThread, SLOT(sendContinueLine(QPointF)));
    QObject::connect(send.clearScreen, &QAction::triggered, sendThread,
                     &SendThread::sendClearScreen);

    QObject::connect(recThread, &ReceiveThread::startLineSig, receive.drawArea,
                     &DrawArea::startLine);
    QObject::connect(recThread, &ReceiveThread::continueLineSig,
                     receive.drawArea, &DrawArea::continueLine);
    QObject::connect(recThread, &ReceiveThread::clearScreenSig,
                     receive.drawArea, &DrawArea::clearScreen);

    send.show();
    receive.show();

    // start window event loop
    qDebug() << "Starting event loop...";
    int ret = a.exec();
    qDebug() << "Event loop stopped.";

    recThread->finished = true;
    sendThread->finished = true;
    threadR.quit();
    threadS.quit();
    threadR.wait();
    threadS.wait();

    // qDebug() << QThread::currentThread()->isRunning();
    // qDebug() << threadR.isRunning();
    // qDebug() << threadS.isRunning();

    return ret;
}
