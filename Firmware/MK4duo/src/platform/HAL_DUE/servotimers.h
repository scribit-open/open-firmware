/**
 * MK4duo Firmware for 3D Printer, Laser and CNC
 *
 * Based on Marlin, Sprinter and grbl
 * Copyright (C) 2011 Camiel Gubbels / Erik van der Zalm
 * Copyright (C) 2013 Alberto Cotronei @MagoKimbra
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */

/**
 * Copyright (c) 2013 Arduino LLC. All right reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 */

/**
 * Defines for 16 bit timers used with Servo library
 *
 * If _useTimerX is defined then TimerX is a 16 bit timer on the current board
 * timer16_Sequence_t enumerates the sequence that the timers should be allocated
 * _Nbr_16timers indicates how many 16 bit timers are available.
 */

/**
 * SAM Only definitions
 * --------------------
 */

// For SAM3X:
//!#define _useTimer1
//!#define _useTimer2
//!#define _useTimer3
//!#define _useTimer4
#define _useTimer5

#define TRIM_DURATION  2  // compensation ticks to trim adjust for digitalWrite delays
#define PRESCALER     32  // timer prescaler

/*
  TC0, chan 0 => TC0_Handler
  TC0, chan 1 => TC1_Handler
  TC0, chan 2 => TC2_Handler
  TC1, chan 0 => TC3_Handler
  TC1, chan 1 => TC4_Handler
  TC1, chan 2 => TC5_Handler
  TC2, chan 0 => TC6_Handler
  TC2, chan 1 => TC7_Handler
  TC2, chan 2 => TC8_Handler
 */

#if ENABLED (_useTimer1)
  #define TC_FOR_TIMER1       TC0
  #define CHANNEL_FOR_TIMER1  1
  #define ID_TC_FOR_TIMER1    ID_TC1
  #define IRQn_FOR_TIMER1     TC1_IRQn
  #define HANDLER_FOR_TIMER1  TC1_Handler
#endif
#if ENABLED (_useTimer2)
  #define TC_FOR_TIMER2       TC0
  #define CHANNEL_FOR_TIMER2  2
  #define ID_TC_FOR_TIMER2    ID_TC2
  #define IRQn_FOR_TIMER2     TC2_IRQn
  #define HANDLER_FOR_TIMER2  TC2_Handler
#endif
#if ENABLED (_useTimer3)
  #define TC_FOR_TIMER3       TC1
  #define CHANNEL_FOR_TIMER3  2
  #define ID_TC_FOR_TIMER3    ID_TC5
  #define IRQn_FOR_TIMER3     TC5_IRQn
  #define HANDLER_FOR_TIMER3  TC5_Handler
#endif
#if ENABLED (_useTimer4)
  #define TC_FOR_TIMER4       TC0
  #define CHANNEL_FOR_TIMER4  2
  #define ID_TC_FOR_TIMER4    ID_TC2
  #define IRQn_FOR_TIMER4     TC2_IRQn
  #define HANDLER_FOR_TIMER4  TC2_Handler
#endif
#if ENABLED (_useTimer5)
  #define TC_FOR_TIMER5       TC1
  #define CHANNEL_FOR_TIMER5  2
  #define ID_TC_FOR_TIMER5    ID_TC5
  #define IRQn_FOR_TIMER5     TC5_IRQn
  #define HANDLER_FOR_TIMER5  TC5_Handler
#endif

typedef enum { _timer5, _Nbr_16timers } timer16_Sequence_t;
