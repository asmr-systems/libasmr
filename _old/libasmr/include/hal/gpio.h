#ifndef ASMR_GPIO_H
#define ASMR_GPIO_H

#include <memory>

#include "../common.h"


namespace asmr {
    namespace hal {

        class GPIO {
        public:
            enum Mode {
                Input   = 0b00,
                Output  = 0b01,
                AltFunc = 0b10,
                Analog  = 0b11,
            };
            enum Type {
                PushPull  = 0b0,
                OpenDrain = 0b1,
            };
            enum Speed {
                Low      = 0b00,
                Medium   = 0b01,
                High     = 0b10,
                VeryHigh = 0b11,
            };
            enum ResistorPull {
                None = 0b00,
                Up   = 0b01,
                Down = 0b10,
            };
            using AltFunction = uint8_t;

            struct Config {
                Mode mode                  = Mode::Output;
                Type type                  = Type::PushPull;
                Speed speed                = Speed::High;
                ResistorPull resistor_pull = ResistorPull::None;
                AltFunction alt_function   = 0;
            };

            enum class Status { Ok, Error };

            virtual ~GPIO() { }

            virtual void write(PinStatus);
            virtual PinStatus read();
            virtual void toggle();
        };

    }

    std::shared_ptr<hal::GPIO> GPIO(Port p, int n, hal::GPIO::Config)  __attribute__((weak));
}

#endif
