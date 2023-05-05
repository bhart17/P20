#ifndef SERIAL_H
#define SERIAL_H

#include <QObject>
#include <QPointF>
#include <algorithm>
#include <QDebug>

enum type { START, CONTINUE, CLEAR };

class Serial : public QObject {
    Q_OBJECT

   public:
    Serial();

   public slots:
    void sendStartLine(QPointF start);
    void sendContinueLine(QPointF next);
    void sendClearScreen();

   signals:
    void startLineSig(QPointF start);
    void continueLineSig(QPointF next);
    void clearScreenSig();

   private:
    void send(unsigned int data);
    void receive(unsigned int data);
    unsigned int serialise(type type, QPointF data);
    unsigned int serialise(type type);
    void deserialise(unsigned int data);
};

#endif  // SERIAL_H