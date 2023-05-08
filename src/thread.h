#ifndef THREAD_H
#define THREAD_H

#include <QDebug>
#include <QObject>
#include <QPointF>
#include <QQueue>
#include <QThread>
#include <algorithm>

enum type { START, CONTINUE, CLEAR };

class Thread : public QObject {
    Q_OBJECT

   public:
    explicit Thread(QObject *parent = nullptr);
    ~Thread();
    static QQueue<unsigned int> queue;

    //    public slots:
    //     void run();
};

#endif  // THREAD_H