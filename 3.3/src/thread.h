#ifndef THREAD_H
#define THREAD_H

#include <QDebug>
#include <QObject>
#include <QPoint>
#include <QQueue>
#include <QThread>
#include <algorithm>

#include "consts.h"

class Thread : public QObject {
    Q_OBJECT

   public:
    explicit Thread(QObject *parent = nullptr);
    ~Thread();

   protected:
    inline static QQueue<unsigned int> queue;
};

#endif  // THREAD_H