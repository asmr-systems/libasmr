#ifndef ASMR_TYPES_H
#define ASMR_TYPES_H

#include <cstdint>

using pin_size_t = uint8_t;

enum class PinStatus {
    LOW,
    HIGH,
    CHANGE,
    FALLING,
    RISING,
};

enum class PinMode {
    INPUT,
    OUTPUT,
    INPUT_PULLUP,
    INPUT_PULLDOWN,
    OUTPUT_OPENDRAIN,
};

enum class BitOrder {
    LSBFIRST,
    MSBFIRST,
};

#endif // ASMR_TYPES_H
