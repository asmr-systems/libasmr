#include "variant.h"
#include "wiring.h"


const PinTableEntry g_PinTable[] = {
    { PORTA, 14, PIO_DIGITAL }, // 0
    { PORTA, 15, PIO_SERCOM }, // 1
    { PORTA, 16, PIO_SERCOM }, // 2
    { PORTA, 17, PIO_SERCOM }, // 3


    // 0..13 - Digital pins
    // ----------------------
    // 0/1 - SERCOM/UART (Serial1)
    // { PORTA, 11, PIO_SERCOM, (PIN_ATTR_DIGITAL), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_11 }, // RX: SERCOM0/PAD[3]
    // { PORTA, 10, PIO_SERCOM, (PIN_ATTR_DIGITAL), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_10 }, // TX: SERCOM0/PAD[2]
};
