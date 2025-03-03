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
 * mcode
 *
 * Copyright (C) 2017 Alberto Cotronei @MagoKimbra
 */

#if HAS_SD_RESTART

  #define CODE_M800

  void menu_sdcard_restart();

  #if ENABLED(DEBUG_RESTART)

    inline void m800_error(PGM_P const prefix) {
      SERIAL_STR(ECHO);
      SERIAL_PS(prefix);
      SERIAL_EM(" Restart Job Data");
    }

  #endif

  /**
   * M800: Resume from Restart Job
   *   - With 'S' go to the Restart/Cancel menu
   *   - With no parameters run restart commands
   */
  inline void gcode_M800(void) {

    if (restart.valid()) {
      #if HAS_LCD_MENU
        if (parser.seen('S'))
          lcdui.goto_screen(menu_sdcard_restart);
        else
      #endif
        restart.resume_job();
    }
    else {
      #if ENABLED(DEBUG_RESTART)
        m800_error(restart.job_info.valid_head ? PSTR("No") : PSTR("Invalid"));
      #endif
    }

  }

#endif // HAS_SD_RESTART
