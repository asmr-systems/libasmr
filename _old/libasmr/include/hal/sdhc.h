//:::: SD Host Controller Interface
//:::::::::::::::::::::::::::::::::

#ifndef ASMR_HAL_SDHC_H
#define ASMR_HAL_SDHC_H

#include <memory>

#include "../sdio.h"
#include "../common.h"


namespace asmr {
    namespace hal {

        class SDHostCtlr {
        public:
            struct Config {
                struct { Port port; Pin pin; } clk_io;
                struct { Port port; Pin pin; } cmd_io;
                struct { Port port; Pin pin; } d0_io;
                struct { Port port; Pin pin; } d1_io;
                struct { Port port; Pin pin; } d2_io;
                struct { Port port; Pin pin; } d3_io;
            };

            enum class Status {
                Ok,
                Error,
            };

            virtual ~SDHostCtlr() { }

            virtual Status init()               = 0;
            virtual Status reset()                      = 0;
            virtual Status power_on()                   = 0;
            virtual Status power_off()                  = 0;
            virtual Status initialize_cards()           = 0;
            virtual Status set_clock_speed(sdio::Speed) = 0;
            virtual Status get_card_info()              = 0;
            virtual Status select_card()                = 0;
            virtual Status enable_wide_bus()            = 0;

            virtual Status read_blocks()                = 0;

        protected:
            virtual Status send_cmd(uint32_t cmd, uint32_t arg) = 0;

            Status send_cmd(sdio::CMD cmd, uint32_t arg) {
                return send_cmd((uint32_t)cmd, arg);
            };

            Status send_cmd(sdio::ACMD cmd, uint32_t arg) {
                auto status = send_cmd(sdio::CMD::APP_CMD, 0x0);
                if (status != Status::Ok) {
                    return status;
                }

                return send_cmd((uint32_t)cmd, arg);
            };
        };

    }

    std::shared_ptr<hal::SDHostCtlr> SDHostCtlr(hal::SDHostCtlr::Config c) __attribute__((weak));
}

#endif
