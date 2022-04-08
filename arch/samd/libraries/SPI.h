#ifndef ASMR_SAMD_LIBRARIES_SPI_H
#define ASMR_SAMD_LIBRARIES_SPI_H

#include <ASMR>
#include <api/HardwareSPI.h>

#include "core/SERCOM.h"


class SPIClass : public HardwareSPI {
public:
    SPIClass();

    virtual uint8_t transfer(uint8_t data);
    virtual uint16_t transfer16(uint16_t data);
    virtual void transfer(void *buf, size_t count);

    // Transaction Functions
    virtual void usingInterrupt(int interruptNumber);
    virtual void notUsingInterrupt(int interruptNumber);
    virtual void beginTransaction(SPISettings settings);
    virtual void endTransaction(void);

    // SPI Configuration methods
    virtual void attachInterrupt();
    virtual void detachInterrupt();

    virtual void begin();
    virtual void end();
};


#if SPI_INTERFACES_COUNT > 0
extern SPIClass SPI;
#endif
#if SPI_INTERFACES_COUNT > 1
extern SPIClass SPI1;
#endif

#endif // ASMR_SAMD_LIBRARIES_SPI_H
