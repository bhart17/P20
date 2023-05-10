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
    void sendHandler(int type, QPoint point);
    void run();

   private:
    void send(unsigned int data);
    unsigned int serialise(type type, QPoint point);
    QQueue<unsigned int> queue;
    int count{0};
};

#endif  // SENDTHREAD_H