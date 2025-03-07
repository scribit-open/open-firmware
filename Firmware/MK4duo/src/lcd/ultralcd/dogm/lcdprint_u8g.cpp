/**
 * @file    lcdprint_u8g.cpp
 * @brief   LCD print api for u8glib
 * @author  Yunhui Fu (yhfudev@gmail.com)
 * @version 1.0
 * @date    2016-08-19
 * @copyright GPL/BSD
 */

#include "../../../../MK4duo.h"

#if HAS_GRAPHICAL_LCD

#include "ultralcd_dogm.h"
#include "u8g_fontutf8.h"
#include "../lcdprint.h"

int lcd_glyph_height(void) { return u8g_GetFontBBXHeight(u8g.getU8g()); }

void lcd_moveto(const uint8_t col, const uint8_t row) { u8g.setPrintPos(col, row); }

void lcd_put_int(const int i) { u8g.print(i); }

// return < 0 on error
// return the advanced pixels
int lcd_put_wchar_max(wchar_t c, pixel_len_t max_length) {
  if (c < 256) {
    u8g.print((char)c);
    return u8g_GetFontBBXWidth(u8g.getU8g());
  }
  unsigned int x = u8g.getPrintCol(),
               y = u8g.getPrintRow(),
               ret = uxg_DrawWchar(u8g.getU8g(), x, y, c, max_length);
  u8g.setPrintPos(x + ret, y);

  return ret;
}

int lcd_put_u8str_max(const char * utf8_str, pixel_len_t max_length) {
  unsigned int x = u8g.getPrintCol(),
               y = u8g.getPrintRow(),
               ret = uxg_DrawUtf8Str(u8g.getU8g(), x, y, utf8_str, max_length);
  u8g.setPrintPos(x + ret, y);
  return ret;
}

int lcd_put_u8str_max_P(PGM_P utf8_str_P, pixel_len_t max_length) {
  unsigned int x = u8g.getPrintCol(),
               y = u8g.getPrintRow(),
               ret = uxg_DrawUtf8StrP(u8g.getU8g(), x, y, utf8_str_P, max_length);
  u8g.setPrintPos(x + ret, y);
  return ret;
}

#endif // HAS_GRAPHICAL_LCD
