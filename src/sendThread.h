#ifndef SENDTHREAD_H
#define SENDTHREAD_H

#include <QCoreApplication>
#include <QQueue>

#include "thread.h"

class SendThread : public Thread {
    Q_OBJECT

   public:
    std::atomic<bool> finished = false;

   public slots:
    void testRun();
    void sendStartLine(QPointF start);
    void sendContinueLine(QPointF next);
    void sendClearScreen();
    void run();

    //    signals:
    //     void send(unsigned int data);

   private:
    void send(unsigned int data);
    unsigned int serialise(type type, QPointF data);
    unsigned int serialise(type type);
    QQueue<unsigned int> queue;
};

#endif  // SENDTHREAD_H