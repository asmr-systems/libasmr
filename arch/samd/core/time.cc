#include <ASMR>


static volatile uint32_t _ulTickCount = 0;

unsigned long millis() {
    return _ulTickCount;
}

unsigned long micros() {
    uint32_t ticks_1, ticks_2;
    uint32_t pend_1, pend_2;
    uint32_t count_1, count_2;

    ticks_2 = SysTick->VAL;                            // read CPU System Timer
    pend_2  = !!(SCB->ICSR & SCB_ICSR_PENDSTCLR_Msk);  // is the System Tick Set Pending flag set?
    count_2 = _ulTickCount;

    do {
        ticks_1 = ticks_2;
        pend_1  = pend_2;
        count_1 = count_2;

        ticks_2 = SysTick->VAL;
        pend_2  = !!(SCB->ICSR & SCB_ICSR_PENDSTCLR_Msk);
        count_2 = _ulTickCount;
    } while ((pend_1 != pend_2) || (count_1 != count_2) || (ticks_1 < ticks_2));

    return ((count_1+pend_1) * 1000) + (((SysTick->LOAD-ticks_1)*(1048576/(VARIANT_MCK/1000000)))>>20);
}

void delay(unsigned long ms) {
    if (ms == 0) {
        return;
    }

    uint32_t start = micros();

    while (ms > 0) {
        while (ms > 0 && (micros() - start) >= 1000) {
            ms--;
            start += 1000;
        }
    }
}

extern "C" {

    void SysTick_Handler() {
        // increment tick count
        _ulTickCount++;
        //tickReset(); // ? idk what really this is
    }

}
