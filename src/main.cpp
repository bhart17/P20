#include <pthread.h>
// #include <wiringPi.h>

#include <QApplication>
#include <QDebug>
#include <QObject>
#include <QThread>


#include "receiveWindow.h"
#include "sendWindow.h"
#include "threads.h"

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

    //also my thread code vv
    QThread::currentThread()->setObjectName("Main Thread");
    qDebug() << "Starting" << QThread::currentThread();

    //To start the receiver thread:
    ReceiveThread *recThread = new ReceiveThread();
    QThread threadR;
    threadR.setObjectName("Receive Thread :)");
    recThread->moveToThread(&threadR);
    QObject::connect(&threadR, &QThread::started, recThread, &ReceiveThread::testRun);   //when the thread is started, recThread calls the run function from the ReceiveThread class
    threadR.start();

    //To start the sender thread:
    SendThread *sendThread = new SendThread();
    QThread threadS;
    threadS.setObjectName("Send Thread :)");
    sendThread->moveToThread(&threadS);
    QObject::connect(&threadS, &QThread::started, sendThread, &SendThread::testRun);   //when the thread is started, recThread calls the run function from the ReceiveThread class
    threadS.start();

    //for troubleshooting and testing purposes on main thread:
    qDebug() << "Doing prep work" << QThread::currentThread();
    for (int i=0; i<10; i++){
        qDebug() << "Working Hard" << QString::number(i) << QThread::currentThread();
        QThread::currentThread()->msleep(500);
    }
    qDebug() << "Finished at 1am" << QThread::currentThread();



    //my thread code segment ends here ˆˆ

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
    
    threadR.quit();
    threadS.exit();
//    thread.exit();            useless because the thread is apparently immortal
    qDebug() << QThread::currentThread()->isRunning();
    qDebug() << threadR.isRunning();
    qDebug() << threadS.isRunning();


    //my thread code here:

    // cleanup pthreads <- what does this mean? this exits the main thread (surely not intended)
    // pthread_exit(NULL);

    // exit
    return ret;
}
