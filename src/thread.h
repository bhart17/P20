#ifndef THREAD_H
#define THREAD_H

#include <QDebug>
#include <QObject>
#include <QPoint>
#include <QQueue>
#include <QThread>
#include <algorithm>

// #include "wiringPi.h"

const auto SLEEP_MS = 50;

const int SEND_DATA = 0;
// const int SEND_CLOCK = 1;
const int REC_DATA = 2;
// const int REC_CLOCK = 3;

enum type { START, CONTINUE, CLEAR };

class Thread : public QObject {
    Q_OBJECT

   public:
    explicit Thread(QObject *parent = nullptr);
    ~Thread();

   protected:
    inline static bool pin{false};
};

#endif  // THREAD_H