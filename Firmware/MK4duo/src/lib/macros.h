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

// NoPin
#define NoPin     -1

// Macros for CAT args
#define _CAT(a, ...) a ## __VA_ARGS__

// Macros to support option testing
#define ENABLED   defined
#define DISABLED !defined

// The axis order in all axis related arrays is X, Y, Z, E
#define NUM_AXIS  4
#define XYZE      4
#define ABCE      4
#define ABC       3
#define XYZ       3

#define _AXIS(A)  (A##_AXIS)

// Function macro
#define _FORCE_INLINE_  __attribute__((__always_inline__)) __inline__
#define  FORCE_INLINE   __attribute__((always_inline)) inline
#define _UNUSED         __attribute__((unused))
#define _O0             __attribute__((optimize("O0")))
#define _Os             __attribute__((optimize("Os")))
#define _O1             __attribute__((optimize("O1")))
#define _O2             __attribute__((optimize("O2")))
#define _O3             __attribute__((optimize("O3")))

// Clock speed factor
#define CYCLES_PER_US   ((F_CPU)/1000000UL)

// Nanoseconds per cycle
#define NS_PER_CYCLE    (1000000000.0/(F_CPU))

// Remove compiler warning on an unused variable
#define UNUSED(x)       ((void)(x))

/**
 * Macrof for Delay
 */
#define DELAY_NS(x) HAL::delayNanoseconds(x)
#define DELAY_US(x) HAL::delayMicroseconds(x)

/**
 * Macros for mechanics type
 */
#define MECH_UNKNOWN        -1
#define MECH_CARTESIAN       0
#define MECH_COREXY          1
#define MECH_COREYX          2
#define MECH_DELTA           3
#define MECH_MORGAN_SCARA    4
#define MECH_MAKERARM_SCARA  5
#define MECH_COREXZ          8
#define MECH_COREZX          9
#define MECH_COREYZ         10
#define MECH_COREZY         11
#define MECH_MUVE3D         21

#define MECH(mech)    (MECHANISM == MECH_##mech)
#define NOMECH(mech)  (MECHANISM != MECH_##mech)

#define IS_SCARA      (MECH(MORGAN_SCARA) || MECH(MAKERARM_SCARA))
#define IS_KINEMATIC  (MECH(DELTA)  || IS_SCARA)
#define CORE_IS_XY    (MECH(COREXY) || MECH(COREYX))
#define CORE_IS_XZ    (MECH(COREXZ) || MECH(COREZX))
#define CORE_IS_YZ    (MECH(COREYZ) || MECH(COREZY))
#define IS_CORE       (CORE_IS_XY || CORE_IS_XZ || CORE_IS_YZ)
#define IS_MUVE3D     (MECH(MUVE3D))

// Macros to inch mode support
#if ENABLED(INCH_MODE_SUPPORT)
  #define LINEAR_UNIT(N)      ((N) / parser.linear_unit_factor)
  #define VOLUMETRIC_UNIT(N)  ((N) / (printer.isVolumetric() ? parser.volumetric_unit_factor : parser.linear_unit_factor))
#else
  #define LINEAR_UNIT(N)      N
  #define VOLUMETRIC_UNIT(N)  N
#endif

// Macros to make a string from a macro
#define STRINGIFY_(M) #M
#define STRINGIFY(M)  STRINGIFY_(M)

#define A(CODE)       " " CODE "\n\t"
#define L(CODE)       CODE ":\n\t"

// Macros for communication
#define FSTRINGVALUE(var,value) const char var[] PROGMEM = value
#define FSTRINGVAR(var)         extern const char var[] PROGMEM

// Macros for bit masks
#undef _BV
#define _BV(b)            (1<<(b))
#define TEST(n,b)         !!((n)&_BV(b))
#define SBI(n,b)          (n |= _BV(b))
#define CBI(n,b)          (n &= ~_BV(b))
#define SET_BIT(N,B,TF)   do{ if (TF) SBI(N,B); else CBI(N,B); }while(0)

#define _BV32(b)          (1UL << (b))
#define TEST32(n,b)       !!((n)&_BV32(b))
#define SBI32(n,b)        (n |= _BV32(b))
#define CBI32(n,b)        (n &= ~_BV32(b))

// Macros to contrain values
#define WITHIN(V,L,H)     ((V) >= (L) && (V) <= (H))
#define NUMERIC(a)        WITHIN(a, '0', '9')
#define DECIMAL(a)        (NUMERIC(a) || a == '.')
#define NUMERIC_SIGNED(a) (NUMERIC(a) || (a) == '-' || (a) == '+')
#define DECIMAL_SIGNED(a) (DECIMAL(a) || (a) == '-' || (a) == '+')
#define COUNT(a)          (sizeof(a)/sizeof(*a))
#define ZERO(a)           memset(a,0,sizeof(a))
#define COPY_ARRAY(a,b)   memcpy(a,b,MIN(sizeof(a),sizeof(b)))

// Macros for initializing arrays
#define ARRAY_12(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, ...)  v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12
#define ARRAY_11(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, ...)       v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11
#define ARRAY_10(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, ...)            v1, v2, v3, v4, v5, v6, v7, v8, v9, v10
#define ARRAY_9(v1, v2, v3, v4, v5, v6, v7, v8, v9, ...)                  v1, v2, v3, v4, v5, v6, v7, v8, v9
#define ARRAY_8(v1, v2, v3, v4, v5, v6, v7, v8, ...)                      v1, v2, v3, v4, v5, v6, v7, v8
#define ARRAY_7(v1, v2, v3, v4, v5, v6, v7, ...)                          v1, v2, v3, v4, v5, v6, v7
#define ARRAY_6(v1, v2, v3, v4, v5, v6, ...)                              v1, v2, v3, v4, v5, v6
#define ARRAY_5(v1, v2, v3, v4, v5, ...)                                  v1, v2, v3, v4, v5
#define ARRAY_4(v1, v2, v3, v4, ...)                                      v1, v2, v3, v4
#define ARRAY_3(v1, v2, v3, ...)                                          v1, v2, v3
#define ARRAY_2(v1, v2, ...)                                              v1, v2
#define ARRAY_1(v1, ...)                                                  v1
#define ARRAY_0(...)

#define _ARRAY_N(N, ...)        ARRAY_ ##N(__VA_ARGS__)
#define ARRAY_N(N, ...)         { _ARRAY_N(N, __VA_ARGS__) }
#define LIST_N(N, ...)          _ARRAY_N(N, __VA_ARGS__)

// ARRAY_BY_N based
#define ARRAY_BY_N_N(N, ...)    ARRAY_N(N, __VA_ARGS__)
#define ARRAY_BY_N(N, v1)       ARRAY_BY_N_N(N, v1, v1, v1, v1, v1, v1, v1, v1, v1, v1, v1, v1)

// ARRAY_BY_EXTRUDERS based on EXTRUDERS
#define ARRAY_BY_EXTRUDERS_N(...) ARRAY_N(EXTRUDERS, __VA_ARGS__)
#define ARRAY_BY_EXTRUDERS(v1)  ARRAY_BY_EXTRUDERS_N(v1, v1, v1, v1, v1, v1, v1, v1, v1, v1, v1, v1)

// ARRAY_BY_HOTENDS based on HOTENDS
#define ARRAY_BY_HOTENDS_N(...) ARRAY_N(HOTENDS, __VA_ARGS__)
#define ARRAY_BY_HOTENDS(v1)    ARRAY_BY_HOTENDS_N(v1, v1, v1, v1, v1, v1)

// ARRAY_BY_FAN based on FAN_COUNT
#define ARRAY_BY_FANS_N(...)    ARRAY_N(FAN_COUNT, __VA_ARGS__)
#define ARRAY_BY_FANS(v1)       ARRAY_BY_FANS_N(v1, v1, v1, v1, v1, v1)

#define PIN_EXISTS(PN)          (defined(PN##_PIN) && PN##_PIN > NoPin)

#define PENDING(NOW,SOON)       ((int32_t)(NOW-(SOON))<0)
#define ELAPSED(NOW,SOON)       (!PENDING(NOW,SOON))

#define NOOP                    do{}while(0)

#define CEILING(x,y)            (((x) + (y) - 1) / (y))

#define UNEAR_ZERO(x)           ((x) < 0.000001f)
#define NEAR_ZERO(x)            WITHIN(x, -0.000001f, 0.000001f)
#define NEAR(x,y)               NEAR_ZERO((x)-(y))

#define RECIPROCAL(x)           (NEAR_ZERO(x) ? 0 : (1 / float(x)))
#define FIXFLOAT(f)             (f + (f < 0 ? -0.00005f : 0.00005f))

// LOOP MACROS
#define LOOP_S_LE_N(VAR, S, N)  for (uint8_t VAR=S; VAR<=N; VAR++)
#define LOOP_S_L_N(VAR, S, N)   for (uint8_t VAR=S; VAR<N; VAR++)
#define LOOP_LE_N(VAR, N)       LOOP_S_LE_N(VAR, 0, N)
#define LOOP_L_N(VAR, N)        LOOP_S_L_N(VAR, 0, N)

#define LOOP_NA(VAR)            LOOP_L_N(VAR, NUM_AXIS)
#define LOOP_XY(VAR)            LOOP_S_LE_N(VAR, X_AXIS, Y_AXIS)
#define LOOP_XYZ(VAR)           LOOP_S_LE_N(VAR, X_AXIS, Z_AXIS)
#define LOOP_XYZE(VAR)          LOOP_S_LE_N(VAR, X_AXIS, E_AXIS)
#define LOOP_XYZE_N(VAR)        LOOP_S_L_N(VAR, X_AXIS, XYZE_N)
#define LOOP_ABC(VAR)           LOOP_S_LE_N(VAR, A_AXIS, C_AXIS)
#define LOOP_ABCE(VAR)          LOOP_S_LE_N(VAR, A_AXIS, E_AXIS)
#define LOOP_ABCE_N(VAR)        LOOP_S_L_N(VAR, A_AXIS, XYZE_N)
#define LOOP_DRV_EXTRUDER()     LOOP_L_N(d, DRIVER_EXTRUDERS)
#define LOOP_EXTRUDER()         LOOP_L_N(e, EXTRUDERS)
#define LOOP_HOTEND()           LOOP_L_N(h, HOTENDS)
#define LOOP_HEATER()           LOOP_L_N(h, HEATER_COUNT)
#define LOOP_FAN()              LOOP_L_N(f, FAN_COUNT)
#define LOOP_SERVO()            LOOP_L_N(s, NUM_SERVOS)
#define LOOP_TMC()              LOOP_L_N(t, TMC_AXIS)

// Feedrate scaling and conversion
#define MMM_TO_MMS(MM_M)        ((MM_M)/60.0f)
#define MMS_TO_MMM(MM_S)        ((MM_S)*60.0f)
#define MMS_SCALED(MM_S)        ((MM_S)*mechanics.feedrate_percentage*0.01)

// Macros for maths shortcuts
#undef M_PI
#define M_PI              3.14159265358979323846f

#define RADIANS(d)        ((d)*float(M_PI)/180.0f)
#define DEGREES(r)        ((r)*180.0f/float(M_PI))
#define HYPOT2(x,y)       (sq(x)+sq(y))
#define HYPOT(x,y)        SQRT(HYPOT2(x,y))
#define SQUARE(x)         ((x)*(x))
#define SIN_60            0.8660254037844386f
#define COS_60            0.5f

#define CIRCLE_AREA(R)    (float(M_PI) * sq(float(R)))
#define CIRCLE_CIRC(R)    (2 * float(M_PI) * float(R))

#define SIGN(a)           ((a>0)-(a<0))
#define IS_POWER_OF_2(x)  ((x) && !((x) & ((x) - 1)))

#undef MIN
#undef MAX
#undef ABS
#undef NOMORE
#undef NOLESS
#undef LIMIT
#undef ATAN2
#undef POW
#undef SQRT
#undef CEIL
#undef FLOOR
#undef LROUND
#undef FMOD
#undef COS
#undef SIN
#define ATAN2(y,x)  atan2f(y, x)
#define POW(x, y)   powf(x, y)
#define SQRT(x)     sqrtf(x)
#define RSQRT(x)    (1 / sqrtf(x))
#define CEIL(x)     ceilf(x)
#define FLOOR(x)    floorf(x)
#define LROUND(x)   lroundf(x)
#define FMOD(x,y)   fmodf(x, y)
#define COS(x)      cosf(x)
#define SIN(x)      sinf(x)
#define LOG(x)      logf(x)

#ifdef __cplusplus

  extern "C++" {

    template <class A, class B> static inline constexpr auto MIN(const A a, const B b) -> decltype(a + b) {
      return a < b ? a : b;
    }
    template <class A, class B> static inline constexpr auto MAX(const A a, const B b) -> decltype(a + b) {
      return a > b ? a : b;
    }
    template<class T, class ... Ts> static inline constexpr const T MIN(T V, Ts... Vs) { return MIN(V, MIN(Vs...)); }
    template<class T, class ... Ts> static inline constexpr const T MAX(T V, Ts... Vs) { return MAX(V, MAX(Vs...)); }

    template <class A> static inline constexpr const A ABS(const A a) { return a >= 0 ? a : -a; }

    template <class A, class B> static inline constexpr void NOLESS(A& a, const B b) { if (a < b) a = b; }
    template <class A, class B> static inline constexpr void NOMORE(A& a, const B b) { if (a > b) a = b; }
    template <class A, class B, class C> static inline constexpr void LIMIT(A& a, const B b, const C c) {
      if (a < b) a = b;
      else if (a > c) a = c;
    }
  }

#else

  // NUM_ARGS(...) evaluates to the number of arguments
  #define _NUM_ARGS(X,X6,X5,X4,X3,X2,X1,N,...) N
  #define NUM_ARGS(...)     _NUM_ARGS(0, __VA_ARGS__ ,6,5,4,3,2,1,0)

  #define MIN_2(a,b)        ({__typeof__(a) _a = (a); __typeof__(b) _b = (b); _a < _b ? _a : _b;})
  #define MIN_3(a,...)      MIN_2(a,MIN_2(__VA_ARGS__))
  #define MIN_4(a,...)      MIN_2(a,MIN_3(__VA_ARGS__))
  #define MIN_5(a,...)      MIN_2(a,MIN_4(__VA_ARGS__))
  #define MIN_6(a,...)      MIN_2(a,MIN_5(__VA_ARGS__))
  #define __MIN_N(N, ...)   MIN_ ## N(__VA_ARGS__)
  #define _MIN_N(N, ...)    __MIN_N(N, __VA_ARGS__)
  #define MIN(...)          _MIN_N(NUM_ARGS(__VA_ARGS__), __VA_ARGS__)

  #define MAX_2(a,b)        ({__typeof__(a) _a = (a); __typeof__(b) _b = (b); _a > _b ? _a : _b;})
  #define MAX_3(a,...)      MAX_2(a,MAX_2(__VA_ARGS__))
  #define MAX_4(a,...)      MAX_2(a,MAX_3(__VA_ARGS__))
  #define MAX_5(a,...)      MAX_2(a,MAX_4(__VA_ARGS__))
  #define MAX_6(a,...)      MAX_2(a,MAX_5(__VA_ARGS__))
  #define __MAX_N(N, ...)   MAX_ ## N(__VA_ARGS__)
  #define _MAX_N(N, ...)    __MAX_N(N, __VA_ARGS__)
  #define MAX(...)          _MAX_N(NUM_ARGS(__VA_ARGS__), __VA_ARGS__)

  #define ABS(a)            ({__typeof__(a) _a = (a); _a >= 0 ? _a : -_a;})

  #define NOLESS(v, n)      do { __typeof__(n) _n = (n); if (v < _n) v = _n; } while(0)
  #define NOMORE(v, n)      do { __typeof__(n) _n = (n); if (v > _n) v = _n; } while(0)
  #define LIMIT(v, n1, n2)  do { __typeof__(n1) _n1 = (n1); __typeof__(n2) _n2 = (n2); \
                                if (v < _n1) v = _n1; \
                                else if (v > _n2) v = _n2; \
                            } while(0)

#endif
