#ifndef STM32F405_I2S_H
#define STM32F405_I2S_H

#include <memory>

#include <asmr>

#include "stm32f4xx.h"


namespace asmr {
    namespace stm32f405 {

        class GPIO : public hal::GPIO {
        public:
            GPIO(Port port, int pin, hal::GPIO::Config config);

            virtual void write(PinStatus) override;
            virtual PinStatus read() override;
            virtual void toggle() override;
        private:
            hal::GPIO::Config config;
            Port generic_port;
            GPIO_TypeDef * port;
            uint8_t pin;

            GPIO_TypeDef * from_generic_port(Port);
            int get_gpio_clock_enable_bit(Port);
        };

    }

    std::shared_ptr<hal::GPIO> GPIO(Port p, int n, hal::GPIO::Config c) {
        return std::shared_ptr<stm32f405::GPIO>(new stm32f405::GPIO(p, n, c));
    };
}

#endif
