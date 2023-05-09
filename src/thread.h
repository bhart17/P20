#ifndef THREAD_H
#define THREAD_H

#include <QDebug>
#include <QObject>
#include <QPoint>
#include <QQueue>
#include <QThread>
#include <algorithm>

#include "wiringPi.h"

const auto SLEEP_MS = 8;

const int SEND_DATA = 0;
const int SEND_CLOCK = 1;
const int REC_DATA = 2;
const int REC_CLOCK = 3;

enum type { CLEAR, START, CONTINUE };

class Thread : public QObject {
    Q_OBJECT

   public:
    explicit Thread(QObject *parent = nullptr);
    ~Thread();
};

#endif  // THREAD_H