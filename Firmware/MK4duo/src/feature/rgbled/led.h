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
#pragma once

/**
 * led.h
 *
 * Copyright (C) 2017 Alberto Cotronei @MagoKimbra
 */

#if HAS_COLOR_LEDS

  #define HAS_WHITE_LED (ENABLED(RGBW_LED) || ENABLED(NEOPIXEL_LED))

  /**
   * LEDcolor type for use with leds.set_color
   */
  typedef struct LEDColor {
    uint8_t r, g, b
      #if HAS_WHITE_LED
        , w
        #if ENABLED(NEOPIXEL_LED)
          , i
        #endif
      #endif
    ;
    LEDColor() : r(255), g(255), b(255)
      #if HAS_WHITE_LED
        , w(255)
        #if ENABLED(NEOPIXEL_LED)
          , i(NEOPIXEL_BRIGHTNESS)
        #endif
      #endif
    {}
    LEDColor(uint8_t r, uint8_t g, uint8_t b
      #if HAS_WHITE_LED
        , uint8_t w=0
        #if ENABLED(NEOPIXEL_LED)
          , uint8_t i=NEOPIXEL_BRIGHTNESS
        #endif
      #endif
      ) : r(r), g(g), b(b)
      #if HAS_WHITE_LED
        , w(w)
        #if ENABLED(NEOPIXEL_LED)
          , i(i)
        #endif
      #endif
    {}
    LEDColor(const uint8_t (&rgbw)[4]) : r(rgbw[0]), g(rgbw[1]), b(rgbw[2])
      #if HAS_WHITE_LED
        , w(rgbw[3])
        #if ENABLED(NEOPIXEL_LED)
          , i(NEOPIXEL_BRIGHTNESS)
        #endif
      #endif
    {}
    LEDColor& operator=(const uint8_t (&rgbw)[4]) {
      r = rgbw[0]; g = rgbw[1]; b = rgbw[2];
      #if HAS_WHITE_LED
        w = rgbw[3];
      #endif
      return *this;
    }
    LEDColor& operator=(const LEDColor &right) {
      if (this != &right) memcpy(this, &right, sizeof(LEDColor));
      return *this;
    }
    bool operator==(const LEDColor &right) {
      if (this == &right) return true;
      return 0 == memcmp(this, &right, sizeof(LEDColor));
    }
    bool operator!=(const LEDColor &right) { return !operator==(right); }
    bool is_off() const {
      return 3 > r + g + b
        #if HAS_WHITE_LED
          + w
        #endif
      ;
    }
  } LEDColor;

  /**
   * Color helpers and presets
   */
  #if HAS_WHITE_LED
    #define LEDColorWhite() LEDColor(0, 0, 0, 255)
    #if ENABLED(NEOPIXEL_LED)
      #define MakeLEDColor(R,G,B,W,I) LEDColor(R, G, B, W, I)
    #else
      #define MakeLEDColor(R,G,B,W,I) LEDColor(R, G, B, W)
    #endif
  #else
    #define MakeLEDColor(R,G,B,W,I) LEDColor(R, G, B)
    #define LEDColorWhite() LEDColor(255, 255, 255)
  #endif
  #define LEDColorOff()     LEDColor(  0,   0,   0)
  #define LEDColorRed()     LEDColor(255,   0,   0)
  #define LEDColorOrange()  LEDColor(255,  80,   0)
  #define LEDColorYellow()  LEDColor(255, 255,   0)
  #define LEDColorGreen()   LEDColor(  0, 255,   0)
  #define LEDColorBlue()    LEDColor(  0,   0, 255)
  #define LEDColorIndigo()  LEDColor(  0, 255, 255)
  #define LEDColorViolet()  LEDColor(255,   0, 255)

  class LEDLights {

    public: /** Constructor */

      LEDLights() {}

    public: /** Public Parameters */

      #if ENABLED(LED_COLOR_PRESETS)
        static const LEDColor defaultLEDColor;
      #endif

      #if ENABLED(LED_CONTROL_MENU) || ENABLED(PRINTER_EVENT_LEDS)
        static LEDColor color; // last non-off color
        static bool lights_on; // the last set color was "on"
      #endif

    public: /** Public Function */

      static void setup();

      static void set_color(const LEDColor &color
        #if ENABLED(NEOPIXEL_LED)
          , bool isSequence=false
        #endif
      );

      inline void set_color(uint8_t r, uint8_t g, uint8_t b
        #if HAS_WHITE_LED
          , uint8_t w=0
          #if ENABLED(NEOPIXEL_LED)
            , uint8_t i=NEOPIXEL_BRIGHTNESS
          #endif
        #endif
        #if ENABLED(NEOPIXEL_LED)
          , bool isSequence=false
        #endif
      ) {
        set_color(MakeLEDColor(r, g, b, w, i)
          #if ENABLED(NEOPIXEL_LED)
            , isSequence
          #endif
        );
      }

      static uint8_t getBrightness();

      static void set_white();
      static inline void set_off()    { set_color(LEDColorOff()); }
      static inline void set_green()  { set_color(LEDColorGreen()); }

      #if ENABLED(LED_COLOR_PRESETS)
        static inline void set_default()  { set_color(defaultLEDColor); }
        static inline void set_red()      { set_color(LEDColorRed()); }
        static inline void set_orange()   { set_color(LEDColorOrange()); }
        static inline void set_yellow()   { set_color(LEDColorYellow()); }
        static inline void set_blue()     { set_color(LEDColorBlue()); }
        static inline void set_indigo()   { set_color(LEDColorIndigo()); }
        static inline void set_violet()   { set_color(LEDColorViolet()); }
      #endif

      #if ENABLED(PRINTER_EVENT_LEDS)
        static inline LEDColor get_color() { return lights_on ? color : LEDColorOff(); }
      #endif

      #if ENABLED(LED_CONTROL_MENU)
        static void toggle();  // swap "off" with color
        static inline void update() { set_color(color); }
      #endif

  };

  extern LEDLights leds;

#endif // HAS_COLOR_LEDS
