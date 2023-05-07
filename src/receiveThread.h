#ifndef RECEIVETHREAD_H
#define RECEIVETHREAD_H

#include "thread.h"

class ReceiveThread : public Thread {
   public slots:
    void testRun();
};

#endif