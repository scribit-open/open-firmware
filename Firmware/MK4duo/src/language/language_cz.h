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
 * Czech
 * UTF-8 for Graphical Display
 *
 * LCD Menu Messages
 *
 * Translated by Petr Zahradnik, Computer Laboratory
 * Blog and video blog Zahradnik se bavi
 * http://www.zahradniksebavi.cz
 *
 */

#define DISPLAY_CHARSET_ISO10646_CZ
#define CHARSIZE 2

#define WELCOME_MSG                         MACHINE_NAME _UxGT(" pripraven.")
#define MSG_BACK                            _UxGT("Zpet")
#define MSG_SD_INSERTED                     _UxGT("Karta vlo�ena")
#define MSG_SD_REMOVED                      _UxGT("Karta vyjmuta")
#define MSG_LCD_ENDSTOPS                    _UxGT("Endstopy") // max 8 znaku
#define MSG_LCD_SOFT_ENDSTOPS               _UxGT("Soft Endstopy")
#define MSG_MAIN                            _UxGT("Hlavn� nab�dka")
#define MSG_AUTOSTART                       _UxGT("Autostart")
#define MSG_DISABLE_STEPPERS                _UxGT("Uvolnit motory")
#define MSG_DEBUG_MENU                      _UxGT("Nab�dka laden�")
#define MSG_PROGRESS_BAR_TEST               _UxGT("Test uk. prubehu")
#define MSG_AUTO_HOME                       _UxGT("Domovsk� pozice")
#define MSG_AUTO_HOME_X                     _UxGT("Domu osa X")
#define MSG_AUTO_HOME_Y                     _UxGT("Domu osa Y")
#define MSG_AUTO_HOME_Z                     _UxGT("Domu osa Z")
#define MSG_TMC_Z_CALIBRATION               _UxGT("Kalibrovat Z")
#define MSG_LEVEL_BED_HOMING                _UxGT("Meren� podlo�ky")
#define MSG_LEVEL_BED_WAITING               _UxGT("Kliknut�m spustte")
#define MSG_LEVEL_BED_NEXT_POINT            _UxGT("Dal�� bod")
#define MSG_LEVEL_BED_DONE                  _UxGT("Meren� hotovo!")
#define MSG_Z_FADE_HEIGHT                   _UxGT("V��ka srovn�v�n�")
#define MSG_SET_HOME_OFFSETS                _UxGT("Nastavit ofsety")
#define MSG_HOME_OFFSETS_APPLIED            _UxGT("Ofsety nastaveny")
#define MSG_SET_ORIGIN                      _UxGT("Nastavit poc�tek")
#define MSG_PREHEAT_1                       _UxGT("Zahr�t " PREHEAT_1_LABEL)
#define MSG_PREHEAT_1_N                     MSG_PREHEAT_1 _UxGT(" ")
#define MSG_PREHEAT_1_ALL                   MSG_PREHEAT_1 _UxGT(" v�e")
#define MSG_PREHEAT_1_END                   MSG_PREHEAT_1 _UxGT(" hotend")
#define MSG_PREHEAT_1_BEDONLY               MSG_PREHEAT_1 _UxGT(" podlo�")
#define MSG_PREHEAT_1_SETTINGS              MSG_PREHEAT_1 _UxGT(" nast")
#define MSG_PREHEAT_2                       _UxGT("Zahr�t " PREHEAT_2_LABEL)
#define MSG_PREHEAT_2_N                     MSG_PREHEAT_2 _UxGT(" ")
#define MSG_PREHEAT_2_ALL                   MSG_PREHEAT_2 _UxGT(" v�e")
#define MSG_PREHEAT_2_END                   MSG_PREHEAT_2 _UxGT(" hotend")
#define MSG_PREHEAT_2_BEDONLY               MSG_PREHEAT_2 _UxGT(" podlo�")
#define MSG_PREHEAT_2_SETTINGS              MSG_PREHEAT_2 _UxGT(" nast")
#define MSG_COOLDOWN                        _UxGT("Zchladit")
#define MSG_SWITCH_PS_ON                    _UxGT("Zapnout nap�jen�")
#define MSG_SWITCH_PS_OFF                   _UxGT("Vypnout nap�jen�")
#define MSG_EXTRUDE                         _UxGT("Vytlacit (extr.)")
#define MSG_RETRACT                         _UxGT("Zatlacit (retr.)")
#define MSG_MOVE_AXIS                       _UxGT("Posunout osy")
#define MSG_BED_LEVELING                    _UxGT("Vyrovnat podlo�ku")
#define MSG_LEVEL_BED                       _UxGT("Vyrovnat podlo�ku")
#define MSG_LEVEL_CORNERS                   _UxGT("Vyrovnat rohy")
#define MSG_NEXT_CORNER                     _UxGT("Dal�� roh")
#define MSG_EDITING_STOPPED                 _UxGT("Konec �prav s�te")

#define MSG_UBL_DOING_G29                   _UxGT("Prov�d�m G29")
#define MSG_UBL_UNHOMED                     _UxGT("Prejedte domu")
#define MSG_UBL_TOOLS                       _UxGT("UBL n�stroje")
#define MSG_UBL_LEVEL_BED                   _UxGT("Unified Bed Leveling")
#define MSG_UBL_MANUAL_MESH                 _UxGT("Manu�ln� s�t bodu")
#define MSG_UBL_BC_INSERT                   _UxGT("Vlo�te kartu, zmerte")
#define MSG_UBL_BC_INSERT2                  _UxGT("Zmerte")
#define MSG_UBL_BC_REMOVE                   _UxGT("Odstrante a zmerte")
#define MSG_UBL_MOVING_TO_NEXT              _UxGT("Presun na dal��")
#define MSG_UBL_ACTIVATE_MESH               _UxGT("Aktivovat UBL")
#define MSG_UBL_DEACTIVATE_MESH             _UxGT("Deaktivovat UBL")
#define MSG_UBL_SET_TEMP_BED                _UxGT("Teplota podlo�ky")
#define MSG_UBL_BED_TEMP_CUSTOM             MSG_UBL_SET_TEMP_BED
#define MSG_UBL_SET_TEMP_HOTEND             _UxGT("Teplota hotendu")
#define MSG_UBL_HOTEND_TEMP_CUSTOM          MSG_UBL_SET_TEMP_HOTEND
#define MSG_UBL_MESH_EDIT                   _UxGT("�prava s�te bodu")
#define MSG_UBL_EDIT_CUSTOM_MESH            _UxGT("Upravit vlastn� s�t")
#define MSG_UBL_FINE_TUNE_MESH              _UxGT("Doladit s�t bodu")
#define MSG_UBL_DONE_EDITING_MESH           _UxGT("Konec �prav s�te")
#define MSG_UBL_BUILD_CUSTOM_MESH           _UxGT("Vlastn� s�t")
#define MSG_UBL_BUILD_MESH_MENU             _UxGT("Vytvorit s�t")
#define MSG_UBL_BUILD_MESH_M1               _UxGT("S�t bodu " PREHEAT_1_LABEL)
#define MSG_UBL_BUILD_MESH_M2               _UxGT("S�t bodu " PREHEAT_2_LABEL)
#define MSG_UBL_BUILD_COLD_MESH             _UxGT("Studen� s�t bodu")
#define MSG_UBL_MESH_HEIGHT_ADJUST          _UxGT("Upravit v��ku s�te")
#define MSG_UBL_MESH_HEIGHT_AMOUNT          _UxGT("V��ka")
#define MSG_UBL_VALIDATE_MESH_MENU          _UxGT("Zkontrolovat s�t")
#define MSG_UBL_VALIDATE_MESH_M1            _UxGT("Kontrola s�te " PREHEAT_1_LABEL)
#define MSG_UBL_VALIDATE_MESH_M2            _UxGT("Kontrola s�te " PREHEAT_2_LABEL)
#define MSG_UBL_VALIDATE_CUSTOM_MESH        _UxGT("Kontrola vlast. s�te")
#define MSG_UBL_CONTINUE_MESH               _UxGT("Pokracovat v s�ti")
#define MSG_UBL_MESH_LEVELING               _UxGT("S�tov� rovn�n�")
#define MSG_UBL_3POINT_MESH_LEVELING        _UxGT("3-bodove rovn�n�")
#define MSG_UBL_GRID_MESH_LEVELING          _UxGT("Mrizkove rovn�n�")
#define MSG_UBL_MESH_LEVEL                  _UxGT("Srovnat podlo�ku")
#define MSG_UBL_SIDE_POINTS                 _UxGT("Postrann� body")
#define MSG_UBL_MAP_TYPE                    _UxGT("Typ s�te bodu")
#define MSG_UBL_OUTPUT_MAP                  _UxGT("Exportovat s�t")
#define MSG_UBL_OUTPUT_MAP_HOST             _UxGT("Exportovat do PC")
#define MSG_UBL_OUTPUT_MAP_CSV              _UxGT("Exportovat do CSV")
#define MSG_UBL_OUTPUT_MAP_BACKUP           _UxGT("Z�loha do PC")
#define MSG_UBL_INFO_UBL                    _UxGT("Info o UBL do PC")
#define MSG_EDIT_MESH                       _UxGT("Upravit s�t bodu")
#define MSG_UBL_FILLIN_AMOUNT               _UxGT("Hustota mr�ky")
#define MSG_UBL_MANUAL_FILLIN               _UxGT("Rucn� hustota")
#define MSG_UBL_SMART_FILLIN                _UxGT("Chytr� hustota")
#define MSG_UBL_FILLIN_MESH                 _UxGT("Zaplnit mr�ku")
#define MSG_UBL_INVALIDATE_ALL              _UxGT("Zru�it v�echno")
#define MSG_UBL_INVALIDATE_CLOSEST          _UxGT("Zru�it posledn�")
#define MSG_UBL_FINE_TUNE_ALL               _UxGT("Upravit v�echny")
#define MSG_UBL_FINE_TUNE_CLOSEST           _UxGT("Upravit posledn�")
#define MSG_UBL_STORAGE_MESH_MENU           _UxGT("Ulo�i�te s�t�")
#define MSG_UBL_STORAGE_SLOT                _UxGT("Pametov� slot")
#define MSG_UBL_LOAD_MESH                   _UxGT("Nac�st s�t bodu")
#define MSG_UBL_SAVE_MESH                   _UxGT("Ulo�it s�t bodu")
#define MSG_MESH_LOADED                     _UxGT("S�t %i nactena")
#define MSG_MESH_SAVED                      _UxGT("S�t %i ulo�ena")
#define MSG_NO_STORAGE                      _UxGT("Nedostatek m�sta")
#define MSG_UBL_SAVE_ERROR                  _UxGT("Err: Ulo�it UBL")
#define MSG_UBL_RESTORE_ERROR               _UxGT("Err: Obnovit UBL")
#define MSG_UBL_Z_OFFSET_STOPPED            _UxGT("Konec Z-Offsetu")
#define MSG_UBL_STEP_BY_STEP_MENU           _UxGT("UBL Postupne")

#define MSG_LED_CONTROL                     _UxGT("LED Nastaven�")
#define MSG_LEDS                            _UxGT("Svetla")
#define MSG_LED_PRESETS                     _UxGT("Svetla Predvolby")
#define MSG_SET_LEDS_RED                    _UxGT("Cerven�")
#define MSG_SET_LEDS_ORANGE                 _UxGT("Oran�ov�")
#define MSG_SET_LEDS_YELLOW                 _UxGT("�lut�")
#define MSG_SET_LEDS_GREEN                  _UxGT("Zelen�")
#define MSG_SET_LEDS_BLUE                   _UxGT("Modr�")
#define MSG_SET_LEDS_INDIGO                 _UxGT("Indigo")
#define MSG_SET_LEDS_VIOLET                 _UxGT("Fialov�")
#define MSG_SET_LEDS_WHITE                  _UxGT("B�l�")
#define MSG_SET_LEDS_DEFAULT                _UxGT("V�choz�")
#define MSG_CUSTOM_LEDS                     _UxGT("Vlastn� svetla")
#define MSG_INTENSITY_R                     _UxGT("Cerven� intenzita")
#define MSG_INTENSITY_G                     _UxGT("Zelen� intezita")
#define MSG_INTENSITY_B                     _UxGT("Modr� intenzita")
#define MSG_INTENSITY_W                     _UxGT("B�l� intenzita")
#define MSG_LED_BRIGHTNESS                  _UxGT("Jas")
#define MSG_USER_MENU                       _UxGT("Vlastn� pr�kazy")

#define MSG_MOVING                          _UxGT("Posouvani...")
#define MSG_FREE_XY                         _UxGT("Uvolnit XY")
#define MSG_MOVE_X                          _UxGT("Posunout X")
#define MSG_MOVE_Y                          _UxGT("Posunout Y")
#define MSG_MOVE_Z                          _UxGT("Posunout Z")
#define MSG_MOVE_E                          _UxGT("Extrud�r")
#define MSG_MOVE_01MM                       _UxGT("Posunout o 0,1mm")
#define MSG_MOVE_1MM                        _UxGT("Posunout o 1mm")
#define MSG_MOVE_10MM                       _UxGT("Posunout o 10mm")
#define MSG_SPEED                           _UxGT("Rychlost")
#define MSG_BED_Z                           _UxGT("V��ka podl.")
#define MSG_NOZZLE                          _UxGT("Tryska")
#define MSG_BED                             _UxGT("Podlo�ka")
#define MSG_FAN_SPEED                       _UxGT("Rychlost vent.")
#define MSG_EXTRA_FAN_SPEED                 _UxGT("Rychlost ex. vent.")
#define MSG_FLOW                            _UxGT("Prutok")
#define MSG_CONTROL                         _UxGT("Ovl�dan�")
#define MSG_MIN                             _UxGT(" ") LCD_STR_THERMOMETER _UxGT(" Min")
#define MSG_MAX                             _UxGT(" ") LCD_STR_THERMOMETER _UxGT(" Max")
#define MSG_FACTOR                          _UxGT(" ") LCD_STR_THERMOMETER _UxGT(" Fakt")
#define MSG_AUTOTEMP                        _UxGT("Autoteplota")
#define MSG_ON                              _UxGT("Zap")
#define MSG_OFF                             _UxGT("Vyp")
#define MSG_PID_P                           _UxGT("PID-P")
#define MSG_PID_I                           _UxGT("PID-I")
#define MSG_PID_D                           _UxGT("PID-D")
#define MSG_PID_C                           _UxGT("PID-C")
#define MSG_SELECT                          _UxGT("Vybrat")
#define MSG_ACC                             _UxGT("Zrychl")
#define MSG_JERK                            _UxGT("Jerk")
#if IS_KINEMATIC
  #define MSG_VA_JERK                       _UxGT("Va-jerk")
  #define MSG_VB_JERK                       _UxGT("Vb-jerk")
  #define MSG_VC_JERK                       _UxGT("Vc-jerk")
#else
  #define MSG_VA_JERK                       _UxGT("Vx-jerk")
  #define MSG_VB_JERK                       _UxGT("Vy-jerk")
  #define MSG_VC_JERK                       _UxGT("Vz-jerk")
#endif
#define MSG_VE_JERK                         _UxGT("Ve-jerk")
#define MSG_VELOCITY                        _UxGT("Rychlost")
#define MSG_VMAX                            _UxGT("Vmax ")
#define MSG_VMIN                            _UxGT("Vmin")
#define MSG_VTRAV_MIN                       _UxGT("VTrav min")
#define MSG_ACCELERATION                    _UxGT("Akcelerace")
#define MSG_AMAX                            _UxGT("Amax ")
#define MSG_A_RETRACT                       _UxGT("A-retrakt")
#define MSG_A_TRAVEL                        _UxGT("A-prejezd")
#define MSG_STEPS_PER_MM                    _UxGT("Kroku/mm")
#if IS_KINEMATIC
  #define MSG_ASTEPS                        _UxGT("Akroku/mm")
  #define MSG_BSTEPS                        _UxGT("Bkroku/mm")
  #define MSG_CSTEPS                        _UxGT("Ckroku/mm")
#else
  #define MSG_ASTEPS                        _UxGT("Xkroku/mm")
  #define MSG_BSTEPS                        _UxGT("Ykroku/mm")
  #define MSG_CSTEPS                        _UxGT("Zkroku/mm")
#endif
#define MSG_ESTEPS                          _UxGT("Ekroku/mm")
#define MSG_E1STEPS                         _UxGT("E1kroku/mm")
#define MSG_E2STEPS                         _UxGT("E2kroku/mm")
#define MSG_E3STEPS                         _UxGT("E3kroku/mm")
#define MSG_E4STEPS                         _UxGT("E4kroku/mm")
#define MSG_E5STEPS                         _UxGT("E5kroku/mm")
#define MSG_E6STEPS                         _UxGT("E6kroku/mm")
#define MSG_TEMPERATURE                     _UxGT("Teplota")
#define MSG_MOTION                          _UxGT("Pohyb")
#define MSG_FILAMENT                        _UxGT("Filament")
#define MSG_VOLUMETRIC_ENABLED              _UxGT("E na mm3")
#define MSG_FILAMENT_DIAM                   _UxGT("Fil. Prum.")
#define MSG_FILAMENT_UNLOAD                 _UxGT("Vysunout mm")
#define MSG_FILAMENT_LOAD                   _UxGT("Zav�st mm")
#define MSG_ADVANCE_K                       _UxGT("K pro posun")
#define MSG_CONTRAST                        _UxGT("Kontrast LCD")
#define MSG_STORE_EEPROM                    _UxGT("Ulo�it nastaven�")
#define MSG_LOAD_EEPROM                     _UxGT("Nac�st nastaven�")
#define MSG_RESTORE_FAILSAFE                _UxGT("Obnovit v�choz�")
#define MSG_INIT_EEPROM                     _UxGT("Inic. EEPROM")
#define MSG_REFRESH                         _UxGT("Obnovit")
#define MSG_WATCH                           _UxGT("Info obrazovka")
#define MSG_PREPARE                         _UxGT("Priprava tisku")
#define MSG_TUNE                            _UxGT("Doladen� tisku")
#define MSG_PAUSE_PRINT                     _UxGT("Pozastavit tisk")
#define MSG_RESUME_PRINT                    _UxGT("Obnovit tisk")
#define MSG_STOP_PRINT                      _UxGT("Zastavit tisk")
#define MSG_POWER_LOSS_RECOVERY             _UxGT("Obnova vypadku")
#define MSG_CARD_MENU                       _UxGT("Tisknout z SD")
#define MSG_NO_CARD                         _UxGT("��dn� SD karta")
#define MSG_DWELL                           _UxGT("Usp�no...")
#define MSG_USERWAIT                        _UxGT("Cek�n� na u�iv...")
#define MSG_PRINT_PAUSED                    _UxGT("Tisk pozastaven")
#define MSG_PRINTING                        _UxGT("Tisknu...")
#define MSG_PRINT_ABORTED                   _UxGT("Tisk zru�en")
#define MSG_NO_MOVE                         _UxGT("��dn� pohyb.")
#define MSG_KILLED                          _UxGT("PRERUSENO. ")
#define MSG_STOPPED                         _UxGT("ZASTAVENO. ")
#define MSG_CONTROL_RETRACT                 _UxGT("Retrakt mm")
#define MSG_CONTROL_RETRACT_SWAP            _UxGT("V�mena Re.mm")
#define MSG_CONTROL_RETRACTF                _UxGT("Retraktovat  V")
#define MSG_CONTROL_RETRACT_ZHOP            _UxGT("Zvednuti Z mm")
#define MSG_CONTROL_RETRACT_RECOVER         _UxGT("UnRet mm")
#define MSG_CONTROL_RETRACT_RECOVER_SWAP    _UxGT("S UnRet mm")
#define MSG_CONTROL_RETRACT_RECOVERF        _UxGT("UnRet  V")
#define MSG_CONTROL_RETRACT_RECOVER_SWAPF   _UxGT("S UnRet V")
#define MSG_AUTORETRACT                     _UxGT("AutoRetr.")
#define MSG_FILAMENTCHANGE                  _UxGT("Vymenit filament")
#define MSG_FILAMENTLOAD                    _UxGT("Zav�st filament")
#define MSG_FILAMENTUNLOAD                  _UxGT("Vysunout filament")
#define MSG_FILAMENTUNLOAD_ALL              _UxGT("Vysunout v�e")

#define MSG_INIT_SDCARD                     _UxGT("Nac�st SD kartu")
#define MSG_CHANGE_SDCARD                   _UxGT("Vymenit SD kartu")
#define MSG_ZPROBE_OUT                      _UxGT("Sonda Z mimo podl")
#define MSG_SKEW_FACTOR                     _UxGT("Faktor zkosen�")
#define MSG_BLTOUCH                         _UxGT("BLTouch")
#define MSG_BLTOUCH_SELFTEST                _UxGT("BLTouch Self-Test")
#define MSG_BLTOUCH_RESET                   _UxGT("BLTouch Reset")
#define MSG_BLTOUCH_DEPLOY                  _UxGT("BLTouch Vysunout")
#define MSG_BLTOUCH_STOW                    _UxGT("BLTouch Zasunout")
#define MSG_HOME                            _UxGT("Domu")  // Used as MSG_HOME " " MSG_X MSG_Y MSG_Z " " MSG_FIRST
#define MSG_FIRST                           _UxGT("prvn�")
#define MSG_ZPROBE_ZOFFSET                  _UxGT("Z ofset")
#define MSG_BABYSTEP_X                      _UxGT("Babystep X")
#define MSG_BABYSTEP_Y                      _UxGT("Babystep Y")
#define MSG_BABYSTEP_Z                      _UxGT("Babystep Z")
#define MSG_ENDSTOP_ABORT                   _UxGT("Endstop abort")
#define MSG_HEATING_FAILED_LCD              _UxGT("Chyba zahr�v�n�")
#define MSG_HEATING_FAILED_LCD_BED          _UxGT("Chyba zahr. podl.")
#define MSG_ERR_REDUNDANT_TEMP              _UxGT("REDUND. TEPLOTA")
#define MSG_THERMAL_RUNAWAY                 _UxGT("TEPLOTN� SKOK")
#define MSG_THERMAL_RUNAWAY_BED             _UxGT("PODL. TEPL. SKOK")
#define MSG_ERR_MAXTEMP                     _UxGT("VYSOK� TEPLOTA")
#define MSG_ERR_MINTEMP                     _UxGT("N�ZKA TEPLOTA")
#define MSG_ERR_MAXTEMP_BED                 _UxGT("VYS. TEPL. PODL.")
#define MSG_ERR_MINTEMP_BED                 _UxGT("N�Z. TEPL. PODL.")
#define MSG_ERR_Z_HOMING                    MSG_HOME _UxGT(" ") MSG_X MSG_Y _UxGT(" ") MSG_FIRST
#define MSG_HALTED                          _UxGT("TISK. ZASTAVENA")
#define MSG_PLEASE_RESET                    _UxGT("Provedte reset")
#define MSG_SHORT_DAY                       _UxGT("d")
#define MSG_SHORT_HOUR                      _UxGT("h")
#define MSG_SHORT_MINUTE                    _UxGT("m")
#define MSG_HEATING                         _UxGT("Zahr�v�n�...")
#define MSG_COOLING                         _UxGT("Chlazen�")
#define MSG_BED_HEATING                     _UxGT("Zahr�v�n� podl...")
#define MSG_BED_COOLING                     _UxGT("Chlazen� podl...")
#define MSG_DELTA_CALIBRATE                 _UxGT("Delta Kalibrace")
#define MSG_DELTA_CALIBRATE_X               _UxGT("Kalibrovat X")
#define MSG_DELTA_CALIBRATE_Y               _UxGT("Kalibrovat Y")
#define MSG_DELTA_CALIBRATE_Z               _UxGT("Kalibrovat Z")
#define MSG_DELTA_CALIBRATE_CENTER          _UxGT("Kalibrovat Stred")
#define MSG_DELTA_SETTINGS                  _UxGT("Delta nastaven�")
#define MSG_DELTA_AUTO_CALIBRATE            _UxGT("Autokalibrace")
#define MSG_DELTA_HEIGHT_CALIBRATE          _UxGT("Nast.v��ku delty")
#define MSG_DELTA_Z_OFFSET_CALIBRATE        _UxGT("Nast. Z-ofset")
#define MSG_DELTA_DIAG_ROD                  _UxGT("Diag rameno")
#define MSG_DELTA_HEIGHT                    _UxGT("V��ka")
#define MSG_DELTA_RADIUS                    _UxGT("Polomer")
#define MSG_INFO_MENU                       _UxGT("O tisk�rne")
#define MSG_INFO_PRINTER_MENU               _UxGT("Info o tisk�rne")
#define MSG_3POINT_LEVELING                 _UxGT("3-bodov� rovn�n�")
#define MSG_LINEAR_LEVELING                 _UxGT("Line�rni rovn�n�")
#define MSG_BILINEAR_LEVELING               _UxGT("Biline�rn� rovn�n�")
#define MSG_UBL_LEVELING                    _UxGT("Unified Bed Leveling")
#define MSG_MESH_LEVELING                   _UxGT("Mr�kov� rovn�n�")
#define MSG_INFO_STATS_MENU                 _UxGT("Statistika")
#define MSG_INFO_BOARD_MENU                 _UxGT("Info o desce")
#define MSG_INFO_THERMISTOR_MENU            _UxGT("Termistory")
#define MSG_INFO_EXTRUDERS                  _UxGT("Extrud�ry")
#define MSG_INFO_BAUDRATE                   _UxGT("Rychlost")
#define MSG_INFO_PROTOCOL                   _UxGT("Protokol")
#define MSG_CASE_LIGHT                      _UxGT("Osvetlen�")
#define MSG_CASE_LIGHT_BRIGHTNESS           _UxGT("Jas svetla")

#if LCD_WIDTH >= 20
  #define MSG_INFO_PRINT_COUNT              _UxGT("Pocet tisku")
  #define MSG_INFO_COMPLETED_PRINTS         _UxGT("Dokonceno")
  #define MSG_INFO_PRINT_TIME               _UxGT("Celkov� cas")
  #define MSG_INFO_PRINT_LONGEST            _UxGT("Nejdel�� tisk")
  #define MSG_INFO_PRINT_FILAMENT           _UxGT("Celkem vytlaceno")
#else
  #define MSG_INFO_PRINT_COUNT              _UxGT("Tisky")
  #define MSG_INFO_COMPLETED_PRINTS         _UxGT("Hotovo")
  #define MSG_INFO_PRINT_TIME               _UxGT("Cas")
  #define MSG_INFO_PRINT_LONGEST            _UxGT("Nejdel��")
  #define MSG_INFO_PRINT_FILAMENT           _UxGT("Vytlaceno")
#endif

#define MSG_INFO_MIN_TEMP                   _UxGT("Teplota min")
#define MSG_INFO_MAX_TEMP                   _UxGT("Teplota max")
#define MSG_INFO_PSU                        _UxGT("Nap. zdroj")
#define MSG_DRIVE_STRENGTH                  _UxGT("Buzen� motoru")
#define MSG_DAC_PERCENT                     _UxGT("Motor %")
#define MSG_DAC_EEPROM_WRITE                _UxGT("Ulo�it do EEPROM")
#define MSG_FILAMENT_CHANGE_HEADER_PAUSE    _UxGT("TISK POZASTAVEN")
#define MSG_FILAMENT_CHANGE_HEADER_LOAD     _UxGT("ZAVEDEN� FILAMENTU")
#define MSG_FILAMENT_CHANGE_HEADER_UNLOAD   _UxGT("VYSUNUT� FILAMENTU")
#define MSG_FILAMENT_CHANGE_OPTION_HEADER   _UxGT("MO�NOSTI OBNOVEN�:")
#define MSG_FILAMENT_CHANGE_OPTION_PURGE    _UxGT("Vytlacit v�c")
#define MSG_FILAMENT_CHANGE_OPTION_RESUME   _UxGT("Obnovit tisk")
#define MSG_FILAMENT_CHANGE_NOZZLE          _UxGT("  Tryska: ")
#define MSG_ERR_HOMING_FAILED               _UxGT("Parkov�n� selhalo")
#define MSG_ERR_PROBING_FAILED              _UxGT("Kalibrace selhala")
#define MSG_M600_TOO_COLD                   _UxGT("M600: Moc studen�")

#if LCD_HEIGHT >= 4
  // Up to 3 lines allowed
  #define MSG_FILAMENT_CHANGE_INIT_1          _UxGT("Cekejte pros�m")
  #define MSG_FILAMENT_CHANGE_INIT_2          _UxGT("na zah�jen�")
  #define MSG_FILAMENT_CHANGE_INIT_3          _UxGT("v�meny filamentu")
  #define MSG_FILAMENT_CHANGE_UNLOAD_1        _UxGT("Cekejte pros�m")
  #define MSG_FILAMENT_CHANGE_UNLOAD_2        _UxGT("na vysunuti")
  #define MSG_FILAMENT_CHANGE_UNLOAD_3        _UxGT("filamentu")
  #define MSG_FILAMENT_CHANGE_INSERT_1        _UxGT("Vlo�te filament")
  #define MSG_FILAMENT_CHANGE_INSERT_2        _UxGT("a stisknete")
  #define MSG_FILAMENT_CHANGE_INSERT_3        _UxGT("tlac�tko...")
  #define MSG_FILAMENT_CHANGE_HEAT_1          _UxGT("Kliknete pro")
  #define MSG_FILAMENT_CHANGE_HEAT_2          _UxGT("nahr�t� trysky")
  #define MSG_FILAMENT_CHANGE_HEATING_1       _UxGT("Cekejte pros�m")
  #define MSG_FILAMENT_CHANGE_HEATING_2       _UxGT("na nahr�t� tr.")
  #define MSG_FILAMENT_CHANGE_LOAD_1          _UxGT("Cekejte pros�m")
  #define MSG_FILAMENT_CHANGE_LOAD_2          _UxGT("na zaveden�")
  #define MSG_FILAMENT_CHANGE_LOAD_3          _UxGT("filamentu")
  #define MSG_FILAMENT_CHANGE_PURGE_1         _UxGT("Vyckejte na")
  #define MSG_FILAMENT_CHANGE_PURGE_2         _UxGT("vytlacen�")
  #define MSG_FILAMENT_CHANGE_RESUME_1        _UxGT("Cekejte pros�m")
  #define MSG_FILAMENT_CHANGE_RESUME_2        _UxGT("na pokracov�n�")
  #define MSG_FILAMENT_CHANGE_RESUME_3        _UxGT("tisku")
#else // LCD_HEIGHT < 4
  // Up to 2 lines allowed
  #define MSG_FILAMENT_CHANGE_INIT_1          _UxGT("Cekejte...")
  #define MSG_FILAMENT_CHANGE_UNLOAD_1        _UxGT("Vysouv�n�...")
  #define MSG_FILAMENT_CHANGE_INSERT_1        _UxGT("Vlo�te, kliknete")
  #define MSG_FILAMENT_CHANGE_HEATING_1       _UxGT("Nahr�v�n�...")
  #define MSG_FILAMENT_CHANGE_LOAD_1          _UxGT("Zav�den�...")
  #define MSG_FILAMENT_CHANGE_PURGE_1         _UxGT("Vytlacov�n�...")
  #define MSG_FILAMENT_CHANGE_RESUME_1        _UxGT("Pokracov�n�...")
#endif // LCD_HEIGHT < 4
