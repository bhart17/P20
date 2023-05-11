#ifndef THREAD_H
#define THREAD_H

#include <QDebug>
#include <QObject>
#include <QPoint>
#include <QQueue>
#include <QThread>

#include "consts.h"
#include "wiringPi.h"

// Both sendThread and receiveThread inherit from this Thread class
class Thread : public QObject {
    Q_OBJECT

   public:
    explicit Thread(QObject *parent = nullptr);
    ~Thread();
};

#endif  // THREAD_H