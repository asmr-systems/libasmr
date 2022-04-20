#ifndef ASMR_HARDWARE_SPI_H
#define ASMR_HARDWARE_SPI_H

#include <cstdint>
#include "types.h"


typedef enum {
    SPI_MODE0 = 0,
    SPI_MODE1 = 1,
    SPI_MODE2 = 2,
    SPI_MODE3 = 3,
} SPIMode;


class SPISettings {
public:
    SPISettings() {}

    SPISettings(uint32_t clockFreq, BitOrder bitOrder, SPIMode dataMode)
        : clockFreq(clockFreq), bitOrder(bitOrder), dataMode(dataMode)
        {}

    bool operator==(const SPISettings& rhs) const
        {
            if ((this->clockFreq == rhs.clockFreq) &&
                (this->bitOrder == rhs.bitOrder) &&
                (this->dataMode == rhs.dataMode)) {
                return true;
            }
            return false;
        }

    bool operator!=(const SPISettings& rhs) const
        {
            return !(*this == rhs);
        }

    uint32_t getClockFreq() const {
        return clockFreq;
    }
    SPIMode getDataMode() const {
        return dataMode;
    }
    BitOrder getBitOrder() const {
        return (bitOrder);
    }
private:
    uint32_t clockFreq = 4000000;
    BitOrder bitOrder  = BitOrder::MSBFIRST;
    SPIMode dataMode   = SPI_MODE0;

    friend class HardwareSPI;
};

const SPISettings DEFAULT_SPI_SETTINGS = SPISettings();

class HardwareSPI {
public:
    virtual ~HardwareSPI() { }

    virtual uint8_t transfer(uint8_t data) = 0;
    virtual uint16_t transfer16(uint16_t data) = 0;
    virtual void transfer(void *buf, size_t count) = 0;

    // Transaction Functions
    virtual void usingInterrupt(int interruptNumber) = 0;
    virtual void notUsingInterrupt(int interruptNumber) = 0;
    virtual void beginTransaction(SPISettings settings) = 0;
    virtual void endTransaction(void) = 0;

    // SPI Configuration methods
    virtual void attachInterrupt() = 0;
    virtual void detachInterrupt() = 0;

    virtual void begin() = 0;
    virtual void end() = 0;
};

#endif // ASMR_HARDWARE_SPI_H
