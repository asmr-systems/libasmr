#ifndef SAMD10_VARIANT_H
#define SAMD10_VARIANT_H

// include SAMD10 CMSIS headers
#include <samd10.h>

// define all SAMD10 and sub-variant related stuff here.

/** Frequency of the board main oscillator (32.768kHz)*/
#define VARIANT_MAINOSC		(32768ul)

// TODO change these defines into constants...why not?
/** Frequency of board main clock 48MHz  */
#define VARIANT_MCK (48000000ul)  // Main Clock


// aliasing defines so that samd10 matches with samd21
#define FUSES_OSC32K_CAL_ADDR FUSES_OSC32K_ADDR
#define FUSES_OSC32K_CAL_Pos  FUSES_OSC32K_Pos
#define FUSES_OSC32K_CAL_Msk  FUSES_OSC32K_Msk

#endif // SAMD10_VARIANT_H
