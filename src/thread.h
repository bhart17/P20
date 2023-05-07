#ifndef THREAD_H
#define THREAD_H

#include <QDebug>
#include <QObject>
#include <QThread>

class Thread : public QObject {
    Q_OBJECT

   public:
    explicit Thread(QObject *parent = nullptr);
    ~Thread();

   public slots:
    void run();
};

#endif  // THREAD_H