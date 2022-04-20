/*
  Copyright (c) 2015 Arduino LLC.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#ifndef _WIRING_PRIVATE_H_
#define _WIRING_PRIVATE_H_

#include <variant.h>

typedef enum {
    PORTA = 0,
    PORTB = 1,
} PortNumber;

typedef enum {
    PIO_NOT_A_PIN=-1,     /* Not under control of a peripheral. */
    PIO_EXTINT=0,         /* The pin is controlled by the associated signal of peripheral A. */
    PIO_ANALOG,           /* The pin is controlled by the associated signal of peripheral B. */
    PIO_SERCOM,           /* The pin is controlled by the associated signal of peripheral C. */
    PIO_SERCOM_ALT,       /* The pin is controlled by the associated signal of peripheral D. */
    PIO_TIMER,            /* The pin is controlled by the associated signal of peripheral E. */
    PIO_TIMER_ALT,        /* The pin is controlled by the associated signal of peripheral F. */
    PIO_COM,              /* The pin is controlled by the associated signal of peripheral G. */
    PIO_AC_CLK,           /* The pin is controlled by the associated signal of peripheral H. */
    PIO_DIGITAL,          /* The pin is controlled by PORT. */
    PIO_INPUT,            /* The pin is controlled by PORT and is an input. */
    PIO_INPUT_PULLUP,     /* The pin is controlled by PORT and is an input with internal pull-up resistor enabled. */
    PIO_OUTPUT,           /* The pin is controlled by PORT and is an output. */

    PIO_PWM=PIO_TIMER,
    PIO_PWM_ALT=PIO_TIMER_ALT,
} PeripheralType;

typedef struct {
    PortNumber       port;
    uint32_t         pin;
    PeripheralType   type;
} PinTableEntry;

int pinPeripheral( uint32_t pin, PeripheralType peripheral );

// Pin table instantiated in variant.cc
extern const PinTableEntry g_PinTable[];

/* Generic Clock Multiplexer IDs */
#define GCM_DFLL48M_REF           (0x00U)
#define GCM_FDPLL96M_INPUT        (0x01U)
#define GCM_FDPLL96M_32K          (0x02U)
#define GCM_WDT                   (0x03U)
#define GCM_RTC                   (0x04U)
#define GCM_EIC                   (0x05U)
#define GCM_USB                   (0x06U)
#define GCM_EVSYS_CHANNEL_0       (0x07U)
#define GCM_EVSYS_CHANNEL_1       (0x08U)
#define GCM_EVSYS_CHANNEL_2       (0x09U)
#define GCM_EVSYS_CHANNEL_3       (0x0AU)
#define GCM_EVSYS_CHANNEL_4       (0x0BU)
#define GCM_EVSYS_CHANNEL_5       (0x0CU)
#define GCM_EVSYS_CHANNEL_6       (0x0DU)
#define GCM_EVSYS_CHANNEL_7       (0x0EU)
#define GCM_EVSYS_CHANNEL_8       (0x0FU)
#define GCM_EVSYS_CHANNEL_9       (0x10U)
#define GCM_EVSYS_CHANNEL_10      (0x11U)
#define GCM_EVSYS_CHANNEL_11      (0x12U)
#define GCM_SERCOMx_SLOW          (0x13U)
#define GCM_SERCOM0_CORE          (0x14U)
#define GCM_SERCOM1_CORE          (0x15U)
#define GCM_SERCOM2_CORE          (0x16U)
#define GCM_SERCOM3_CORE          (0x17U)
#define GCM_SERCOM4_CORE          (0x18U)
#define GCM_SERCOM5_CORE          (0x19U)
#define GCM_TCC0_TCC1             (0x1AU)
#define GCM_TCC2_TC3              (0x1BU)
#define GCM_TC4_TC5               (0x1CU)
#define GCM_TC6_TC7               (0x1DU)
#define GCM_ADC                   (0x1EU)
#define GCM_AC_DIG                (0x1FU)
#define GCM_AC_ANA                (0x20U)
#define GCM_DAC                   (0x21U)
#define GCM_PTC                   (0x22U)
#define GCM_I2S_0                 (0x23U)
#define GCM_I2S_1                 (0x24U)


#endif
