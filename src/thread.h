#ifndef THREAD_H
#define THREAD_H

#include <QDebug>
#include <QMutex>
#include <QObject>
#include <QPoint>
#include <QQueue>
#include <QThread>
#include <algorithm>

enum type { START, CONTINUE, CLEAR };

class Thread : public QObject {
    Q_OBJECT

   public:
    explicit Thread(QObject *parent = nullptr);
    ~Thread();
    // inline static QQueue<unsigned int> queue;
    inline static bool pin;
    inline static bool clock = 0;

    //    public slots:
    //     void run();
   protected:
    // inline static QMutex mutex;
};

#endif  // THREAD_H