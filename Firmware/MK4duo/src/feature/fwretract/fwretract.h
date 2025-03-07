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
 * fwretract.h - Define firmware-based retraction interface
 *
 * Copyright (C) 2017 Alberto Cotronei @MagoKimbra
 */

#pragma once

#if ENABLED(FWRETRACT)

  typedef struct {
    float retract_length,                     // M207 S - G10 Retract length
          retract_feedrate_mm_s,              // M207 F - G10 Retract feedrate
          retract_zlift,                      // M207 Z - G10 Retract hop size
          retract_recover_length,             // M208 S - G11 Recover length
          retract_recover_feedrate_mm_s,      // M208 F - G11 Recover feedrate
          swap_retract_length,                // M207 W - G10 Swap Retract length
          swap_retract_recover_length,        // M208 W - G11 Swap Recover length
          swap_retract_recover_feedrate_mm_s; // M208 R - G11 Swap Recover feedrate
  } fwretract_data_t;

  class FWRetract {

    public: /** Constructor */

      FWRetract() { reset(); }

    public: /** Public Parameters */

      static fwretract_data_t data;

      static bool   autoretract_enabled,                // M209 S - Autoretract switch
                    retracted[EXTRUDERS];               // Which extruders are currently retracted
      static float  current_retract[EXTRUDERS],         // Retract value used by planner
                    current_hop;                        // Hop value used by planner

    private: /** Private Parameters */

      #if EXTRUDERS > 1
        static bool retracted_swap[EXTRUDERS];          // Which extruders are swap-retracted
      #endif

    public: /** Public Function */

      static void reset();

      static void refresh_autoretract() {
        LOOP_EXTRUDER() retracted[e] = false;
      }

      static void enable_autoretract(const bool enable) {
        autoretract_enabled = enable;
        refresh_autoretract();
      }

      static void retract(const bool retracting
        #if EXTRUDERS > 1
          , bool swapping = false
        #endif
      );
  };

  extern FWRetract fwretract;

#endif // ENABLED(FWRETRACT)
