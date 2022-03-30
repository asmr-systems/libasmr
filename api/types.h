#ifndef ASMR_TYPES_H
#define ASMR_TYPES_H

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
