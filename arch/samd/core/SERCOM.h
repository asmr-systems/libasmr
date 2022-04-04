#ifndef ASMR_CORE_SERCOM_H
#define ASMR_CORE_SERCOM_H

#include <samd.h>

class SERCOM {
public:
    SERCOM(Sercom* s);

    //:::: UART ::::
    // TODO

    //:::: SPI ::::
    void initSPI();
    // TODO

    //:::: WIRE (I2C) ::::
    // TODO
};

#endif // ASMR_CORE_SERCOM_H
