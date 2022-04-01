#include "stm32f405xx.h"

#include <asmr>

#include "interrupts.h"


void asmr::hal::set_interrupt(int irq_n, uint32_t irq_addr) {
    static uint32_t *vectors = nullptr;

    __disable_irq();
    if (!vectors) {
        // relocate interrupt vectors from ROM->RAM
        uint32_t *old_vectors = (uint32_t *)(FLASH_BASE);
        vectors = new uint32_t[asmr::stm32f405::N_INTERRUPTS];
        for (int i = 0; i < asmr::stm32f405::N_INTERRUPTS; i++) {
            vectors[i] = old_vectors[i];
        }
        SCB->VTOR = (uint32_t)&vectors;
    }

    NVIC_SetVector((IRQn_Type)irq_n, irq_addr);

    __enable_irq();
};
