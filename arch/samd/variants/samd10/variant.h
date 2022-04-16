#ifndef SAMD10_VARIANT_H
#define SAMD10_VARIANT_H

// include SAMD10 CMSIS headers
#include <samd10.h>

// define all SAMD10 and sub-variant related stuff here.

// TODO change these defines into constants...why not?
#define VARIANT_MCK (48000000ul)  // Main Clock

enum PortGroup {
    PORTA = 0,
    PORTB = 1,
}

struct PinTable {
    PortGroup  port;
    uint32_t   pin;
};

// Pin table instantiated in variant.cc
extern const PinTable g_PinTable[];

#endif // SAMD10_VARIANT_H
