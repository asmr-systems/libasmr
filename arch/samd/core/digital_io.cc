#include <ASMR>


void pinMode(pin_size_t pinNumber, PinMode pinMode) {
    // TODO figure out how to detect if the pin is not a pin
    // from the pin mapping.

    // set pin configuration
    switch (pinMode) {
    case PinMode::INPUT:
        PORT->Group[g_PinTable[pin].port].PINCFG[g_PinTable[pin].pin].reg = (uint8_t)(PORT_PINCFG_INEN);
        PORT->Group[g_PinTable[pin].port].DIRCLR[g_PinTable[pin].pin].reg = (uint32_t)(1<<g_PinTable[pin].pin);
        break;
    case PinMode::OUTPUT:
        // set to output with input enabled (for reading current value of outputs)
        PORT->Group[g_PinTable[pin].port].PINCFG[g_PinTable[pin].pin].reg = (uint8_t)(PORT_PINCFG_INEN);
        PORT->Group[g_PinTable[pin].port].DIRSET[g_PinTable[pin].pin].reg = (uint32_t)(1<<g_PinTable[pin].pin);
        break;
    case PinMode::INPUT_PULLUP:
        PORT->Group[g_PinTable[pin].port].PINCFG[g_PinTable[pin].pin].reg = (uint8_t)(PORT_PINCFG_INEN|PORT_PINCFG_PULLEN);
        PORT->Group[g_PinTable[pin].port].DIRCLR[g_PinTable[pin].pin].reg = (uint32_t)(1<<g_PinTable[pin].pin);

        // Enable pull level (cf '22.6.3.2 Input Configuration' and '22.8.7 Data Output Value Set')
        PORT->Group[g_PinTable[pin].pin].OUTSET.reg = (uint32_t)(1<<g_PinTable[pin].pin) ;
        break;
    case PinMode::INPUT_PULLDOWN:
        PORT->Group[g_PinTable[pin].port].PINCFG[g_PinTable[pin].pin].reg = (uint8_t)(PORT_PINCFG_INEN|PORT_PINCFG_PULLEN);
        PORT->Group[g_PinTable[pin].port].DIRCLR[g_PinTable[pin].pin].reg = (uint32_t)(1<<g_PinTable[pin].pin);

        // Enable pull level (cf '22.6.3.2 Input Configuration' and '22.8.7 Data Output Value Clear')
        PORT->Group[g_PinTable[pin].pin].OUTCLR.reg = (uint32_t)(1<<g_PinTable[pin].pin) ;
        break;
    default:
        break;
    }
}

void digitalWrite(pin_size_t pinNumber, PinStatus status) {
    // TODO

    // TODO handle case if pin isn't available

    switch (status) {
    case PinStatus::LOW:
        // TODO
        break;
    case PinStatus::HIGH:
        //TODO
        break;
    }
}

PinStatus digitalRead(pin_size_t pinNumber) {
    // TODO
}
