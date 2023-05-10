#ifndef THREAD_H
#define THREAD_H

#include <QDebug>
#include <QObject>
#include <QPoint>
#include <QQueue>
#include <QThread>

#include "wiringPi.h"

#include "consts.h"

class Thread : public QObject {
    Q_OBJECT

   public:
    explicit Thread(QObject *parent = nullptr);
    ~Thread();
};

#endif  // THREAD_H