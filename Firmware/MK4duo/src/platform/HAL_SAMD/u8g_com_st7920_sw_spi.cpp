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
 * Based on u8g_com_st7920_hw_spi.c
 *
 * Universal 8bit Graphics Library
 *
 * Copyright (c) 2011, olikraus@gmail.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice, this list
 *    of conditions and the following disclaimer.
 *
 *  * Redistributions in binary form must reproduce the above copyright notice, this
 *    list of conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "../../../MK4duo.h"

#if ENABLED(ARDUINO_ARCH_SAMD) && HAS_GRAPHICAL_LCD

#include <U8glib.h>
#include <Arduino.h>

void u8g_SetPIOutput_SAMD(u8g_t *u8g, uint8_t pin_index) {
  //SET_OUTPUT(u8g->pin_list[pin_index]);
  pinMode(u8g->pin_list[pin_index],OUTPUT);
}

void u8g_SetPILevel_SAMD(u8g_t *u8g, uint8_t pin_index, uint8_t level) {
  //WRITE(u8g->pin_list[pin_index],level);
 digitalWrite(u8g->pin_list[pin_index], level);

}

uint32_t pin_MOSI,pin_SCK;

static void spiSend_sw_SAMD(uint8_t val) { // 800KHz
  for (uint8_t i = 0; i < 8; i++) {
    WRITE (pin_MOSI,val & 0x80);
     
    DELAY_NS(50);

    WRITE (pin_SCK,1);
    DELAY_NS(905); // 762 dead, 810 garbage, 858/0 900kHz, 905/1 825k, 953/1 800k, 1000/2 725KHz
    val <<= 1;
    WRITE (pin_SCK,0);
  }
}

static uint8_t rs_last_state = 255;

static void u8g_com_SAMD_st7920_write_byte_sw_spi(uint8_t rs, uint8_t val) {
  uint8_t i;

  if (rs != rs_last_state) {  // time to send a command/data byte
    rs_last_state = rs;

    if (rs == 0)
      /* command */
      spiSend_sw_SAMD(0x0F8);
    else
       /* data */
      spiSend_sw_SAMD(0x0FA);

    DELAY_US(40); // give the controller some time to process the data: 20 is bad, 30 is OK, 40 is safe
  }

  spiSend_sw_SAMD(val & 0x0F0);
  spiSend_sw_SAMD(val << 4);
}

static void writebyte(uint8_t rs, uint8_t val) {
  uint8_t i;

  if ( rs == 0 ) {
    /* command */
    SPI.transfer(0x0f8);
  }
  else if ( rs == 1 ) {
    /* data */
    SPI.transfer(0x0fa);
  }

  SPI.transfer(val & 0x0f0);
  SPI.transfer(val << 4);
  HAL::delayMicroseconds(50);
}

uint8_t u8g_com_HAL_SAMD_ST7920_sw_spi_fn(u8g_t *u8g, uint8_t msg, uint8_t arg_val, void *arg_ptr) {

  pin_MOSI = u8g->pin_list[U8G_PI_MOSI];
  pin_SCK = u8g->pin_list[U8G_PI_SCK];

  switch (msg) {
    case U8G_COM_MSG_INIT:
      u8g_SetPILevel_SAMD(u8g, U8G_PI_CS, 0);
      u8g_SetPIOutput_SAMD(u8g, U8G_PI_CS);
      u8g_Delay(5);

      u8g->pin_list[U8G_PI_A0_STATE] = 0;       /* inital RS state: command mode */
      break;

    case U8G_COM_MSG_STOP:
      break;

    case U8G_COM_MSG_RESET:
       if (U8G_PIN_NONE != u8g->pin_list[U8G_PI_RESET]) u8g_SetPILevel_SAMD(u8g, U8G_PI_RESET, arg_val);
      break;

    case U8G_COM_MSG_ADDRESS:                     /* define cmd (arg_val = 0) or data mode (arg_val = 1) */
      u8g->pin_list[U8G_PI_A0_STATE] = arg_val;
      break;

    case U8G_COM_MSG_CHIP_SELECT:
      if (U8G_PIN_NONE != u8g->pin_list[U8G_PI_CS])
        u8g_SetPILevel_SAMD(u8g, U8G_PI_CS, arg_val);  //note: the st7920 has an active high chip select
      break;

    case U8G_COM_MSG_WRITE_BYTE:

      u8g_com_SAMD_st7920_write_byte_sw_spi(u8g->pin_list[U8G_PI_A0_STATE], arg_val);
      break;

    case U8G_COM_MSG_WRITE_SEQ: {
        uint8_t *ptr = (uint8_t*) arg_ptr;
        while (arg_val > 0) {
          u8g_com_SAMD_st7920_write_byte_sw_spi(u8g->pin_list[U8G_PI_A0_STATE], *ptr++);
          arg_val--;
        }
      }
      break;

      case U8G_COM_MSG_WRITE_SEQ_P: {
        uint8_t *ptr = (uint8_t*) arg_ptr;
        while (arg_val > 0) {
          u8g_com_SAMD_st7920_write_byte_sw_spi(u8g->pin_list[U8G_PI_A0_STATE], *ptr++);
          arg_val--;
        }
      }
      break;
  }
  return 1;
}

#endif  // ENABLED(ARDUINO_ARCH_SAMD) && HAS_GRAPHICAL_LCD
