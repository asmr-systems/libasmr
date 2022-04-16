#ifndef ASMR_DIGITAL_IO_H
#define ASMR_DIGITAL_IO_H

#include "types.h"

void pinMode(pin_size_t pinNumber, PinMode pinMode);
void digitalWrite(pin_size_t pinNumber, PinStatus status);
PinStatus digitalRead(pin_size_t pinNumber);

#endif // ASMR_DIGITAL_IO_H
