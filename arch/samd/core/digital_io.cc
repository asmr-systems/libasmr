#include <ASMR>


void pinMode(pin_size_t pinNumber, PinMode pinMode) {
    // TODO figure out how to detect if the pin is not a pin
    // from the pin mapping.

    // set pin configuration
    switch (pinMode) {
    case PinMode::INPUT:
        PORT->Group[g_PinTable[pin].port].PINCFG[g_PinTable[pin].pin].reg = (uint8_t)(PORT_PINCFG_INEN);
        break;
    case PinMode::OUTPUT:
        break;
    case PinMode::INPUT_PULLUP:
        break;
    case PinMode::INPUT_PULLDOWN:
        break;
    case PinMode::OUTPUT_OPENDRAIN:
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
