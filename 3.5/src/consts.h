#ifndef CONSTS_H
#define CONSTS_H

const auto BITS = 22;

const auto SLEEP_US = 10000;
const auto TIMEOUT_MS = 18;

const auto SEND_DATA = 0; // 26
const auto SEND_CLOCK = 1; // 25
const auto REC_DATA = 2; // 24
const auto REC_CLOCK = 3; // 29

enum type { CLEAR, START, CONTINUE };

#endif  // CONSTS_H