#ifndef THREAD_H
#define THREAD_H

#include <QDebug>
#include <QObject>
#include <QThread>
#include <QPointF>
#include <algorithm>

enum type { START, CONTINUE, CLEAR };

class Thread : public QObject {
    Q_OBJECT

   public:
    explicit Thread(QObject *parent = nullptr);
    ~Thread();

   public slots:
    void run();
};

#endif  // THREAD_H