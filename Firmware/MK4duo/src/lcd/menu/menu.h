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

#if HAS_LCD_MENU

extern int8_t encoderLine, encoderTopLine, screen_items;
extern bool screen_changed;

void scroll_screen(const uint8_t limit, const bool is_menu);

////////////////////////////////////////////
////////// Menu Item Numeric Types /////////
////////////////////////////////////////////

#define DECLARE_MENU_EDIT_TYPE(TYPE, NAME, STRFUNC, SCALE) \
  struct MenuItemInfo_##NAME { \
    typedef TYPE type_t; \
    static constexpr float scale = SCALE; \
    static inline char* strfunc(const float value) { return STRFUNC((TYPE) value); } \
  };

DECLARE_MENU_EDIT_TYPE(int16_t,  int3,        itostr3,         1     );
DECLARE_MENU_EDIT_TYPE(int16_t,  int4,        itostr4sign,     1     );
DECLARE_MENU_EDIT_TYPE(uint8_t,  int8,        i8tostr3,        1     );
DECLARE_MENU_EDIT_TYPE(float,    float3,      ftostr3,         1     );
DECLARE_MENU_EDIT_TYPE(float,    float52,     ftostr52,      100     );
DECLARE_MENU_EDIT_TYPE(float,    float43,     ftostr43sign, 1000     );
DECLARE_MENU_EDIT_TYPE(float,    float5,      ftostr5rj,       0.01f );
DECLARE_MENU_EDIT_TYPE(float,    float51,     ftostr51sign,   10     );
DECLARE_MENU_EDIT_TYPE(float,    float52sign, ftostr52sign,  100     );
DECLARE_MENU_EDIT_TYPE(float,    float62,     ftostr62rj,    100     );
DECLARE_MENU_EDIT_TYPE(uint32_t, long5,       ftostr5rj,       0.01f );

////////////////////////////////////////////
///////// Menu Item Draw Functions /////////
////////////////////////////////////////////

void draw_edit_screen(PGM_P const pstr, const char* const value=NULL);
void draw_menu_item(const bool sel, const uint8_t row, PGM_P const pstr, const char pre_char, const char post_char);
void draw_menu_item_static(const uint8_t row, PGM_P const pstr, const bool center=true, const bool invert=false, const char *valstr=NULL);
void _draw_menu_item_edit(const bool sel, const uint8_t row, PGM_P const pstr, const char* const data, const bool pgm);
FORCE_INLINE void draw_menu_item_back(const bool sel, const uint8_t row, PGM_P const pstr) { draw_menu_item(sel, row, pstr, LCD_STR_UPLEVEL[0], LCD_STR_UPLEVEL[0]); }
FORCE_INLINE void draw_menu_item_edit(const bool sel, const uint8_t row, PGM_P const pstr, const char* const data) { _draw_menu_item_edit(sel, row, pstr, data, false); }
FORCE_INLINE void draw_menu_item_edit_P(const bool sel, const uint8_t row, PGM_P const pstr, const char* const data) { _draw_menu_item_edit(sel, row, pstr, data, true); }
#define draw_menu_item_submenu(sel, row, pstr, data)  draw_menu_item(sel, row, pstr, '>', LCD_STR_ARROW_RIGHT[0])
#define draw_menu_item_gcode(sel, row, pstr, gcode)   draw_menu_item(sel, row, pstr, '>', ' ')
#define draw_menu_item_function(sel, row, pstr, data) draw_menu_item(sel, row, pstr, '>', ' ')
#define DRAW_MENU_ITEM_SETTING_EDIT_GENERIC(VAL)      draw_menu_item_edit(sel, row, pstr, VAL)
#define DRAW_BOOL_SETTING(sel, row, pstr, data)       draw_menu_item_edit_P(sel, row, pstr, (*(data))?PSTR(MSG_ON):PSTR(MSG_OFF))

#if HAS_SD_SUPPORT
  class SDCard;
  void draw_sd_menu_item(const bool sel, const uint8_t row, PGM_P const pstr, SDCard &theCard, const bool isDir);
  FORCE_INLINE void draw_menu_item_sdfile(const bool sel, const uint8_t row, PGM_P const pstr, SDCard &theCard) { draw_sd_menu_item(sel, row, pstr, theCard, false); }
  FORCE_INLINE void draw_menu_item_sdfolder(const bool sel, const uint8_t row, PGM_P const pstr, SDCard &theCard) { draw_sd_menu_item(sel, row, pstr, theCard, true); }
#endif

#if HAS_GRAPHICAL_LCD && (ENABLED(BABYSTEP_ZPROBE_GFX_OVERLAY) || ENABLED(MESH_EDIT_GFX_OVERLAY))
  void _lcd_zoffset_overlay_gfx(const float zvalue);
#endif

////////////////////////////////////////////
/////// Edit Setting Draw Functions ////////
////////////////////////////////////////////

#define _DEFINE_DRAW_MENU_ITEM_SETTING_EDIT(TYPE, NAME, STRFUNC) \
  FORCE_INLINE void draw_menu_item_edit_##NAME (const bool sel, const uint8_t row, PGM_P const pstr, PGM_P const pstr2, TYPE * const data, ...) { \
    UNUSED(pstr2); \
    DRAW_MENU_ITEM_SETTING_EDIT_GENERIC(STRFUNC(*(data))); \
  } \
  FORCE_INLINE void draw_menu_item_edit_accessor_##NAME (const bool sel, const uint8_t row, PGM_P const pstr, PGM_P const pstr2, TYPE (*pget)(), void (*pset)(TYPE), ...) { \
    UNUSED(pstr2); UNUSED(pset); \
    DRAW_MENU_ITEM_SETTING_EDIT_GENERIC(STRFUNC(pget())); \
  } \
  typedef void NAME##_void
#define DEFINE_DRAW_MENU_ITEM_SETTING_EDIT(NAME) _DEFINE_DRAW_MENU_ITEM_SETTING_EDIT(MenuItemInfo_##NAME::type_t, NAME, MenuItemInfo_##NAME::strfunc)

DEFINE_DRAW_MENU_ITEM_SETTING_EDIT(int3);
DEFINE_DRAW_MENU_ITEM_SETTING_EDIT(int4);
DEFINE_DRAW_MENU_ITEM_SETTING_EDIT(int8);
DEFINE_DRAW_MENU_ITEM_SETTING_EDIT(float3);
DEFINE_DRAW_MENU_ITEM_SETTING_EDIT(float52);
DEFINE_DRAW_MENU_ITEM_SETTING_EDIT(float43);
DEFINE_DRAW_MENU_ITEM_SETTING_EDIT(float5);
DEFINE_DRAW_MENU_ITEM_SETTING_EDIT(float51);
DEFINE_DRAW_MENU_ITEM_SETTING_EDIT(float52sign);
DEFINE_DRAW_MENU_ITEM_SETTING_EDIT(float62);
DEFINE_DRAW_MENU_ITEM_SETTING_EDIT(long5);

#define draw_menu_item_edit_bool(sel, row, pstr, pstr2, data, ...)           DRAW_BOOL_SETTING(sel, row, pstr, data)
#define draw_menu_item_edit_accessor_bool(sel, row, pstr, pstr2, pget, pset) DRAW_BOOL_SETTING(sel, row, pstr, data)

////////////////////////////////////////////
/////////////// Menu Actions ///////////////
////////////////////////////////////////////

class MenuItem_back {
  public:
    static inline void action() { lcdui.goto_previous_screen(); }
};

class MenuItem_submenu {
  public:
    static inline void action(const screenFunc_t func) { lcdui.save_previous_screen(); lcdui.goto_screen(func); }
};

class MenuItem_gcode {
  public:
    static void action(const char * const pgcode);
};

class MenuItem_function {
  public:
    static inline void action(const menuAction_t func) { (*func)(); };
};

////////////////////////////////////////////
/////////// Menu Editing Actions ///////////
////////////////////////////////////////////

class MenuItemBase {
  protected:
    typedef char* (*strfunc_t)(const int32_t);
    typedef void (*loadfunc_t)(void *, const int32_t);
    static void init(PGM_P const el, void * const ev, const int32_t minv, const int32_t maxv, const uint32_t ep, const screenFunc_t cs, const screenFunc_t cb, const bool le);
    static void edit(strfunc_t, loadfunc_t);
};

template<typename NAME>
class TMenuItem : MenuItemBase {
  private:
    typedef typename NAME::type_t type_t;
    inline static float unscale(const float value)    { return value * (1.0f / NAME::scale);  }
    inline static float scale(const float value)      { return value * NAME::scale;           }
    static void  load(void *ptr, const int32_t value) { *((type_t*)ptr) = unscale(value);     }
    static char* to_string(const int32_t value)       { return NAME::strfunc(unscale(value)); }
  public:
    static void action_edit(PGM_P const pstr, type_t * const ptr, const type_t minValue, const type_t maxValue, const screenFunc_t callback=NULL, const bool live=false) {
      const int32_t minv = scale(minValue);
      init(pstr, ptr, minv, int32_t(scale(maxValue)) - minv, int32_t(scale(*ptr)) - minv, edit, callback, live);
    }
    static void edit() { MenuItemBase::edit(to_string, load); }
};

#define DECLARE_MENU_EDIT_ITEM(NAME) typedef TMenuItem<MenuItemInfo_##NAME> MenuItem_##NAME;

DECLARE_MENU_EDIT_ITEM(int3);
DECLARE_MENU_EDIT_ITEM(int4);
DECLARE_MENU_EDIT_ITEM(int8);
DECLARE_MENU_EDIT_ITEM(float3);
DECLARE_MENU_EDIT_ITEM(float52);
DECLARE_MENU_EDIT_ITEM(float43);
DECLARE_MENU_EDIT_ITEM(float5);
DECLARE_MENU_EDIT_ITEM(float51);
DECLARE_MENU_EDIT_ITEM(float52sign);
DECLARE_MENU_EDIT_ITEM(float62);
DECLARE_MENU_EDIT_ITEM(long5);

class MenuItem_bool {
  public:
    static void action_edit(PGM_P const pstr, bool* ptr, const screenFunc_t callbackFunc=NULL);
};

////////////////////////////////////////////
//////////// Menu System Macros ////////////
////////////////////////////////////////////

/**
 * SCREEN_OR_MENU_LOOP generates init code for a screen or menu
 *
 *   encoderTopLine is the top menu line to display
 *   _lcdLineNr is the index of the LCD line (e.g., 0-3)
 *   _menuLineNr is the menu item to draw and process
 *   _thisItemNr is the index of each MENU_ITEM or STATIC_ITEM
 */
#define SCREEN_OR_MENU_LOOP() \
  int8_t _menuLineNr = encoderTopLine, _thisItemNr; \
  for (int8_t _lcdLineNr = 0; _lcdLineNr < LCD_HEIGHT; _lcdLineNr++, _menuLineNr++) { \
    _thisItemNr = 0

/**
 * START_SCREEN  Opening code for a screen having only static items.
 *               Do simplified scrolling of the entire screen.
 *
 * START_MENU    Opening code for a screen with menu items.
 *               Scroll as-needed to keep the selected line in view.
 */
#define START_SCREEN() \
  scroll_screen(LCD_HEIGHT, false); \
  bool _skipStatic = false; \
  SCREEN_OR_MENU_LOOP()

#define START_MENU() \
  scroll_screen(1, true); \
  bool _skipStatic = true; \
  SCREEN_OR_MENU_LOOP()

#define END_SCREEN() \
  } \
  screen_items = _thisItemNr

#define END_MENU() \
  } \
  screen_items = _thisItemNr; \
  UNUSED(_skipStatic)

#if ENABLED(ENCODER_RATE_MULTIPLIER)
  #define ENCODER_RATE_MULTIPLY(F) (lcdui.encoderRateMultiplierEnabled = F)
  #define _MENU_ITEM_MULTIPLIER_CHECK(USE_MULTIPLIER) do{ if (USE_MULTIPLIER) lcdui.enable_encoder_multiplier(true); }while(0)
  //#define ENCODER_RATE_MULTIPLIER_DEBUG  // If defined, output the encoder steps per second value
#else
  #define ENCODER_RATE_MULTIPLY(F) NOOP
  #define _MENU_ITEM_MULTIPLIER_CHECK(USE_MULTIPLIER)
#endif

/**
 * MENU_ITEM generates draw & handler code for a menu item, potentially calling:
 *
 *   draw_menu_item_<type>[_variant](sel, row, label, arg3...)
 *   MenuItem_<type>::action[_variant](arg3...)
 *
 * Examples:
 *   MENU_ITEM(back, MSG_WATCH, 0 [dummy parameter] )
 *   or
 *   MENU_BACK(MSG_WATCH)
 *     draw_menu_item_back(sel, row, PSTR(MSG_WATCH))
 *     MenuItem_back::action()
 *
 *   MENU_ITEM(function, MSG_PAUSE_PRINT, lcd_sdcard_pause)
 *     draw_menu_item_function(sel, row, PSTR(MSG_PAUSE_PRINT), lcd_sdcard_pause)
 *     MenuItem_function::action(lcd_sdcard_pause)
 *
 *   MENU_ITEM_EDIT(int3, MSG_SPEED, &feedrate_percentage, 10, 999)
 *     draw_menu_item_edit_int3(sel, row, PSTR(MSG_SPEED), PSTR(MSG_SPEED), &feedrate_percentage, 10, 999)
 *     MenuItem_int3::action_edit(PSTR(MSG_SPEED), &feedrate_percentage, 10, 999)
 *
 */
#define _MENU_ITEM_VARIANT_P(TYPE, VARIANT, USE_MULTIPLIER, PLABEL, ...) do { \
    _skipStatic = false; \
    if (_menuLineNr == _thisItemNr) { \
      if (encoderLine == _thisItemNr && lcdui.use_click()) { \
        _MENU_ITEM_MULTIPLIER_CHECK(USE_MULTIPLIER); \
        MenuItem_##TYPE ::action ## VARIANT(__VA_ARGS__); \
        if (screen_changed) return; \
      } \
      if (lcdui.should_draw()) \
        draw_menu_item ## VARIANT ## _ ## TYPE(encoderLine == _thisItemNr, _lcdLineNr, PLABEL, ## __VA_ARGS__); \
    } \
  ++_thisItemNr; \
}while(0)

// Used to print static text with no visible cursor.
// Parameters: label [, bool center [, bool invert [, char *value] ] ]
#define STATIC_ITEM_P(PLABEL, ...) do{ \
  if (_menuLineNr == _thisItemNr) { \
    if (_skipStatic && encoderLine <= _thisItemNr) { \
      lcdui.encoderPosition += ENCODER_STEPS_PER_MENU_ITEM; \
      ++encoderLine; \
    } \
    if (lcdui.should_draw()) \
      draw_menu_item_static(_lcdLineNr, PLABEL, ## __VA_ARGS__); \
  } \
  ++_thisItemNr; \
} while(0)

#define MENU_ITEM_ADDON_START(X) \
  if (lcdui.should_draw() && _menuLineNr == _thisItemNr - 1) { \
    SETCURSOR(X, _lcdLineNr)

#define MENU_ITEM_ADDON_END() } (0)

#define STATIC_ITEM(LABEL, ...)                               STATIC_ITEM_P(PSTR(LABEL), ## __VA_ARGS__)

#define MENU_BACK(LABEL)                                      MENU_ITEM(back, LABEL)
#define MENU_ITEM_DUMMY()                                     do { _thisItemNr++; }while(0)
#define MENU_ITEM_P(TYPE, PLABEL, ...)                        _MENU_ITEM_VARIANT_P(TYPE,             , false,        PLABEL,       ## __VA_ARGS__)
#define MENU_ITEM(TYPE, LABEL, ...)                           _MENU_ITEM_VARIANT_P(TYPE,             , false,        PSTR(LABEL),  ## __VA_ARGS__)
#define MENU_ITEM_EDIT(TYPE, LABEL, ...)                      _MENU_ITEM_VARIANT_P(TYPE, _edit, false, PSTR(LABEL),  PSTR(LABEL),  ## __VA_ARGS__)
#define MENU_ITEM_EDIT_CALLBACK(TYPE, LABEL, ...)             _MENU_ITEM_VARIANT_P(TYPE, _edit, false, PSTR(LABEL),  PSTR(LABEL),  ## __VA_ARGS__)
#define MENU_MULTIPLIER_ITEM_EDIT(TYPE, LABEL, ...)           _MENU_ITEM_VARIANT_P(TYPE, _edit,  true, PSTR(LABEL),  PSTR(LABEL),  ## __VA_ARGS__)
#define MENU_MULTIPLIER_ITEM_EDIT_CALLBACK(TYPE, LABEL, ...)  _MENU_ITEM_VARIANT_P(TYPE, _edit,  true, PSTR(LABEL),  PSTR(LABEL),  ## __VA_ARGS__)

////////////////////////////////////////////
/////////////// Menu Screens ///////////////
////////////////////////////////////////////

void menu_main();
void menu_move();

#if HAS_SD_SUPPORT
  void menu_sdcard();
  void menu_stop_print();
#endif

#if HAS_EEPROM
  void menu_eeprom();
#endif

#if HAS_NEXTION_LCD
  void menu_nextion();
  #if HAS_SD_SUPPORT
    void menu_firmware();
  #endif
#endif

// First Fan Speed title in "Tune" and "Control>Temperature" menus
#if FAN_COUNT > 0 && HAS_FAN0
  #if FAN_COUNT > 1
    #define FAN_SPEED_1_SUFFIX " 1"
  #else
    #define FAN_SPEED_1_SUFFIX ""
  #endif
#endif

////////////////////////////////////////////
//////// Menu Item Helper Functions ////////
////////////////////////////////////////////

void lcd_move_z();
void _lcd_draw_homing();

void watch_temp_callback_E0();
void watch_temp_callback_E1();
void watch_temp_callback_E2();
void watch_temp_callback_E3();
void watch_temp_callback_E4();
void watch_temp_callback_E5();
void watch_temp_callback_bed();
void watch_temp_callback_chamber();
void watch_temp_callback_cooler();

#define HAS_LINE_TO_Z (MECH(DELTA) || ENABLED(PROBE_MANUALLY) || ENABLED(MESH_BED_LEVELING) || ENABLED(LEVEL_BED_CORNERS))

#if HAS_LINE_TO_Z
  void line_to_z(const float &z);
#endif

#if ENABLED(AUTO_BED_LEVELING_UBL) || ENABLED(PID_AUTOTUNE_MENU) || ENABLED(ADVANCED_PAUSE_FEATURE)
  void lcd_enqueue_command(const char * const cmd);
  void lcd_enqueue_commands_P(PGM_P const cmd);
#endif

#if ENABLED(LEVEL_BED_CORNERS)
  void _lcd_level_bed_corners();
#endif

#if ENABLED(ENABLE_LEVELING_FADE_HEIGHT)
  extern float lcd_z_fade_height;
  void _lcd_set_z_fade_height();
#endif

#if ENABLED(LCD_BED_LEVELING) || (HAS_LEVELING && DISABLED(SLIM_LCD_MENUS))
  void _lcd_toggle_bed_leveling();
#endif

#if HAS_SOFTWARE_ENDSTOPS
  void _lcd_toggle_soft_endstops(); 
#endif

#if ENABLED(BABYSTEPPING)
  #if ENABLED(BABYSTEP_ZPROBE_OFFSET)
    void lcd_babystep_zoffset();
  #else
    void lcd_babystep_z();
  #endif
#endif

#if ENABLED(EEPROM_SETTINGS)
  void lcd_store_settings();
  void lcd_load_settings();
#endif

#if HAS_SD_RESTART
  void menu_sdcard_restart();
#endif

#endif // HAS_LCD_MENU
