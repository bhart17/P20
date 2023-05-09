#ifndef SENDTHREAD_H
#define SENDTHREAD_H

#include <QCoreApplication>
#include <QQueue>

#include "thread.h"

class SendThread : public Thread {
    Q_OBJECT

   public:
    std::atomic<bool> finished{false};

   public slots:
    void sendStartLine(QPoint start);
    void sendContinueLine(QPoint next);
    void sendClearScreen();
    void run();

   private:
    void send(unsigned int data);
    unsigned int serialise(type type, QPoint data);
    unsigned int serialise(type type);
    QQueue<unsigned int> queue;
    int count{0};
};

#endif  // SENDTHREAD_H