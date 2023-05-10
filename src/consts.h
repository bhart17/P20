#ifndef CONSTS_H
#define CONSTS_H

const auto SLEEP_US = 8000;

const auto SEND_DATA = 0;
const auto SEND_CLOCK = 1;
const auto REC_DATA = 2;
const auto REC_CLOCK = 3;

enum type { CLEAR, START, CONTINUE };

#endif  // CONSTS_H