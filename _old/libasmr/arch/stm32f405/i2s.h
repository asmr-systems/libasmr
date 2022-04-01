#ifndef STM32F405_I2S_H
#define STM32F405_I2S_H

#include <memory>

#include "stm32f4xx.h"

#include <asmr>


namespace asmr {
    namespace stm32f405 {

        class I2S : public hal::I2S {
        public:
            static std::shared_ptr<I2S> Instance() {
                static auto const singleton = std::shared_ptr<I2S>(new I2S);
                return singleton;
            };

            virtual hal::I2S::Status init(hal::I2S::Config c) override;
            virtual bool input_ready() override;
            virtual bool output_ready() override;
            virtual Audio& get_audio_input() override;
            virtual Audio& get_audio_output() override;

        protected:
            I2S() { };
            static void irq();
        private:
            void init();
            void init_dma();

            hal::I2S::Config config;

            uint32_t* output_buffers[2];
            uint32_t* input_buffers[2];

            Audio audio_input;
            Audio audio_output;
        };

    }

    std::shared_ptr<hal::I2S> I2S() {
        return stm32f405::I2S::Instance();
    };

}

#endif
