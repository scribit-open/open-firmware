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

#include "../../MK4duo.h"

#if ENABLED(DIGIPOT_I2C)

#include <Stream.h>
#include <Wire.h>
#include <utility/twi.h>

#include "digipot_mcp4451.h"

static byte current_to_wiper(float current) {
  return byte(CEIL(float((DIGIPOT_I2C_FACTOR * current))));
}

static void i2c_send(byte addr, byte a, byte b) {
  Wire.beginTransmission(addr);
  Wire.write(a);
  Wire.write(b);
  Wire.endTransmission();
}

// This is for the MCP4451 I2C based digipot
void digipot_i2c_set_current(int channel, float current) {
  current = min((float) MAX(current, 0.0f), DIGIPOT_I2C_MAX_CURRENT);
  // these addresses are specific to Azteeg X3 Pro, can be set to others,
  // In this case first digipot is at address A0=0, A1= 0, second one is at A0=0, A1= 1
  byte addr = 0x2C; // channel 0-3
  if (channel >= 4) {
    addr = 0x2E; // channel 4-7
    channel -= 4;
  }

  // Initial setup
  i2c_send(addr, 0x40, 0xFF);
  i2c_send(addr, 0xA0, 0xFF);

  // Set actual wiper value
  byte addresses[4] = { 0x00, 0x10, 0x60, 0x70 };
  i2c_send(addr, addresses[channel], current_to_wiper(current));
}

void digipot_i2c_init() {
  const float digipot_motor_current[] = DIGIPOT_I2C_MOTOR_CURRENTS;
  Wire.begin();
  // setup initial currents as defined in Configuration_adv.h
  for (int i = 0; i < COUNT(digipot_motor_current); i++)
    digipot_i2c_set_current(i, digipot_motor_current[i]);
}

#endif // DIGIPOT_I2C
