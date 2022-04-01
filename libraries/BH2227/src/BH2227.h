#ifndef ASMR_BH2227_H
#define ASMR_BH2227_H

#include "ASMR.h"

#include <SPI.h>

/*!
 *  @brief  Class that writes 8-bit values to the BH2227 DAC.
 */
class BH2227 {
public:
    BH2227(uint8_t _cs, SPIClass* = &SPI);

    void begin();

    void write(uint8_t chan, uint8_t val);
    void write(uint8_t val1, uint8_t val2, uint8_t val3, uint8_t val4);

private:
    SPIClass *_spi;
    SPISettings _spiSettings;
    uint8_t _cs;
};

#endif // ASMR_BH2227FV_H
