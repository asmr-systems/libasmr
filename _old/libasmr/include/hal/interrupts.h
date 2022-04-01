#ifndef ASMR_HAL_INTERRUPTS_H
#define ASMR_HAL_INTERRUPTS_H

#include <cstdint>


namespace asmr {
    namespace hal {

        void set_interrupt(int irq_n, uint32_t irq_addr); // __attribute__((weak));

    }
}

#endif
