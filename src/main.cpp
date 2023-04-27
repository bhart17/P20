#include <pthread.h>
// #include <wiringPi.h>

#include <QApplication>
#include <QDebug>
#include <QObject>

#include "receiveWindow.h"
#include "sendWindow.h"

void* worker(void* thread_id) {
    long tid = (long)thread_id;
    // do something....
    qDebug() << "Worker thread " << tid << "started.";

    // end thread
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    // setup GPIO interface - uncomment when needed
    // needs to run with root via sudo in terminal.
    // wiringPiSetup();
    // pinMode(0, OUTPUT);

    // setup Qt GUI
    QApplication a(argc, argv);
    SendWindow send;
    ReceiveWindow receive;

    // not sure which syntax is best
    // QObject::connect(send.drawArea, &DrawArea::startLineSig,
    //                  receive.drawArea, &DrawArea::startLine);
    // QObject::connect(send.drawArea, &DrawArea::continueLineSig,
    //                  receive.drawArea, &DrawArea::continueLine);
    QObject::connect(send.drawArea, SIGNAL(startLineSig(QPointF)),
                     receive.drawArea, SLOT(startLine(QPointF)));
    QObject::connect(send.drawArea, SIGNAL(continueLineSig(QPointF)),
                     receive.drawArea, SLOT(continueLine(QPointF)));
    QObject::connect(send.clearScreen, SIGNAL(triggered()), receive.drawArea,
                     SLOT(clearScreen()));

    send.show();
    receive.show();

    // starting worker thread(s)
    pthread_t worker_thread;
    int rc = pthread_create(&worker_thread, NULL, worker, (void*)1);
    if (rc) {
        qDebug() << "Unable to start worker thread.";
        exit(1);
    }

    // start window event loop
    qDebug() << "Starting event loop...";
    int ret = a.exec();
    qDebug() << "Event loop stopped.";

    // cleanup pthreads <- what does this mean? this exits the main thread (surely not intended)
    // pthread_exit(NULL);

    // exit
    return ret;
}
