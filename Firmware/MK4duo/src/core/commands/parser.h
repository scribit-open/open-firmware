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
 * parser.h - Parser for a GCode line, providing a parameter interface.
 *            Codes like M149 control the way the GCode parser behaves,
 *            so settings for these codes are located in this class.
 */

//#define DEBUG_GCODE_PARSER

/**
 * Parser Gcode
 *
 *  - Parse a single gcode line for its letter, code, subcode, and parameters
 *  - FASTER_GCODE_PARSER:
 *    - Flags existing params (1 bit each)
 *    - Stores value offsets (1 byte each)
 *  - Provide accessors for parameters:
 *    - Parameter exists
 *    - Parameter has value
 *    - Parameter value in different units and types
 */
class GCodeParser {

  public: /** Public Parameters */

    // Global states for GCode-level units features
    #if ENABLED(INCH_MODE_SUPPORT)
      static float  linear_unit_factor,
                    volumetric_unit_factor;
    #endif

    #if ENABLED(TEMPERATURE_UNITS_SUPPORT)
      static TempUnitEnum input_temp_units;
    #endif

    // Command line state
    static char *command_ptr,     // The command, so it can be echoed
                *string_arg;      // string of command line

    static char command_letter;  // G, M, or T

    static uint16_t codenum;      // 123

    #if USE_GCODE_SUBCODES
      static uint8_t subcode;     // .1
    #endif

  private: /** Private Parameters */

    static char *value_ptr;       // Set by seen, used to fetch the value

    #if ENABLED(FASTER_GCODE_PARSER)
      static uint32_t codebits;   // Parameters pre-scanned
      static uint8_t param[26];   // For A-Z, offsets into command args
    #else
      static char *command_args;  // Args start here, for slow scan
    #endif

  public: /** Public Function */

    #if ENABLED(DEBUG_GCODE_PARSER)
      static void debug();
    #endif

    // Reset is done before parsing
    static void reset();

    #define LETTER_BIT(N) ((N) - 'A')

    FORCE_INLINE static bool valid_signless(PGM_P const p) {
      return NUMERIC(p[0]) || (p[0] == '.' && NUMERIC(p[1])); // .?[0-9]
    }

    FORCE_INLINE static bool valid_float(PGM_P const p) {
      return valid_signless(p) || ((p[0] == '-' || p[0] == '+') && valid_signless(&p[1])); // [-+]?.?[0-9]
    }

    FORCE_INLINE static bool valid_int(PGM_P const p) {
      return NUMERIC(p[0]) || ((p[0] == '-' || p[0] == '+') && NUMERIC(p[1])); // [-+]?[0-9]
    }

    #if ENABLED(FASTER_GCODE_PARSER)

      // Set the flag and pointer for a parameter
      static inline void set(const char c, char * const ptr) {
        const uint8_t ind = LETTER_BIT(c);
        if (ind >= COUNT(param)) return;           // Only A-Z
        SBI32(codebits, ind);                      // parameter exists
        param[ind] = ptr ? ptr - command_ptr : 0;  // parameter offset or 0
        #if ENABLED(DEBUG_GCODE_PARSER)
          if (codenum == 800) {
            SERIAL_MV("Set bit ", (int)ind);
            SERIAL_MV(" of codebits (", hex_address((void*)(codebits >> 16)));
            print_hex_word((uint16_t)(codebits & 0xFFFF));
            SERIAL_EMV(" | param = ",(int)param[ind]);
          }
        #endif
      }

      // Code seen bit was set. If not found, value_ptr is unchanged.
      // This allows "if (seen('A')||seen('B'))" to use the last-found value.
      static inline bool seen(const char c) {
        const uint8_t ind = LETTER_BIT(c);
        if (ind >= COUNT(param)) return false; // Only A-Z
        const bool b = TEST32(codebits, ind);
        if (b) {
          char * const ptr = command_ptr + param[ind];
          value_ptr = param[ind] && valid_float(ptr) ? ptr : (char*)NULL;
        }
        return b;
      }

      FORCE_INLINE static constexpr uint32_t letter_bits(const char * const str) {
        return  (str[0] ? _BV32(LETTER_BIT(str[0])) |
                (str[1] ? _BV32(LETTER_BIT(str[1])) |
                (str[2] ? _BV32(LETTER_BIT(str[2])) |
                (str[3] ? _BV32(LETTER_BIT(str[3])) |
                (str[4] ? _BV32(LETTER_BIT(str[4])) |
                (str[5] ? _BV32(LETTER_BIT(str[5])) |
                (str[6] ? _BV32(LETTER_BIT(str[6])) |
                (str[7] ? _BV32(LETTER_BIT(str[7])) |
                (str[8] ? _BV32(LETTER_BIT(str[8])) |
                (str[9] ? _BV32(LETTER_BIT(str[9]))
              : 0) : 0) : 0) : 0) : 0) : 0) : 0) : 0) : 0) : 0);
      }

      // At least one of a list of code letters was seen
      #if ENABLED(CPU_32_BIT)
        FORCE_INLINE static bool seen(const char * const str) { return !!(codebits & letter_bits(str)); }
      #else
        // At least one of a list of code letters was seen
        FORCE_INLINE static bool seen(const char * const str) {
          const uint32_t letrbits = letter_bits(str);
          const uint8_t * const cb = (uint8_t*)&codebits;
          const uint8_t * const lb = (uint8_t*)&letrbits;
          return (cb[0] & lb[0]) || (cb[1] & lb[1]) || (cb[2] & lb[2]) || (cb[3] & lb[3]);
        }
      #endif

      static inline bool seen_any() { return !!codebits; }

      #define SEEN_TEST(L) TEST32(codebits, LETTER_BIT(L))

    #else // !FASTER_GCODE_PARSER

      // Code is found in the string. If not found, value_ptr is unchanged.
      // This allows "if (seen('A')||seen('B'))" to use the last-found value.
      // p DEVE ESSERE CHAR e non CONST CHAR
      static inline bool seen(const char c) {
        char *p = strchr(command_args, c);
        const bool b = !!p;
        if (b) value_ptr = valid_float(&p[1]) ? &p[1] : (char*)NULL;
        return b;
      }

      static inline bool seen_any() { return *command_args == '\0'; }

      #define SEEN_TEST(L) !!strchr(command_args, L)

      // At least one of a list of code letters was seen
      static inline bool seen(const char * const str) {
        for (uint8_t i = 0; const char c = str[i]; i++)
          if (SEEN_TEST(c)) return true;
        return false;
      }

    #endif // !FASTER_GCODE_PARSER

    // Seen any axis parameter
    static inline bool seen_axis() {
      return SEEN_TEST('X') || SEEN_TEST('Y') || SEEN_TEST('Z') || SEEN_TEST('E');
    }

    // Populate all fields by parsing a single line of GCode
    // This uses 54 bytes of SRAM to speed up seen/value
    static void parse(char * p);

    // Code value pointer was set
    FORCE_INLINE static bool has_value() { return value_ptr != NULL; }

    // Seen a parameter with a value
    static inline bool seenval(const char c) { return seen(c) && has_value(); }

    // Float removes 'E' to prevent scientific notation interpretation
    static inline float value_float() {
      if (value_ptr) {
        char *e = value_ptr;
        for (;;) {
          const char c = *e;
          if (c == '\0' || c == ' ') break;
          if (c == 'E' || c == 'e') {
            *e = '\0';
            const float ret = strtof(value_ptr, NULL);
            *e = c;
            return ret;
          }
          ++e;
        }
        return strtof(value_ptr, NULL);
      }
      return 0;
    }

    // Code value as a long or ulong
    static inline int32_t   value_long()  { return value_ptr ? strtol(value_ptr, NULL, 10) : 0L; }
    static inline uint32_t  value_ulong() { return value_ptr ? strtoul(value_ptr, NULL, 10) : 0UL; }

    // Code value for use as time
    static inline millis_t  value_millis()              { return value_ulong(); }
    static inline millis_t  value_millis_from_seconds() { return (millis_t)(value_float() * 1000); }

    // Reduce to fewer bits
    static inline int16_t   value_int()     { return  (int16_t)value_long(); }
    static inline uint16_t  value_ushort()  { return (uint16_t)value_long(); }
    static inline uint8_t         value_byte()    { return  (uint8_t)constrain(value_long(), 0, 255); }

    // Bool is true with no value or non-zero
    static inline bool            value_bool()    { return !has_value() || !!value_byte(); }

    // Pin value
    static pin_t value_pin();
    static pin_t analog_value_pin();

    // Units modes: Inches, Fahrenheit, Kelvin

    #if ENABLED(INCH_MODE_SUPPORT)

      static float axis_unit_factor(const AxisEnum axis);

      static inline void set_input_linear_units(float factor) {
        linear_unit_factor = factor;
        volumetric_unit_factor = POW(linear_unit_factor, 3);
      }

      static inline float value_linear_units()                     { return value_float() * linear_unit_factor; }
      static inline float value_axis_units(const AxisEnum axis)    { return value_float() * axis_unit_factor(axis); }
      static inline float value_per_axis_unit(const AxisEnum axis) { return value_float() / axis_unit_factor(axis); }

    #else

      static inline float value_linear_units()                  {            return value_float(); }
      static inline float value_axis_units(const AxisEnum a)    { UNUSED(a); return value_float(); }
      static inline float value_per_axis_unit(const AxisEnum a) { UNUSED(a); return value_float(); }

    #endif

    #if ENABLED(TEMPERATURE_UNITS_SUPPORT)

      static inline void set_input_temp_units(TempUnitEnum units) { input_temp_units = units; }

      #if ENABLED(ULTIPANEL) && DISABLED(DISABLE_M503)

        static inline char temp_units_code() {
          return input_temp_units == TEMPUNIT_K ? 'K' : input_temp_units == TEMPUNIT_F ? 'F' : 'C';
        }

        static inline char* temp_units_name() {
          return input_temp_units == TEMPUNIT_K ? PSTR("Kelvin") : input_temp_units == TEMPUNIT_F ? PSTR("Fahrenheit") : PSTR("Celsius");
        }

        static inline float to_temp_units(const float &f) {
          switch (input_temp_units) {
            case TEMPUNIT_F:
              return f * 0.5555555556f + 32;
            case TEMPUNIT_K:
              return f + 273.15f;
            case TEMPUNIT_C:
            default:
              return f;
          }
        }

      #endif // ULTIPANEL && !DISABLE_M503

      static inline float value_celsius() {
        const float f = value_float();
        switch (input_temp_units) {
          case TEMPUNIT_F:
            return (f - 32.0f) * 0.5555555556f;
          case TEMPUNIT_K:
            return f - 273.15f;
          case TEMPUNIT_C:
          default:
            return f;
        }
      }

      static inline float value_celsius_diff() {
        switch (input_temp_units) {
          case TEMPUNIT_F:
            return value_float() * 0.5555555556f;
          case TEMPUNIT_C:
          case TEMPUNIT_K:
          default:
            return value_float();
        }
      }

    #else // !TEMPERATURE_UNITS_SUPPORT

      static inline float value_celsius()      { return value_float(); }
      static inline float value_celsius_diff() { return value_float(); }

    #endif // !TEMPERATURE_UNITS_SUPPORT

    static inline float value_feedrate() { return value_linear_units(); }

    // Provide simple value accessors with default option
    static inline float     floatval(const char c, const float dval=0.0)    { return seenval(c) ? value_float()         : dval; }
    static inline bool      boolval(const char c, const bool dval=false)    { return seenval(c) ? value_bool()          : (seen(c) ? true : dval); }
    static inline uint8_t   byteval(const char c, const uint8_t dval=0)     { return seenval(c) ? value_byte()          : dval; }
    static inline int16_t   intval(const char c, const int16_t dval=0)      { return seenval(c) ? value_int()           : dval; }
    static inline uint16_t  ushortval(const char c, const uint16_t dval=0)  { return seenval(c) ? value_ushort()        : dval; }
    static inline int32_t   longval(const char c, const int32_t dval=0)     { return seenval(c) ? value_long()          : dval; }
    static inline uint32_t  ulongval(const char c, const uint32_t dval=0)   { return seenval(c) ? value_ulong()         : dval; }
    static inline float     linearval(const char c, const float dval=0)     { return seenval(c) ? value_linear_units()  : dval; }
    static inline float     celsiusval(const char c, const float dval=0)    { return seenval(c) ? value_celsius()       : dval; }
    static inline pin_t     pinval(const char c, const uint8_t dval=NoPin)  { return seenval(c) ? value_pin()           : dval; }

  private: /** Private Function */

};

extern GCodeParser parser;
