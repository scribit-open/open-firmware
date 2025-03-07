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

#define _UxGT(a) a

// Fallback if no language is set. DON'T CHANGE
#if DISABLED(LCD_LANGUAGE)
  #define LCD_LANGUAGE en
#endif

#define PROTOCOL_VERSION "2.0"

// For character-based LCD controllers (DISPLAY_CHARSET_HD44780)
#define JAPANESE 1
#define WESTERN  2
#define CYRILLIC 3

//Machine name
#if ENABLED(CUSTOM_MACHINE_NAME)
  #define MACHINE_NAME CUSTOM_MACHINE_NAME
#else
  #define MACHINE_NAME BOARD_NAME
#endif

// LCD Menu Messages
#if DISABLED(DISPLAY_CHARSET_HD44780_JAPAN) && DISABLED(DISPLAY_CHARSET_HD44780_WESTERN) && DISABLED(DISPLAY_CHARSET_HD44780_CYRILLIC)
  #define DISPLAY_CHARSET_HD44780_JAPAN
#endif

// Serial Console Messages (do not translate those!)
#if MECH(CARTESIAN)
  #define MACHINE_TYPE                      "Cartesian"
#elif MECH(COREXY)
  #define MACHINE_TYPE                      "CoreXY"
#elif MECH(COREYX)
  #define MACHINE_TYPE                      "CoreYX"
#elif MECH(COREXZ)
  #define MACHINE_TYPE                      "CoreXZ"
#elif MECH(COREZX)
  #define MACHINE_TYPE                      "CoreZX"
#elif MECH(COREYZ)
  #define MACHINE_TYPE                      "CoreYZ"
#elif MECH(COREZY)
  #define MACHINE_TYPE                      "CoreZY"
#elif MECH(DELTA)
  #define MACHINE_TYPE                      "Delta"
#elif MECH(MORGAN_SCARA)
  #define MACHINE_TYPE                      "Morgan Scara"
#elif MECH(MAKERARM_SCARA)
  #define MACHINE_TYPE                      "MakerArm Scara"
#elif MECH(MUVE3D)
  #define MACHINE_TYPE                      "Muve3D"
#endif  

#if HAS_GRAPHICAL_LCD
  //
  // Custom characters from MK4duo_symbols.fon which was merged into ISO10646-0-3.bdf
  // \x00 intentionally skipped to avoid problems in strings
  //
  #define LCD_STR_REFRESH     "\x01"
  #define LCD_STR_FOLDER      "\x02"
  #define LCD_STR_ARROW_RIGHT "\x03"
  #define LCD_STR_UPLEVEL     "\x04"
  #define LCD_STR_CLOCK       "\x05"
  #define LCD_STR_FEEDRATE    "\x06"
  #define LCD_STR_BEDTEMP     "\x07"
  #define LCD_STR_THERMOMETER "\x08"
  #define LCD_STR_DEGREE      "\x09"

  #define LCD_STR_SPECIAL_MAX '\x09'
  // Maximum here is 0x1F because 0x20 is ' ' (space) and the normal charsets begin.
  // Better stay below 0x10 because DISPLAY_CHARSET_HD44780_WESTERN begins here.

  // Symbol characters
  #define LCD_STR_FILAM_DIA   "\xF8"
  #define LCD_STR_FILAM_MUL   "\xA4"

#elif HAS_CHARACTER_LCD

  // Custom characters defined in the first 8 characters of the LCD
  #define LCD_STR_BEDTEMP     "\x00" // Print only as a char. This will have 'unexpected' results when used in a string!
  #define LCD_STR_DEGREE      "\x01"
  #define LCD_STR_THERMOMETER "\x02" // Still used with string concatenation
  #define LCD_STR_UPLEVEL     "\x03"
  #define LCD_STR_REFRESH     "\x04"
  #define LCD_STR_FOLDER      "\x05"
  #define LCD_STR_FEEDRATE    "\x06"
  #define LCD_STR_CLOCK       "\x07"
  #define LCD_STR_ARROW_RIGHT ">"  /* from the default character set */

#elif HAS_NEXTION_LCD

  #define LCD_STR_BEDTEMP     ""
  #define LCD_STR_DEGREE      "°"
  #define LCD_STR_THERMOMETER ""
  #define LCD_STR_UPLEVEL     ""
  #define LCD_STR_REFRESH     ""
  #define LCD_STR_FOLDER      "|^"
  #define LCD_STR_FEEDRATE    ""
  #define LCD_STR_CLOCK       ""
  #define LCD_STR_ARROW_RIGHT ">"

#endif

#define MSG_ENQUEUEING                      "enqueueing \""
#define MSG_POWERUP                         "PowerUp"
#define MSG_EXTERNAL_RESET                  "External Reset"
#define MSG_BROWNOUT_RESET                  "Brown out Reset"
#define MSG_WATCHDOG_RESET                  "Watchdog Reset"
#define MSG_SOFTWARE_RESET                  "Software Reset"
#define MSG_AUTHOR                          " | Author: "
#define MSG_CONFIGURATION_VER               "Last Updated: "
#define MSG_COMPILED                        "Compiled: "
#define MSG_FREE_MEMORY                     "Free Memory: "
#define MSG_PLANNER_BUFFER_BYTES            " PlannerBufferBytes: "
#define MSG_STATS                           "Stats: "
#define MSG_ERR_LINE_NO                     "Line Number is not Last Line Number+1, Last Line: "
#define MSG_ERR_CHECKSUM_MISMATCH           "checksum mismatch, Last Line: "
#define MSG_ERR_NO_CHECKSUM                 "No Checksum with line number, Last Line: "
#define MSG_FILE_PRINTED                    "Done printing file"
#define MSG_BEGIN_FILE_LIST                 "Begin file list"
#define MSG_END_FILE_LIST                   "End file list"
#define MSG_INVALID_EXTRUDER                "Invalid extruder"
#define MSG_INVALID_HOTEND                  "Invalid hotend"
#define MSG_INVALID_HEATER                  "Invalid heater"
#define MSG_INVALID_SOLENOID                "Invalid solenoid"
#define MSG_ERR_NO_THERMISTORS              "No thermistors - no temperature"
#define MSG_M115_REPORT                     "FIRMWARE_NAME:MK4duo " SHORT_BUILD_VERSION " FIRMWARE_URL:" FIRMWARE_URL " PROTOCOL_VERSION:" PROTOCOL_VERSION " MACHINE_TYPE:" MACHINE_TYPE " EXTRUDER_COUNT:" STRINGIFY(EXTRUDERS) " UUID:" MACHINE_UUID "\n"
#define MSG_COUNT_X                         " Count X:"
#define MSG_COUNT_A                         " Count A:"
#define MSG_COUNT_ALPHA                     " Count Alpha:"
#define MSG_ERR_KILLED                      "Printer halted. kill() called!"
#define MSG_ERR_STOPPED                     "Printer stopped due to errors. Fix the error and use M999 to restart. (Temperature is reset. Set it after restarting)"
#define MSG_BUSY_PROCESSING                 "processing"
#define MSG_BUSY_WAIT_HEATER                "heating"
#define MSG_BUSY_DOOR_OPEN                  "door open"
#define MSG_BUSY_PAUSED_FOR_USER            "paused for user"
#define MSG_BUSY_PAUSED_FOR_INPUT           "paused for input"
#define MSG_UNKNOWN_COMMAND                 "Unknown command: \""
#define MSG_ACTIVE_DRIVER                   "Active Driver: "
#define MSG_ACTIVE_EXTRUDER                 "Active Extruder: "
#define MSG_ACTIVE_COLOR                    "Active Color: "
#define MSG_X_MIN                           "x_min"
#define MSG_X_MAX                           "x_max"
#define MSG_X2_MIN                          "x2_min"
#define MSG_X2_MAX                          "x2_max"
#define MSG_Y_MIN                           "y_min"
#define MSG_Y_MAX                           "y_max"
#define MSG_Y2_MIN                          "y2_min"
#define MSG_Y2_MAX                          "y2_max"
#define MSG_Z_MIN                           "z_min"
#define MSG_Z_MAX                           "z_max"
#define MSG_Z2_MIN                          "z2_min"
#define MSG_Z2_MAX                          "z2_max"
#define MSG_Z3_MIN                          "z3_min"
#define MSG_Z3_MAX                          "z3_max"
#define MSG_Z_PROBE                         "z_probe"
#define MSG_E_MIN                           "e_min"
#define MSG_PROBE_Z_OFFSET                  "Probe Z Offset"
#define MSG_FILAMENT_RUNOUT                 "filament"
#define MSG_DOOR_OPEN                       "door"
#define MSG_POWER_CHECK                     "power check"
#define MSG_ERR_MATERIAL_INDEX              "M145 S<index> out of range (0-2)"
#define MSG_ERR_M421_PARAMETERS             "M421 incorrect parameter usage"
#define MSG_ERR_MESH_XY                     "Mesh point cannot be resolved"
#define MSG_ERR_ARC_ARGS                    "G2/G3 bad parameters"
#define MSG_ERR_PROTECTED_PIN               "Protected Pin"
#define MSG_ERR_M420_FAILED                 "Failed to enable Bed Leveling"
#define MSG_ERR_M428_TOO_FAR                "Too far from reference point"
#define MSG_ERR_M303_DISABLED               "PIDTEMP disabled"
#define MSG_M119_REPORT                     "Reporting endstop status"
#define MSG_ENDSTOP_HIT                     "TRIGGERED"
#define MSG_ENDSTOP_OPEN                    "NOT TRIGGERED"
#define MSG_HOTEND_OFFSET                   "Hotend offsets:"
#define MSG_DUPLICATION_MODE                "Duplication mode: "
#define MSG_SOFT_ENDSTOPS                   "Soft endstops: "
#define MSG_SOFT_MIN                        "  Min:"
#define MSG_SOFT_MAX                        "  Max:"

// SD Card
#define MSG_SD_CANT_OPEN_SUBDIR             "Cannot open subdir "
#define MSG_SD_ERRORCODE                    "SD errorCode:"
#define MSG_SD_INIT_FAIL                    "SD init fail"
#define MSG_SD_CARD_OK                      "SD card ok"
#define MSG_SD_OPEN_FILE_FAIL               "open failed, File: "
#define MSG_SD_FILE_OPENED                  "File opened: "
#define MSG_SD_SIZE                         " Size: "
#define MSG_SD_FILE_SELECTED                "File selected"
#define MSG_SD_WRITE_TO_FILE                "Writing to file: "
#define MSG_SD_FILE_SAVED                   "Done saving file."
#define MSG_SD_PRINTING_BYTE                "SD printing byte "
#define MSG_SD_NOT_PRINTING                 "Not SD printing"
#define MSG_SD_ERR_WRITE_TO_FILE            "error writing to file"
#define MSG_SD_ERR_READ                     "SD read error"
#define MSG_SD_CANT_ENTER_SUBDIR            "Cannot enter subdir: "
#define MSG_SD_FILE_DELETED                 "File deleted"
#define MSG_SD_FILE_DELETION_ERR            "Deletion failed"
#define MSG_SD_DIRECTORY_CREATED            "Directory created"
#define MSG_SD_CREATION_FAILED              "Creation failed"
#define MSG_SD_SLASH                        "/"
#define MSG_SD_MAX_DEPTH                    "trying to call sub-gcode files with too many levels. MAX level is:"

#define MSG_ENDSTOPS_HIT                    "endstops hit: "
#define MSG_ERR_COLD_EXTRUDE_STOP           "cold extrusion prevented"
#define MSG_ERR_LONG_EXTRUDE_STOP           "too long extrusion prevented"

#define MSG_FILAMENT_CHANGE_HEAT            "Press button (or M108) to heat nozzle"
#define MSG_FILAMENT_CHANGE_INSERT          "Insert filament and press button (or M108)"
#define MSG_FILAMENT_CHANGE_WAIT            "Press button (or M108) to resume"
#define MSG_FILAMENT_CHANGE_HEAT_LCD        "Press button to heat nozzle"
#define MSG_FILAMENT_CHANGE_INSERT_LCD      "Insert filament and press button"
#define MSG_FILAMENT_CHANGE_WAIT_LCD        "Press button to resume"
#define MSG_FILAMENT_CHANGE_HEAT_M108       "Send M108 to heat nozzle"
#define MSG_FILAMENT_CHANGE_INSERT_M108     "Insert filament and send M108"
#define MSG_FILAMENT_CHANGE_WAIT_M108       "Send M108 to resume"

#define MSG_ERR_EEPROM_WRITE                "Error writing to EEPROM!"

#define MSG_STOP_BLTOUCH                    "STOP called because of BLTouch error - restart with M999"
#define MSG_STOP_UNHOMED                    "STOP called because of unhomed error - restart with M999"
#define MSG_KILL_INACTIVE_TIME              "KILL caused by too much inactive time - current command: "
#define MSG_KILL_BUTTON                     "KILL caused by KILL button/pin"

#define MSG_MICROSTEP_MS1_MS2               "MS1,MS2 Pins"
#define MSG_MICROSTEP_X                     "X:"
#define MSG_MICROSTEP_Y                     "Y:"
#define MSG_MICROSTEP_Z                     "Z:"
#define MSG_MICROSTEP_E0                    "E0:"
#define MSG_MICROSTEP_E1                    "E1:"

// temperature.cpp strings
#define MSG_PID_AUTOTUNE                    "PID Autotune"
#define MSG_PID_AUTOTUNE_START              MSG_PID_AUTOTUNE " start"
#define MSG_PID_AUTOTUNE_FAILED             MSG_PID_AUTOTUNE " failed!"
#define MSG_PID_TEMP_TOO_HIGH               MSG_PID_AUTOTUNE_FAILED " Temperature too high"
#define MSG_PID_TEMP_TOO_LOW                MSG_PID_AUTOTUNE_FAILED " Temperature too low"
#define MSG_PID_TIMEOUT                     MSG_PID_AUTOTUNE_FAILED " timeout"
#define MSG_BIAS                            " bias: "
#define MSG_D                               " d: "
#define MSG_T_MIN                           " min: "
#define MSG_T_MAX                           " max: "
#define MSG_KU                              " Ku: "
#define MSG_TU                              " Tu: "
#define MSG_CLASSIC_PID                     " Classic PID"
#define MSG_SOME_OVERSHOOT_PID              " Some Overshoot PID"
#define MSG_NO_OVERSHOOT_PID                " No Overshoot PID"
#define MSG_PESSEN_PID                      " Pessen Integral Rule PID"
#define MSG_TYREUS_LYBEN_PID                " Tyreus-Lyben PID"
#define MSG_KP                              " Kp: "
#define MSG_KI                              " Ki: "
#define MSG_KD                              " Kd: "
#define MSG_T                               " T:"
#define MSG_B                               " B:"
#define MSG_AT                              " @"
#define MSG_BAT                             " B@:"
#define MSG_CAT                             " C@:"
#define MSG_W                               " W:"
#define MSG_PID_AUTOTUNE_FINISHED           MSG_PID_AUTOTUNE " finished! Put the last Kp, Ki and Kd constants from below into Configuration!"
#define MSG_PID_DEBUG                       " PID_DEBUG "
#define MSG_PID_DEBUG_INPUT                 ": Input "
#define MSG_PID_DEBUG_OUTPUT                " Output "
#define MSG_PID_DEBUG_PTERM                 " pTerm "
#define MSG_PID_DEBUG_ITERM                 " iTerm "
#define MSG_PID_DEBUG_DTERM                 " dTerm "
#define MSG_INVALID_EXTRUDER_NUM            " - Invalid extruder number !"

#define MSG_STOPPED_HEATER                  ", heater stopped! Heater_ID: "
#define MSG_HEATER_BED                      "Bed"
#define MSG_HEATER_CHAMBER                  "Chamber"
#define MSG_HEATER_COOLER                   "Cooler"
#define MSG_REDUNDANCY                      "Heater switched off. Temperature difference between temp sensors is too high !"
#define MSG_T_HEATING_FAILED                "Heating failed"
#define MSG_T_THERMAL_RUNAWAY               "Thermal Runaway"
#define MSG_T_MAXTEMP                       "MAXTEMP triggered"
#define MSG_T_MINTEMP                       "MINTEMP triggered"

// other
#define MSG_BED_LEVELING_X                  " X:"
#define MSG_BED_LEVELING_Y                  " Y:"
#define MSG_BED_LEVELING_Z                  "Z-probe:"

// Pins
#define MSG_CHANGE_PIN                      "For change pin please write in EEPROM and reset the printer."

// Never translate these strings
#define MSG_X "X"
#define MSG_Y "Y"
#define MSG_Z "Z"
#define MSG_E "E"
#define MSG_H1 "1"
#define MSG_H2 "2"
#define MSG_H3 "3"
#define MSG_H4 "4"
#define MSG_N1 " 1"
#define MSG_N2 " 2"
#define MSG_N3 " 3"
#define MSG_N4 " 4"
#define MSG_N5 " 5"
#define MSG_N6 " 6"
#define MSG_E1 " E1"
#define MSG_E2 " E2"
#define MSG_E3 " E3"
#define MSG_E4 " E4"
#define MSG_E5 " E5"
#define MSG_E6 " E6"
#define MSG_MOVE_E1 "1"
#define MSG_MOVE_E2 "2"
#define MSG_MOVE_E3 "3"
#define MSG_MOVE_E4 "4"
#define MSG_MOVE_E5 "5"
#define MSG_MOVE_E6 "6"
#define MSG_DIAM_E1 " 1"
#define MSG_DIAM_E2 " 2"
#define MSG_DIAM_E3 " 3"
#define MSG_DIAM_E4 " 4"
#define MSG_DIAM_E5 " 5"
#define MSG_DIAM_E6 " 6"

#define LANGUAGE_INCL(M)        STRINGIFY(language_##M.h)
#define INCLUDE_BY_LANGUAGE(M)  LANGUAGE_INCL(M)

#include INCLUDE_BY_LANGUAGE(LCD_LANGUAGE)

#if DISABLED(DISPLAY_CHARSET_ISO10646_1) \
 && DISABLED(DISPLAY_CHARSET_ISO10646_5) \
 && DISABLED(DISPLAY_CHARSET_ISO10646_KANA) \
 && DISABLED(DISPLAY_CHARSET_ISO10646_GREEK) \
 && DISABLED(DISPLAY_CHARSET_ISO10646_CN) \
 && DISABLED(DISPLAY_CHARSET_ISO10646_TR) \
 && DISABLED(DISPLAY_CHARSET_ISO10646_PL) \
 && DISABLED(DISPLAY_CHARSET_ISO10646_CZ) \
 && DISABLED(DISPLAY_CHARSET_ISO10646_SK)
  #define DISPLAY_CHARSET_ISO10646_1 // use the better font on full graphic displays.
#endif

#include "language_en.h"
