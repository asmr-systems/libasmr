#include <samd10.h>

/**
 *  \brief System Initialization function for SAMD.
 *
 *  See arduino samd startup.c for other ideas of what to do on startup!
 */
void SystemInit() {
    // see cortex SysTick->CTRL register
    // also https://developer.arm.com/documentation/dui0662/b/Cortex-M0--Peripherals/System-timer--SysTick/SysTick-Control-and-Status-Register?lang=en
    SysTick->CTRL = 7; // enabled, use interrupt,internal clock source
}
