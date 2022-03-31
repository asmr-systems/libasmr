#include "ASMR.h"

static volatile uint32_t _ulTickCount = 0;



unsigned long millis() {
    return _ulTickCount;
}

unsigned long micros() {
    // TODO implement me
}
