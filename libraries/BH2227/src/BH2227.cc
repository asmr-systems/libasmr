#include "BH2227.h"


/*!
 *  @brief  Instantiates a new BH2227 class using hardware SPI.
 *  @param  _cs
 *          chip select pin.
 *  @param  _spi (optional)
 *          SPI instance.
 */
BH2227::BH2227(uint8_t _cs, SPIClass* _spi)
    : _cs(_cs), _spi(_spi)
{}

/*!
 *  @brief Initializes everything.
 */
void BH2227::begin() {
    // setup hardware SPI
    pinMode(_cs, PinMode::OUTPUT);
    digitalWrite(_cs, PinStatus::HIGH); // active low

    _spi->begin();

    // configure spi for BH2227
    uint32_t sck_freq = 1000000; // 1MHz is nominal value for BH2227
    _spiSettings = SPISettings(sck_freq, BitOrder::LSBFIRST, asmr::SPI_MODE0);
}

/*!
 *  @brief  Writes a value to a single DAC output channel.
 *  @param  chan
 *          The selected channel
 *  @param  val
 *          The output value
 */
void write(uint8_t chan, uint8_t val) {
    // channel settings
    switch (chan) {
    case 0:
        chan = 0x8000; // 0b1000 left shifted
        break;
    case 1:
        chan = 0x4000; // 0b0100 left shifted
        break;
    case 2:
        chan = 0xA000; // 0b1010 left shifted
        break;
    case 3:
        chan = 0x6000; // 0b0110 left shifted
        break;
    default:
        // cannot have more than 4 channels.
        return;
    }

    _spi->beginTransaction(_spiSettings);

    digitalWrite(_cs, PinStatus::LOW);
    transfer16( (((uint16_t)chan)<<8) | (((uint16_t)val)<<4) );
    digitalWrite(_cs, PinStatus::HIGH);
}

/*!
 *  @brief  Writes values to all DAC output channels
 *  @param  vals
 *          Vector of 4 values for each respective DAC output channel
 */
void write(uint8_t vals[4]) {
    for (uint8_t i = 0; i<4; i++) {
        write(i, vals[i]);
    }
}
