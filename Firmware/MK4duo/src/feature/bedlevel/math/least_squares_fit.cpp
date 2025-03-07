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
 * Least Squares Best Fit by Roxy and Ed Williams
 *
 * This algorithm is high speed and has a very small code footprint.
 * Its results are identical to both the Iterative Least-Squares published
 * earlier by Roxy and the QR_SOLVE solution. If used in place of QR_SOLVE
 * it saves roughly 10K of program memory. It also does not require all of
 * coordinates to be present during the calculations. Each point can be
 * probed and then discarded.
 *
 */

#include "../../../../MK4duo.h"

#if ABL_PLANAR || ENABLED(AUTO_BED_LEVELING_UBL)

  #include "least_squares_fit.h"

  int finish_incremental_LSF(struct linear_fit_data *lsf) {

    const float N = lsf->N;

    if (N == 0.0)
      return 1;

    lsf->xbar /= N;
    lsf->ybar /= N;
    lsf->zbar /= N;
    lsf->x2bar = lsf->x2bar / N - sq(lsf->xbar);
    lsf->y2bar = lsf->y2bar / N - sq(lsf->ybar);
    lsf->z2bar = lsf->z2bar / N - sq(lsf->zbar);
    lsf->xybar = lsf->xybar / N - lsf->xbar * lsf->ybar;
    lsf->yzbar = lsf->yzbar / N - lsf->ybar * lsf->zbar;
    lsf->xzbar = lsf->xzbar / N - lsf->xbar * lsf->zbar;
    const float DD = lsf->x2bar * lsf->y2bar - sq(lsf->xybar);

    if (ABS(DD) <= 1e-10 * (lsf->max_absx + lsf->max_absy))
      return 1;

    lsf->A = (lsf->yzbar * lsf->xybar - lsf->xzbar * lsf->y2bar) / DD;
    lsf->B = (lsf->xzbar * lsf->xybar - lsf->yzbar * lsf->x2bar) / DD;
    lsf->D = -(lsf->zbar + lsf->A * lsf->xbar + lsf->B * lsf->ybar);
    return 0;
  }

#endif // ENABLED(AUTO_BED_LEVELING_LINEAR)
