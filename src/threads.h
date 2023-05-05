#ifndef THREADS_H
#define THREADS_H

#include <QObject>
#include <QThread>
#include <QDebug>

class ReceiveThread : public QObject
{
public:
    explicit ReceiveThread(QObject *parent = nullptr);
    ~ReceiveThread();

    signals:

    public slots:
    void run();
    void testRun();
};

class SendThread : public QObject
{
public:
    explicit SendThread(QObject *parent = nullptr);
    ~SendThread();

    signals:

    public slots:
    void run();
    void testRun();
};



#endif