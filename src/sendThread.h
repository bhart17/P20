#ifndef SENDTHREAD_H
#define SENDTHREAD_H

#include "thread.h"

class SendThread : public Thread {
   public slots:
    void testRun();
};

#endif // SENDTHREAD_H