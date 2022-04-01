#ifndef STM32F405_SDHC_H
#define STM32F405_SDHC_H

#include <memory>

#include "stm32f4xx.h"

#include <asmr>


namespace asmr {
    namespace stm32f405 {

        class SDHostCtlr : public hal::SDHostCtlr {
        public:
            static std::shared_ptr<SDHostCtlr> Instance(hal::SDHostCtlr::Config c) {
                static auto const singleton = std::shared_ptr<SDHostCtlr>(new SDHostCtlr(c));
                return singleton;
            };

            virtual hal::SDHostCtlr::Status init() override;
            virtual hal::SDHostCtlr::Status reset() override;
            virtual hal::SDHostCtlr::Status power_on() override;
            virtual hal::SDHostCtlr::Status power_off() override;
            virtual hal::SDHostCtlr::Status initialize_cards() override;
            virtual hal::SDHostCtlr::Status set_clock_speed(sdio::Speed) override;
            virtual hal::SDHostCtlr::Status get_card_info() override;
            virtual hal::SDHostCtlr::Status select_card() override;
            virtual hal::SDHostCtlr::Status enable_wide_bus() override;

            virtual hal::SDHostCtlr::Status read_blocks() override;

        protected:
            SDHostCtlr(hal::SDHostCtlr::Config);
            static void irq();
        private:
            // SDIO_CK = SDIOCLK / [CLKDIV +2]
            // for stm32f405 devices, SDIOCLK = 48MHz
            static const uint8_t ClkDivInit = 0x76;  // SDIO_CK <= 400KHz
            static const uint8_t ClkDivTx   = 0x00;  // SDIO_CK <= 25MHz

            hal::SDHostCtlr::Config config;
            std::shared_ptr<hal::GPIO> clk_io;
            std::shared_ptr<hal::GPIO> cmd_io;
            std::shared_ptr<hal::GPIO> d0_io;
            std::shared_ptr<hal::GPIO> d1_io;
            std::shared_ptr<hal::GPIO> d2_io;
            std::shared_ptr<hal::GPIO> d3_io;

            // response (yes/no?)
            // wait (bool?)
            // cpsm (bool?)
            enum class Response {
                None  = 0b00,
                Short = 0b01,
                Long  = 0b11,
            };

            // ADD these to interface (maybe making the CMD/ACMD wrappers just defined in base)
            // since the mappings from command type to response type are well defined by the sdio
            // spec...we should just build this into these commands somehow
            void send_cmd(uint32_t cmd, uint32_t arg, uint32_t resp);
            void send_cmd(sdio::CMD, uint32_t arg, Response resp);
            void send_cmd(sdio::ACMD, uint32_t arg, Response resp);
        };

    }

    std::shared_ptr<hal::SDHostCtlr> SDHostCtlr(hal::SDHostCtlr::Config c) {
        return stm32f405::SDHostCtlr::Instance(c);
    };

}

#endif
