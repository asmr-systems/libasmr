#include "gpio.h"

using namespace asmr;


stm32f405::GPIO::GPIO(Port _port, int _pin, hal::GPIO::Config _config) {
    generic_port = _port;
    port = from_generic_port(generic_port);
    pin = _pin;
    config = _config;

    // Enable GPIO <Port> Peripheral Clock
    RCC->AHB1ENR |= get_gpio_clock_enable_bit(generic_port);

    port->MODER   |= (config.mode)<<(pin*2);
    port->OTYPER  |= (config.type)<<5;
    port->OSPEEDR |= (config.speed)<<(pin*2);
    port->PUPDR   |= (config.resistor_pull)<<(pin*2);

    if (config.mode == Mode::AltFunc) {
        port->AFR[pin > 7]  |= config.alt_function << ((pin - (pin > 7 ? 8 : 0)) * 4);
    }

}

PinStatus stm32f405::GPIO::read() { return PinStatus::High; }

void stm32f405::GPIO::write(PinStatus status) {
    if (status == PinStatus::High) {
        port->ODR |= 1<<pin;
    } else {
        port->ODR &= ~(1<<pin);
    }
}

void stm32f405::GPIO::toggle() {
    write(static_cast<bool>(port->ODR&(1<<pin)) ? PinStatus::Low : PinStatus::High);
}


//:::: Private
//::::::::::::

GPIO_TypeDef * stm32f405::GPIO::from_generic_port(Port p) {
    GPIO_TypeDef* ports[9] = {GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOF,GPIOG,GPIOH,GPIOI};

    return ports[static_cast<int>(p)];
}

int stm32f405::GPIO::get_gpio_clock_enable_bit(Port p) {
    return (0x1UL << static_cast<int>(p));
}
