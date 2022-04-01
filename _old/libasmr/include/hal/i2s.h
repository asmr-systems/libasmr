//:::: Inter-IC Sound (I2S) Interface
//:::::::::::::::::::::::::::::::::::

#ifndef ASMR_HAL_I2S_H
#define ASMR_HAL_I2S_H

#include <memory>

#include "../audio.h"


namespace asmr {
    namespace hal {

        class I2S {
        public:
            struct Config {
                uint32_t sample_rate    = 44100;
                uint32_t buffer_size    = 2048; //2048
                uint16_t bit_depth      = 24;
                uint16_t channels       = 2;
                bool     input_enabled  = false;
                bool     output_enabled = true;
                bool     mclk_enabled   = false;
            };

            enum class Status {
                Ok,
                Error,
            };

            virtual ~I2S() { }

            virtual Status init(Config c)      = 0;
            virtual bool input_ready()         = 0;
            virtual bool output_ready()        = 0;
            virtual Audio& get_audio_input()   = 0;
            virtual Audio& get_audio_output()  = 0;
        };

    }

    // TODO do we need the weak attribute? maybe add an alias that returns something?
    // ideally it would be a compile time error.
    std::shared_ptr<hal::I2S> I2S() __attribute__((weak));
}

#endif
