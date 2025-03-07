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
 * Description: functions for SPI connected external EEPROM.
 * Not platform dependent.
 */

#include "../../../MK4duo.h"

#if HAS_EEPROM_SPI

#include "../platform.h"

#define CMD_WREN  6   // WREN
#define CMD_READ  3   // WRITE
#define CMD_WRITE 2   // WRITE

uint8_t eeprom_read_byte(uint8_t* pos) {
  uint8_t v;
  uint8_t eeprom_temp[3];

  // set read location
  // begin transmission from device
  eeprom_temp[0] = CMD_READ;
  eeprom_temp[1] = ((unsigned)pos >> 8) & 0xFF; // addr High
  eeprom_temp[2] = (unsigned)pos & 0xFF;        // addr Low
  HAL::digitalWrite(SPI_EEPROM1_CS, HIGH);
  HAL::digitalWrite(SPI_EEPROM1_CS, LOW);
  HAL::spiSend(SPI_CHAN_EEPROM1, eeprom_temp, 3);

  v = HAL::spiReceive(SPI_CHAN_EEPROM1);
  HAL::digitalWrite(SPI_EEPROM1_CS, HIGH);
  return v;
}

void eeprom_read_block(void* pos, const void* eeprom_address, size_t n) {
  uint8_t eeprom_temp[3];
  uint8_t *p_pos = (uint8_t *)pos;

  // set read location
  // begin transmission from device
  eeprom_temp[0] = CMD_READ;
  eeprom_temp[1] = ((unsigned)eeprom_address >> 8) & 0xFF;  // addr High
  eeprom_temp[2] = (unsigned)eeprom_address & 0xFF;         // addr Low
  HAL::digitalWrite(SPI_EEPROM1_CS, HIGH);
  HAL::digitalWrite(SPI_EEPROM1_CS, LOW);
  HAL::spiSend(SPI_CHAN_EEPROM1, eeprom_temp, 3);

  while (n--)
    *p_pos++ = HAL::spiReceive(SPI_CHAN_EEPROM1);
  HAL::digitalWrite(SPI_EEPROM1_CS, HIGH);
}

void eeprom_write_byte(uint8_t* pos, uint8_t value) {
  uint8_t eeprom_temp[3];

  /*write enable*/
  eeprom_temp[0] = CMD_WREN;
  HAL::digitalWrite(SPI_EEPROM1_CS, LOW);
  HAL::spiSend(SPI_CHAN_EEPROM1, eeprom_temp, 1);
  HAL::digitalWrite(SPI_EEPROM1_CS, HIGH);
  HAL::delayMilliseconds(1);

  /*write addr*/
  eeprom_temp[0] = CMD_WRITE;
  eeprom_temp[1] = ((unsigned)pos>>8) & 0xFF;  //addr High
  eeprom_temp[2] = (unsigned)pos & 0xFF;       //addr Low
  HAL::digitalWrite(SPI_EEPROM1_CS, LOW);
  HAL::spiSend(SPI_CHAN_EEPROM1, eeprom_temp, 3);

  HAL::spiSend(SPI_CHAN_EEPROM1, value);
  HAL::digitalWrite(SPI_EEPROM1_CS, HIGH);
  HAL::delayMilliseconds(7);  // wait for page write to complete
}

void eeprom_update_block(const void* pos, void* eeprom_address, size_t n) {
  uint8_t eeprom_temp[3];

  /*write enable*/
  eeprom_temp[0] = CMD_WREN;
  HAL::digitalWrite(SPI_EEPROM1_CS, LOW);
  HAL::spiSend(SPI_CHAN_EEPROM1, eeprom_temp, 1);
  HAL::digitalWrite(SPI_EEPROM1_CS, HIGH);
  HAL::delayMilliseconds(1);

  /*write addr*/
  eeprom_temp[0] = CMD_WRITE;
  eeprom_temp[1] = ((unsigned)eeprom_address >> 8) & 0xFF;  // addr High
  eeprom_temp[2] = (unsigned)eeprom_address & 0xFF;         // addr Low
  HAL::digitalWrite(SPI_EEPROM1_CS, LOW);
  HAL::spiSend(SPI_CHAN_EEPROM1, eeprom_temp, 3);

  HAL::spiSend(SPI_CHAN_EEPROM1, (const uint8_t*)pos, n);
  HAL::digitalWrite(SPI_EEPROM1_CS, HIGH);
  HAL::delayMilliseconds(7);  // wait for page write to complete
}

#endif // HAS_EEPROM_SPI
