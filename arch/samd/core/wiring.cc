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

#include <ASMR>
#include "wiring.h"

int pinPeripheral( uint32_t ulPin, PeripheralType ulPeripheral )
{
  // Handle the case the pin isn't usable as PIO
  if ( g_PinTable[ulPin].type == PIO_NOT_A_PIN )
  {
    return -1 ;
  }

  switch ( ulPeripheral )
  {
    case PIO_DIGITAL:
    case PIO_INPUT:
    case PIO_INPUT_PULLUP:
    case PIO_OUTPUT:
      // Disable peripheral muxing, done in pinMode
//			PORT->Group[g_PinTable[ulPin].ulPort].PINCFG[g_PinTable[ulPin].ulPin].bit.PMUXEN = 0 ;

      // Configure pin mode, if requested
      if ( ulPeripheral == PIO_INPUT )
      {
          pinMode( ulPin, PinMode::INPUT ) ;
      }
      else
      {
        if ( ulPeripheral == PIO_INPUT_PULLUP )
        {
            pinMode( ulPin, PinMode::INPUT_PULLUP ) ;
        }
        else
        {
          if ( ulPeripheral == PIO_OUTPUT )
          {
              pinMode( ulPin, PinMode::OUTPUT ) ;
          }
          else
          {
            // PIO_DIGITAL, do we have to do something as all cases are covered?
          }
        }
      }
    break ;

    case PIO_ANALOG:
    case PIO_SERCOM:
    case PIO_SERCOM_ALT:
    case PIO_TIMER:
    case PIO_TIMER_ALT:
    case PIO_EXTINT:
    case PIO_COM:
    case PIO_AC_CLK:
#if 0
      // Is the pio pin in the lower 16 ones?
      // The WRCONFIG register allows update of only 16 pin max out of 32
      if ( g_PinTable[ulPin].ulPin < 16 )
      {
        PORT->Group[g_PinTable[ulPin].ulPort].WRCONFIG.reg = PORT_WRCONFIG_WRPMUX | PORT_WRCONFIG_PMUXEN | PORT_WRCONFIG_PMUX( ulPeripheral ) |
                                                                    PORT_WRCONFIG_WRPINCFG |
                                                                    PORT_WRCONFIG_PINMASK( g_PinTable[ulPin].ulPin ) ;
      }
      else
      {
        PORT->Group[g_PinTable[ulPin].ulPort].WRCONFIG.reg = PORT_WRCONFIG_HWSEL |
                                                                    PORT_WRCONFIG_WRPMUX | PORT_WRCONFIG_PMUXEN | PORT_WRCONFIG_PMUX( ulPeripheral ) |
                                                                    PORT_WRCONFIG_WRPINCFG |
                                                                    PORT_WRCONFIG_PINMASK( g_PinTable[ulPin].ulPin - 16 ) ;
      }
#else
      if ( g_PinTable[ulPin].pin & 1 ) // is pin odd?
      {
        uint32_t temp ;

        // Get whole current setup for both odd and even pins and remove odd one
        temp = (PORT->Group[g_PinTable[ulPin].port].PMUX[g_PinTable[ulPin].pin >> 1].reg) & PORT_PMUX_PMUXE( 0xF ) ;
        // Set new muxing
        PORT->Group[g_PinTable[ulPin].port].PMUX[g_PinTable[ulPin].pin >> 1].reg = temp|PORT_PMUX_PMUXO( ulPeripheral ) ;
        // Enable port mux
        PORT->Group[g_PinTable[ulPin].port].PINCFG[g_PinTable[ulPin].pin].reg |= PORT_PINCFG_PMUXEN ;
      }
      else // even pin
      {
        uint32_t temp ;

        temp = (PORT->Group[g_PinTable[ulPin].port].PMUX[g_PinTable[ulPin].pin >> 1].reg) & PORT_PMUX_PMUXO( 0xF ) ;
        PORT->Group[g_PinTable[ulPin].port].PMUX[g_PinTable[ulPin].pin >> 1].reg = temp|PORT_PMUX_PMUXE( ulPeripheral ) ;
        PORT->Group[g_PinTable[ulPin].port].PINCFG[g_PinTable[ulPin].pin].reg |= PORT_PINCFG_PMUXEN ; // Enable port mux
      }
#endif
    break ;

    case PIO_NOT_A_PIN:
      return -1l ;
    break ;
  }

  return 0l ;
}
