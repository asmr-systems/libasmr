#ifndef ASMR_SAMD_LIBRARIES_SPI_H
#define ASMR_SAMD_LIBRARIES_SPI_H

#include <ASMR>
#include <api/HardwareSPI.h>

#include "SERCOM.h"
#include "variant.h"

// The datasheet specifies a typical SPI SCK period (tSCK) of 42 ns,
// see "Table 36-48. SPI Timing Characteristics and Requirements",
// which translates into a maximum SPI clock of 23.8 MHz.
// Conservatively, the divider is set for a 12 MHz maximum SPI clock.
#define SPI_MIN_CLOCK_DIVIDER (uint8_t)(1 + ((F_CPU - 1) / 12000000))


class SPIClass : public HardwareSPI {
public:
    SPIClass(SERCOM *sercom,
             uint8_t cipo,
             uint8_t sck,
             uint8_t copi,
             SercomSpiTXPad padTx,
             SercomRXPad padRx);

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

private:
    void init();
    void config(SPISettings settings);

    void setBitOrder(BitOrder order);
    void setDataMode(uint8_t mode);
    void setClockDivider(uint8_t div);

    SERCOM *_sercom;
    uint8_t _cipo;
    uint8_t _copi;
    uint8_t _sck;

    SercomSpiTXPad _padTx;
    SercomRXPad    _padRx;

    SPISettings settings;

    bool initialized = false;
};


#if SPI_INTERFACES_COUNT > 0
extern SPIClass SPI;
#endif
#if SPI_INTERFACES_COUNT > 1
extern SPIClass SPI1;
#endif

#endif // ASMR_SAMD_LIBRARIES_SPI_H
