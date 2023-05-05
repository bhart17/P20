#ifndef THREADS_H
#define THREADS_H

#include <QDebug>
#include <QObject>
#include <QThread>

class ReceiveThread : public QObject {
    Q_OBJECT

   public:
    explicit ReceiveThread(QObject *parent = nullptr);
    ~ReceiveThread();

   signals:

   public slots:
    void run();
    void testRun();
};

class SendThread : public QObject {
    Q_OBJECT

   public:
    explicit SendThread(QObject *parent = nullptr);
    ~SendThread();

   signals:

   public slots:
    void run();
    void testRun();
};

#endif