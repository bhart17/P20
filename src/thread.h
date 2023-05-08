#ifndef THREAD_H
#define THREAD_H

#include <QDebug>
#include <QMutex>
#include <QObject>
#include <QPoint>
#include <QQueue>
#include <QThread>
#include <algorithm>

#include "wiringPi.h"

const int SEND_DATA = 0;
const int SEND_CLOCK = 1;
const int REC_DATA = 2;
const int REC_CLOCK = 3;

enum type { START, CONTINUE, CLEAR };

class Thread : public QObject {
    Q_OBJECT

   public:
    explicit Thread(QObject *parent = nullptr);
    ~Thread();
    // inline static QQueue<unsigned int> queue;
    // inline static bool pin;
    // inline static bool clock = 0;

    //    public slots:
    //     void run();
   protected:
    // inline static QMutex mutex;
};

#endif  // THREAD_H