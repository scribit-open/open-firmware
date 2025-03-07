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

void crc16(uint16_t *crc, const void * const data, uint16_t cnt) {
  uint8_t *ptr = (uint8_t *)data;
  while (cnt--) {
    *crc = (uint16_t)(*crc ^ (uint16_t)(((uint16_t)*ptr++) << 8));
    for (uint8_t i = 0; i < 8; i++)
      *crc = (uint16_t)((*crc & 0x8000) ? ((uint16_t)(*crc << 1) ^ 0x1021) : (*crc << 1));
  }
}

char conv[8] = { 0 };

#define DIGIT(n)        ('0' + (n))
#define DIGIMOD(n, f)   DIGIT((n)/(f) % 10)
#define RJDIGIT(n, f)   ((n) >= (f) ? DIGIMOD(n, f) : ' ')
#define MINUSOR(n, alt) (n >= 0 ? (alt) : (n = -n, '-'))

// Convert unsigned int to string 123 format
char* i8tostr3(const uint8_t i) {
  conv[4] = RJDIGIT(i, 100);
  conv[5] = RJDIGIT(i, 10);
  conv[6] = DIGIMOD(i, 1);
  return &conv[4];
}

// Convert signed int to rj string with 123 or -12 format
char* itostr3(int i) {
  conv[4] = MINUSOR(i, RJDIGIT(i, 100));
  conv[5] = RJDIGIT(i, 10);
  conv[6] = DIGIMOD(i, 1);
  return &conv[4];
}

// Convert unsigned int to lj string with 123 format
char* itostr3left(const int i) {
  char *str = &conv[6];
  *str = DIGIMOD(i, 1);
  if (i >= 10) {
    *(--str) = DIGIMOD(i, 10);
    if (i >= 100)
      *(--str) = DIGIMOD(i, 100);
  }
  return str;
}

// Convert signed int to rj string with 1234, _123, -123, _-12, or __-1 format
char* itostr4sign(const int i) {
  const bool neg = i < 0;
  const int ii = neg ? -i : i;
  if (i >= 1000) {
    conv[3] = DIGIMOD(ii, 1000);
    conv[4] = DIGIMOD(ii, 100);
    conv[5] = DIGIMOD(ii, 10);
  }
  else if (ii >= 100) {
    conv[3] = neg ? '-' : ' ';
    conv[4] = DIGIMOD(ii, 100);
    conv[5] = DIGIMOD(ii, 10);
  }
  else {
    conv[3] = ' ';
    conv[4] = ' ';
    if (ii >= 10) {
      conv[4] = neg ? '-' : ' ';
      conv[5] = DIGIMOD(ii, 10);
    }
    else {
      conv[5] = neg ? '-' : ' ';
    }
  }
  conv[6] = DIGIMOD(ii, 1);
  return &conv[3];
}

// Convert unsigned float to string with 1.23 format
char* ftostr12ns(const float &f) {
  const long i = ((f < 0 ? -f : f) * 1000 + 5) / 10;
  conv[3] = DIGIMOD(i, 100);
  conv[4] = '.';
  conv[5] = DIGIMOD(i, 10);
  conv[6] = DIGIMOD(i, 1);
  return &conv[3];
}

// Convert signed float to fixed-length string with 023.45 / -23.45 format
char* ftostr52(const float &f) {
  long i = (f * 1000 + (f < 0 ? -5: 5)) / 10;
  conv[1] = MINUSOR(i, DIGIMOD(i, 10000));
  conv[2] = DIGIMOD(i, 1000);
  conv[3] = DIGIMOD(i, 100);
  conv[4] = '.';
  conv[5] = DIGIMOD(i, 10);
  conv[6] = DIGIMOD(i, 1);
  return &conv[1];
}

#if ENABLED(LCD_DECIMAL_SMALL_XY)

  // Convert float to rj string with 1234, _123, -123, _-12, 12.3, _1.2, or -1.2 format
  char* ftostr4sign(const float &f) {
    const int i = (f * 100 + (f < 0 ? -5: 5)) / 10;
    if (!WITHIN(i, -99, 999)) return itostr4sign((int)f);
    const bool neg = i < 0;
    const int ii = neg ? -i : i;
    conv[3] = neg ? '-' : (ii >= 100 ? DIGIMOD(ii, 100) : ' ');
    conv[4] = DIGIMOD(ii, 10);
    conv[5] = '.';
    conv[6] = DIGIMOD(ii, 1);
    return &conv[3];
  }

#endif // LCD_DECIMAL_SMALL_XY

// Convert float to fixed-length string with +123.4 / -123.4 format
char* ftostr41sign(const float &f) {
  int i = (f * 100 + (f < 0 ? -5: 5)) / 10;
  conv[1] = MINUSOR(i, '+');
  conv[2] = DIGIMOD(i, 1000);
  conv[3] = DIGIMOD(i, 100);
  conv[4] = DIGIMOD(i, 10);
  conv[5] = '.';
  conv[6] = DIGIMOD(i, 1);
  return &conv[1];
}

// Convert signed float to string (6 digit) with -1.234 / _0.000 / +1.234 format
char* ftostr43sign(const float &f, char plus/*=' '*/) {
  long i = (f * 10000 + (f < 0 ? -5: 5)) / 10;
  conv[1] = i ? MINUSOR(i, plus) : ' ';
  conv[2] = DIGIMOD(i, 1000);
  conv[3] = '.';
  conv[4] = DIGIMOD(i, 100);
  conv[5] = DIGIMOD(i, 10);
  conv[6] = DIGIMOD(i, 1);
  return &conv[1];
}

// Convert unsigned float to rj string with 12345 format
char* ftostr5rj(const float &f) {
  const long i = ((f < 0 ? -f : f) * 10 + 5) / 10;
  conv[2] = RJDIGIT(i, 10000);
  conv[3] = RJDIGIT(i, 1000);
  conv[4] = RJDIGIT(i, 100);
  conv[5] = RJDIGIT(i, 10);
  conv[6] = DIGIMOD(i, 1);
  return &conv[2];
}

// Convert signed float to string with +1234.5 format
char* ftostr51sign(const float &f) {
  long i = (f * 100 + (f < 0 ? -5: 5)) / 10;
  conv[0] = MINUSOR(i, '+');
  conv[1] = DIGIMOD(i, 10000);
  conv[2] = DIGIMOD(i, 1000);
  conv[3] = DIGIMOD(i, 100);
  conv[4] = DIGIMOD(i, 10);
  conv[5] = '.';
  conv[6] = DIGIMOD(i, 1);
  return conv;
}

// Convert signed float to string with +123.45 format
char* ftostr52sign(const float &f) {
  long i = (f * 1000 + (f < 0 ? -5: 5)) / 10;
  conv[0] = MINUSOR(i, '+');
  conv[1] = DIGIMOD(i, 10000);
  conv[2] = DIGIMOD(i, 1000);
  conv[3] = DIGIMOD(i, 100);
  conv[4] = '.';
  conv[5] = DIGIMOD(i, 10);
  conv[6] = DIGIMOD(i, 1);
  return conv;
}

// Convert unsigned float to string with 1234.56 format omitting trailing zeros
char* ftostr62rj(const float &f) {
  const long i = ((f < 0 ? -f : f) * 1000 + 5) / 10;
  conv[0] = RJDIGIT(i, 100000);
  conv[1] = RJDIGIT(i, 10000);
  conv[2] = RJDIGIT(i, 1000);
  conv[3] = DIGIMOD(i, 100);
  conv[4] = '.';
  conv[5] = DIGIMOD(i, 10);
  conv[6] = DIGIMOD(i, 1);
  return conv;
}

// Convert signed float to space-padded string with -_23.4_ format
char* ftostr52sp(const float &f) {
  long i = (f * 1000 + (f < 0 ? -5: 5)) / 10;
  uint8_t dig;
  conv[1] = MINUSOR(i, RJDIGIT(i, 10000));
  conv[2] = RJDIGIT(i, 1000);
  conv[3] = DIGIMOD(i, 100);

  if ((dig = i % 10)) {           // second digit after decimal point?
    conv[4] = '.';
    conv[5] = DIGIMOD(i, 10);
    conv[6] = DIGIT(dig);
  }
  else {
    if ((dig = (i / 10) % 10)) {  // first digit after decimal point?
      conv[4] = '.';
      conv[5] = DIGIT(dig);
    }
    else                          // nothing after decimal point
      conv[4] = conv[5] = ' ';
    conv[6] = ' ';
  }
  return &conv[1];
}
