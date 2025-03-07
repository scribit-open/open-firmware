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
 * servo.h - Interrupt driven Servo library for Arduino using 16 bit timers- Version 2
 * Copyright (c) 2009 Michael Margolis. All right reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

/**
  A servo is activated by creating an instance of the Servo class passing
  the desired pin to the attach() method.
  The servos are pulsed in the background using the value most recently
  written using the write() method.

  Note that analogWrite of PWM on pins associated with the timer are
  disabled when the first servo is attached.
  Timers are seized as needed in groups of 12 servos - 24 servos use two
  timers, 48 servos will use four.
  The sequence used to sieze timers is defined in timers.h

  The methods are:

    Servo - Class for manipulating servo motors connected to Arduino pins.

    attach(pin )  - Attaches a servo motor to an i/o pin.
    attach(pin, min, max  ) - Attaches to a pin setting min and max values in microseconds
    default min is 544, max is 2400

    write()     - Sets the servo angle in degrees.  (invalid angle that is valid as pulse in microseconds is treated as microseconds)
    writeMicroseconds() - Sets the servo pulse width in microseconds
    read()      - Gets the last written servo pulse width as an angle between 0 and 180.
    readMicroseconds()   - Gets the last written servo pulse width in microseconds. (was read_us() in first release)
    attached()  - Returns true if there is a servo attached.
    detach()    - Stops an attached servos from pulsing its i/o pin.
    move(angle) - Sequence of attach(0), write(angle),
                    With DEACTIVATE_SERVOS_AFTER_MOVE wait SERVO_DELAY and detach.
 */

#ifndef _SERVO_H_
#define _SERVO_H_

#if HAS_SERVOS

  #include <inttypes.h>

  #if ENABLED(ARDUINO_ARCH_SAM)
    #include "../HAL_DUE/servotimers.h"
  #elif ENABLED(__AVR__)
    #include "../HAL_AVR/servotimers.h"
  #else
    #error "Unsupported Platform!"
  #endif

  /**
   * Defines for 16 bit timers used with  Servo library
   *
   * If _useTimerX is defined then TimerX is a 16 bit timer on the current board
   * timer16_Sequence_t enumerates the sequence that the timers should be allocated
   * _Nbr_16timers indicates how many 16 bit timers are available.
   */

  #define Servo_VERSION           2     // software version of this library

  #define MIN_PULSE_WIDTH       544     // the shortest pulse sent to a servo
  #define MAX_PULSE_WIDTH      2400     // the longest pulse sent to a servo
  #define DEFAULT_PULSE_WIDTH  1500     // default pulse width when servo is attached
  #define REFRESH_INTERVAL    20000     // minumim time to refresh servos in microseconds

  #define SERVOS_PER_TIMER       12     // the maximum number of servos controlled by one timer
  #define MAX_SERVOS          (_Nbr_16timers  * SERVOS_PER_TIMER)

  #define INVALID_SERVO         255     // flag indicating an invalid servo index

  #define MOVE_SERVO(I, P)    servo[I].move(P)

  extern void servo_init();

  typedef struct {
    uint8_t nbr        :6 ;             // a pin number from 0 to 63
    uint8_t isActive   :1 ;             // true if this channel is enabled, pin not pulsed if false
  } ServoPin_t;

  typedef struct {
    ServoPin_t Pin;
    unsigned int ticks;
  } ServoInfo_t;

  class Servo {

    public: /** Constructor */

      Servo();

    public: /** Public Parameters */

      int angle[2];

    private: /** Private Parameters */

      uint8_t index;  // index into the channel data for this servo
      int8_t  min,    // minimum is this value times 4 added to MIN_PULSE_WIDTH
              max;    // maximum is this value times 4 added to MAX_PULSE_WIDTH

    public: /** Public Function */

      int8_t attach(const pin_t pin);                   // attach the given pin to the next free channel, sets pinMode, returns channel number or 0 if failure
      int8_t attach(const pin_t pin, int min, int max); // as above but also sets min and max values for writes.
      void detach();
      void write(int value);              // if value is < 200 it is treated as an angle, otherwise as pulse width in microseconds
      void writeMicroseconds(int value);  // Write pulse width in microseconds
      void move(int value);               // attach the servo, then move to value
                                          // if value is < 200 it is treated as an angle, otherwise as pulse width in microseconds
                                          // if DEACTIVATE_SERVOS_AFTER_MOVE wait SERVO_DEACTIVATION_DELAY, then detach
      int read();                         // returns current pulse width as an angle between 0 and 180 degrees
      int readMicroseconds();             // returns current pulse width in microseconds for this servo (was read_us() in first release)
      bool attached();                    // return true if this servo is attached, otherwise false

      void print_parameters();

  };

  extern Servo servo[NUM_SERVOS];

#endif // SERVOS

#endif /* _SERVO_H_ */
