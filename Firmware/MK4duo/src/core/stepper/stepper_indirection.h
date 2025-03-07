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
 * stepper_indirection.h - stepper motor driver indirection macros
 * to allow some stepper functions to be done via SPI/I2c instead of direct pin manipulation
 * Part of MK4duo
 *
 * Copyright (c) 2015 Dominik Wenger
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
 */

#ifndef _STEPPER_INDIRECTION_H_
#define _STEPPER_INDIRECTION_H_

// TMC26X drivers have STEP/DIR on normal pins, but ENABLE via SPI
#if HAVE_DRV(TMC26X)
  #include <TMC26XStepper.h>
  void tmc26x_init_to_defaults();
#endif

// L6470 has STEP on normal pins, but DIR/ENABLE via SPI
#if HAVE_DRV(L6470)
  #include <L6470.h>
  void L6470_init_to_defaults();
#endif

void restore_stepper_drivers();  // Called by PSU_ON
void reset_stepper_drivers();    // Called by eeprom.load / eeprom.reset

// X Stepper
#if X_HAS_DRV(L6470)
  extern L6470 stepperX;
  #define X_ENABLE_INIT               NOOP
  #define X_ENABLE_WRITE(STATE)       do{ if(STATE) stepperX->Step_Clock(stepperX->getStatus() & STATUS_HIZ); else stepperX->softFree(); }while(0)
  #define X_ENABLE_READ               (stepperX->getStatus() & STATUS_HIZ)
  #define X_DIR_INIT                  NOOP
  #define X_DIR_WRITE(STATE)          stepperX->Step_Clock(STATE)
  #define X_DIR_READ                  (stepperX->getStatus() & STATUS_DIR)
#else
  #if X_HAS_DRV(TMC26X)
    extern TMC26XStepper stepperX;
    #define X_ENABLE_INIT             NOOP
    #define X_ENABLE_WRITE(STATE)     stepperX->setEnabled(STATE)
    #define X_ENABLE_READ             stepperX->isEnabled()
  #else
    #define X_ENABLE_INIT             SET_OUTPUT(X_ENABLE_PIN)
    #define X_ENABLE_WRITE(STATE)     WRITE(X_ENABLE_PIN,STATE)
    #define X_ENABLE_READ             READ(X_ENABLE_PIN)
  #endif
  #define X_DIR_INIT                  SET_OUTPUT(X_DIR_PIN)
  #define X_DIR_WRITE(STATE)          WRITE(X_DIR_PIN,STATE)
  #define X_DIR_READ                  READ(X_DIR_PIN)
#endif
#define X_STEP_INIT                   SET_OUTPUT(X_STEP_PIN)
#define X_STEP_WRITE(STATE)           WRITE(X_STEP_PIN,STATE)
#define X_STEP_READ                   READ(X_STEP_PIN)

// Y Stepper
#if Y_HAS_DRV(L6470)
  extern L6470 stepperY;
  #define Y_ENABLE_INIT               NOOP
  #define Y_ENABLE_WRITE(STATE)       do{ if(STATE) stepperY->Step_Clock(stepperY->getStatus() & STATUS_HIZ); else stepperY->softFree(); }while(0)
  #define Y_ENABLE_READ               (stepperY->getStatus() & STATUS_HIZ)
  #define Y_DIR_INIT                  NOOP
  #define Y_DIR_WRITE(STATE)          stepperY->Step_Clock(STATE)
  #define Y_DIR_READ                  (stepperY->getStatus() & STATUS_DIR)
#else
  #if Y_HAS_DRV(TMC26X)
    extern TMC26XStepper stepperY;
    #define Y_ENABLE_INIT             NOOP
    #define Y_ENABLE_WRITE(STATE)     stepperY->setEnabled(STATE)
    #define Y_ENABLE_READ             stepperY->isEnabled()
  #else
    #define Y_ENABLE_INIT             SET_OUTPUT(Y_ENABLE_PIN)
    #define Y_ENABLE_WRITE(STATE)     WRITE(Y_ENABLE_PIN,STATE)
    #define Y_ENABLE_READ             READ(Y_ENABLE_PIN)
  #endif
  #define Y_DIR_INIT                  SET_OUTPUT(Y_DIR_PIN)
  #define Y_DIR_WRITE(STATE)          WRITE(Y_DIR_PIN,STATE)
  #define Y_DIR_READ                  READ(Y_DIR_PIN)
#endif
#define Y_STEP_INIT                   SET_OUTPUT(Y_STEP_PIN)
#define Y_STEP_WRITE(STATE)           WRITE(Y_STEP_PIN,STATE)
#define Y_STEP_READ                   READ(Y_STEP_PIN)

// Z Stepper
#if Z_HAS_DRV(L6470)
  extern L6470 stepperZ;
  #define Z_ENABLE_INIT               NOOP
  #define Z_ENABLE_WRITE(STATE)       do{ if(STATE) stepperZ->Step_Clock(stepperZ->getStatus() & STATUS_HIZ); else stepperZ->softFree(); }while(0)
  #define Z_ENABLE_READ               (stepperZ->getStatus() & STATUS_HIZ)
  #define Z_DIR_INIT                  NOOP
  #define Z_DIR_WRITE(STATE)          stepperZ->Step_Clock(STATE)
  #define Z_DIR_READ                  (stepperZ->getStatus() & STATUS_DIR)
#else
  #if Z_HAS_DRV(TMC26X)
    extern TMC26XStepper stepperZ;
    #define Z_ENABLE_INIT             NOOP
    #define Z_ENABLE_WRITE(STATE)     stepperZ->setEnabled(STATE)
    #define Z_ENABLE_READ             stepperZ->isEnabled()
  #else
    #define Z_ENABLE_INIT             SET_OUTPUT(Z_ENABLE_PIN)
    #define Z_ENABLE_WRITE(STATE)     WRITE(Z_ENABLE_PIN,STATE)
    #define Z_ENABLE_READ             READ(Z_ENABLE_PIN)
  #endif
  #define Z_DIR_INIT                  SET_OUTPUT(Z_DIR_PIN)
  #define Z_DIR_WRITE(STATE)          WRITE(Z_DIR_PIN,STATE)
  #define Z_DIR_READ                  READ(Z_DIR_PIN)
#endif
#define Z_STEP_INIT                   SET_OUTPUT(Z_STEP_PIN)
#define Z_STEP_WRITE(STATE)           WRITE(Z_STEP_PIN,STATE)
#define Z_STEP_READ                   READ(Z_STEP_PIN)

// X2 Stepper
#if HAS_X2_ENABLE
  #if X2_HAS_DRV(L6470)
    extern L6470 stepperX2;
    #define X2_ENABLE_INIT            NOOP
    #define X2_ENABLE_WRITE(STATE)    do{ if(STATE) stepperX2->Step_Clock(stepperX2->getStatus() & STATUS_HIZ); else stepperX2->softFree(); }while(0)
    #define X2_ENABLE_READ            (stepperX2->getStatus() & STATUS_HIZ)
    #define X2_DIR_INIT               NOOP
    #define X2_DIR_WRITE(STATE)       stepperX2->Step_Clock(STATE)
    #define X2_DIR_READ               (stepperX2->getStatus() & STATUS_DIR)
  #else
    #if X2_HAS_DRV(TMC26X)
      extern TMC26XStepper stepperX2;
      #define X2_ENABLE_INIT          NOOP
      #define X2_ENABLE_WRITE(STATE)  stepperX2->setEnabled(STATE)
      #define X2_ENABLE_READ          stepperX2->isEnabled()
    #else
      #define X2_ENABLE_INIT          SET_OUTPUT(X2_ENABLE_PIN)
      #define X2_ENABLE_WRITE(STATE)  WRITE(X2_ENABLE_PIN,STATE)
      #define X2_ENABLE_READ          READ(X2_ENABLE_PIN)
    #endif
    #define X2_DIR_INIT               SET_OUTPUT(X2_DIR_PIN)
    #define X2_DIR_WRITE(STATE)       WRITE(X2_DIR_PIN,STATE)
    #define X2_DIR_READ               READ(X2_DIR_PIN)
  #endif
  #define X2_STEP_INIT                SET_OUTPUT(X2_STEP_PIN)
  #define X2_STEP_WRITE(STATE)        WRITE(X2_STEP_PIN,STATE)
  #define X2_STEP_READ                READ(X2_STEP_PIN)
#endif

// Y2 Stepper
#if HAS_Y2_ENABLE
  #if Y2_HAS_DRV(L6470)
    extern L6470 stepperY2;
    #define Y2_ENABLE_INIT            NOOP
    #define Y2_ENABLE_WRITE(STATE)    do{ if(STATE) stepperY2->Step_Clock(stepperY2->getStatus() & STATUS_HIZ); else stepperY2->softFree(); }while(0)
    #define Y2_ENABLE_READ            (stepperY2->getStatus() & STATUS_HIZ)
    #define Y2_DIR_INIT               NOOP
    #define Y2_DIR_WRITE(STATE)       stepperY2->Step_Clock(STATE)
    #define Y2_DIR_READ               (stepperY2->getStatus() & STATUS_DIR)
  #else
    #if Y2_HAS_DRV(TMC26X)
      extern TMC26XStepper stepperY2;
      #define Y2_ENABLE_INIT          NOOP
      #define Y2_ENABLE_WRITE(STATE)  stepperY2->setEnabled(STATE)
      #define Y2_ENABLE_READ          stepperY2->isEnabled()
    #else
      #define Y2_ENABLE_INIT          SET_OUTPUT(Y2_ENABLE_PIN)
      #define Y2_ENABLE_WRITE(STATE)  WRITE(Y2_ENABLE_PIN,STATE)
      #define Y2_ENABLE_READ          READ(Y2_ENABLE_PIN)
    #endif
    #define Y2_DIR_INIT               SET_OUTPUT(Y2_DIR_PIN)
    #define Y2_DIR_WRITE(STATE)       WRITE(Y2_DIR_PIN,STATE)
    #define Y2_DIR_READ               READ(Y2_DIR_PIN)
  #endif
  #define Y2_STEP_INIT                SET_OUTPUT(Y2_STEP_PIN)
  #define Y2_STEP_WRITE(STATE)        WRITE(Y2_STEP_PIN,STATE)
  #define Y2_STEP_READ                READ(Y2_STEP_PIN)
#endif

// Z2 Stepper
#if HAS_Z2_ENABLE
  #if Z2_HAS_DRV(L6470)
    extern L6470 stepperZ2;
    #define Z2_ENABLE_INIT            NOOP
    #define Z2_ENABLE_WRITE(STATE)    do{ if(STATE) stepperZ2->Step_Clock(stepperZ2->getStatus() & STATUS_HIZ); else stepperZ2->softFree(); }while(0)
    #define Z2_ENABLE_READ            (stepperZ2->getStatus() & STATUS_HIZ)
    #define Z2_DIR_INIT               NOOP
    #define Z2_DIR_WRITE(STATE)       stepperZ2->Step_Clock(STATE)
    #define Z2_DIR_READ               (stepperZ2->getStatus() & STATUS_DIR)
  #else
    #if Z2_HAS_DRV(TMC26X)
      extern TMC26XStepper stepperZ2;
      #define Z2_ENABLE_INIT          NOOP
      #define Z2_ENABLE_WRITE(STATE)  stepperZ2->setEnabled(STATE)
      #define Z2_ENABLE_READ          stepperZ2->isEnabled()
    #else
      #define Z2_ENABLE_INIT          SET_OUTPUT(Z2_ENABLE_PIN)
      #define Z2_ENABLE_WRITE(STATE)  WRITE(Z2_ENABLE_PIN,STATE)
      #define Z2_ENABLE_READ          READ(Z2_ENABLE_PIN)
    #endif
    #define Z2_DIR_INIT               SET_OUTPUT(Z2_DIR_PIN)
    #define Z2_DIR_WRITE(STATE)       WRITE(Z2_DIR_PIN,STATE)
    #define Z2_DIR_READ               READ(Z2_DIR_PIN)
  #endif
  #define Z2_STEP_INIT                SET_OUTPUT(Z2_STEP_PIN)
  #define Z2_STEP_WRITE(STATE)        WRITE(Z2_STEP_PIN,STATE)
  #define Z2_STEP_READ                READ(Z2_STEP_PIN)
#endif

// Z3 Stepper
#if HAS_Z3_ENABLE
  #if Z3_HAS_DRV(L6470)
    extern L6470 stepperZ3;
    #define Z3_ENABLE_INIT            NOOP
    #define Z3_ENABLE_WRITE(STATE)    do{ if(STATE) stepperZ3->Step_Clock(stepperZ3->getStatus() & STATUS_HIZ); else stepperZ3->softFree(); }while(0)
    #define Z3_ENABLE_READ            (stepperZ3->getStatus() & STATUS_HIZ)
    #define Z3_DIR_INIT               NOOP
    #define Z3_DIR_WRITE(STATE)       stepperZ3->Step_Clock(STATE)
    #define Z3_DIR_READ               (stepperZ3->getStatus() & STATUS_DIR)
  #else
    #if Z3_HAS_DRV(TMC26X)
      extern TMC26XStepper stepperZ3;
      #define Z3_ENABLE_INIT          NOOP
      #define Z3_ENABLE_WRITE(STATE)  stepperZ3->setEnabled(STATE)
      #define Z3_ENABLE_READ          stepperZ3->isEnabled()
    #else
      #define Z3_ENABLE_INIT          SET_OUTPUT(Z3_ENABLE_PIN)
      #define Z3_ENABLE_WRITE(STATE)  WRITE(Z3_ENABLE_PIN,STATE)
      #define Z3_ENABLE_READ          READ(Z3_ENABLE_PIN)
    #endif
    #define Z3_DIR_INIT               SET_OUTPUT(Z3_DIR_PIN)
    #define Z3_DIR_WRITE(STATE)       WRITE(Z3_DIR_PIN,STATE)
    #define Z3_DIR_READ               READ(Z3_DIR_PIN)
  #endif
  #define Z3_STEP_INIT                SET_OUTPUT(Z3_STEP_PIN)
  #define Z3_STEP_WRITE(STATE)        WRITE(Z3_STEP_PIN,STATE)
  #define Z3_STEP_READ                READ(Z3_STEP_PIN)
#endif

// Z4 Stepper
#if HAS_Z4_ENABLE
  #if Z4_HAS_DRV(L6470)
    extern L6470 stepperZ4;
    #define Z4_ENABLE_INIT            NOOP
    #define Z4_ENABLE_WRITE(STATE)    do{ if(STATE) stepperZ4.Step_Clock(stepperZ4.getStatus() & STATUS_HIZ); else stepperZ4.softFree(); }while(0)
    #define Z4_ENABLE_READ            (stepperZ4.getStatus() & STATUS_HIZ)
    #define Z4_DIR_INIT               NOOP
    #define Z4_DIR_WRITE(STATE)       stepperZ4.Step_Clock(STATE)
    #define Z4_DIR_READ               (stepperZ4.getStatus() & STATUS_DIR)
  #else
    #if Z4_HAS_DRV(TMC26X)
      extern TMC26XStepper stepperZ4;
      #define Z4_ENABLE_INIT          NOOP
      #define Z4_ENABLE_WRITE(STATE)  stepperZ4.setEnabled(STATE)
      #define Z4_ENABLE_READ          stepperZ4.isEnabled()
    #else
      #define Z4_ENABLE_INIT          SET_OUTPUT(Z4_ENABLE_PIN)
      #define Z4_ENABLE_WRITE(STATE)  WRITE(Z4_ENABLE_PIN,STATE)
      #define Z4_ENABLE_READ          READ(Z4_ENABLE_PIN)
    #endif
    #define Z4_DIR_INIT               SET_OUTPUT(Z4_DIR_PIN)
    #define Z4_DIR_WRITE(STATE)       WRITE(Z4_DIR_PIN,STATE)
    #define Z4_DIR_READ               READ(Z4_DIR_PIN)
  #endif
  #define Z4_STEP_INIT                SET_OUTPUT(Z4_STEP_PIN)
  #define Z4_STEP_WRITE(STATE)        WRITE(Z4_STEP_PIN,STATE)
  #define Z4_STEP_READ                READ(Z4_STEP_PIN)
#endif

#if E0_HAS_DRV(L6470)
  extern L6470 stepperE0;
  #define E0_ENABLE_INIT              NOOP
  #define E0_ENABLE_WRITE(STATE)      do{ if(STATE) stepperE0->Step_Clock(stepperE0->getStatus() & STATUS_HIZ); else stepperE0->softFree(); }while(0)
  #define E0_ENABLE_READ              (stepperE0->getStatus() & STATUS_HIZ)
  #define E0_DIR_INIT                 NOOP
  #define E0_DIR_WRITE(STATE)         stepperE0->Step_Clock(STATE)
  #define E0_DIR_READ                 (stepperE0->getStatus() & STATUS_DIR)
#else
  #if E0_HAS_DRV(TMC26X)
    extern TMC26XStepper stepperE0;
    #define E0_ENABLE_INIT            NOOP
    #define E0_ENABLE_WRITE(STATE)    stepperE0->setEnabled(STATE)
    #define E0_ENABLE_READ            stepperE0->isEnabled()
  #else
    #define E0_ENABLE_INIT            SET_OUTPUT(E0_ENABLE_PIN)
    #define E0_ENABLE_WRITE(STATE)    WRITE(E0_ENABLE_PIN,STATE)
    #define E0_ENABLE_READ            READ(E0_ENABLE_PIN)
  #endif
  #define E0_DIR_INIT                 SET_OUTPUT(E0_DIR_PIN)
  #define E0_DIR_WRITE(STATE)         WRITE(E0_DIR_PIN,STATE)
  #define E0_DIR_READ                 READ(E0_DIR_PIN)
#endif
#if HAS_DAV_SYSTEM
  #define E0_STEP_INIT                SET_OUTPUT(E0_STEP_PIN); SET_OUTPUT(FIL_RUNOUT_DAV_PIN)
  #define E0_STEP_WRITE(STATE)        WRITE(E0_STEP_PIN,STATE); WRITE(FIL_RUNOUT_DAV_PIN,STATE)
  #define E0_STEP_READ                READ(E0_STEP_PIN)
#else
  #define E0_STEP_INIT                SET_OUTPUT(E0_STEP_PIN)
  #define E0_STEP_WRITE(STATE)        WRITE(E0_STEP_PIN,STATE)
  #define E0_STEP_READ                READ(E0_STEP_PIN)
#endif

// E1 Stepper
#if E1_HAS_DRV(L6470)
  extern L6470 stepperE1;
  #define E1_ENABLE_INIT              NOOP
  #define E1_ENABLE_WRITE(STATE)      do{if(STATE) stepperE1->Step_Clock(stepperE1->getStatus() & STATUS_HIZ); else stepperE1->softFree();}while(0)
  #define E1_ENABLE_READ              (stepperE1->getStatus() & STATUS_HIZ)
  #define E1_DIR_INIT                 NOOP
  #define E1_DIR_WRITE(STATE)         stepperE1->Step_Clock(STATE)
  #define E1_DIR_READ                 (stepperE1->getStatus() & STATUS_DIR)
#else
  #if E1_HAS_DRV(TMC26X)
    extern TMC26XStepper stepperE1;
    #define E1_ENABLE_INIT            NOOP
    #define E1_ENABLE_WRITE(STATE)    stepperE1->setEnabled(STATE)
    #define E1_ENABLE_READ            stepperE1->isEnabled()
  #else
    #define E1_ENABLE_INIT            SET_OUTPUT(E1_ENABLE_PIN)
    #define E1_ENABLE_WRITE(STATE)    WRITE(E1_ENABLE_PIN,STATE)
    #define E1_ENABLE_READ            READ(E1_ENABLE_PIN)
  #endif
  #define E1_DIR_INIT                 SET_OUTPUT(E1_DIR_PIN)
  #define E1_DIR_WRITE(STATE)         WRITE(E1_DIR_PIN,STATE)
  #define E1_DIR_READ                 READ(E1_DIR_PIN)
#endif
#define E1_STEP_INIT                  SET_OUTPUT(E1_STEP_PIN)
#define E1_STEP_WRITE(STATE)          WRITE(E1_STEP_PIN,STATE)
#define E1_STEP_READ                  READ(E1_STEP_PIN)

// E2 Stepper
#if E2_HAS_DRV(L6470)
  extern L6470 stepperE2;
  #define E2_ENABLE_INIT              NOOP
  #define E2_ENABLE_WRITE(STATE)      do{if(STATE) stepperE2->Step_Clock(stepperE2->getStatus() & STATUS_HIZ); else stepperE2->softFree();}while(0)
  #define E2_ENABLE_READ              (stepperE2->getStatus() & STATUS_HIZ)
  #define E2_DIR_INIT                 NOOP
  #define E2_DIR_WRITE(STATE)         stepperE2->Step_Clock(STATE)
  #define E2_DIR_READ                 (stepperE2->getStatus() & STATUS_DIR)
#else
  #if E2_HAS_DRV(TMC26X)
    extern TMC26XStepper stepperE2;
    #define E2_ENABLE_INIT            NOOP
    #define E2_ENABLE_WRITE(STATE)    stepperE2->setEnabled(STATE)
    #define E2_ENABLE_READ            stepperE2->isEnabled()
  #else
    #define E2_ENABLE_INIT            SET_OUTPUT(E2_ENABLE_PIN)
    #define E2_ENABLE_WRITE(STATE)    WRITE(E2_ENABLE_PIN,STATE)
    #define E2_ENABLE_READ            READ(E2_ENABLE_PIN)
  #endif
  #define E2_DIR_INIT                 SET_OUTPUT(E2_DIR_PIN)
  #define E2_DIR_WRITE(STATE)         WRITE(E2_DIR_PIN,STATE)
  #define E2_DIR_READ                 READ(E2_DIR_PIN)
#endif
#define E2_STEP_INIT                  SET_OUTPUT(E2_STEP_PIN)
#define E2_STEP_WRITE(STATE)          WRITE(E2_STEP_PIN,STATE)
#define E2_STEP_READ                  READ(E2_STEP_PIN)

// E3 Stepper
#if E3_HAS_DRV(L6470)
  extern L6470 stepperE3;
  #define E3_ENABLE_INIT              NOOP
  #define E3_ENABLE_WRITE(STATE)      do{if(STATE) stepperE3->Step_Clock(stepperE3->getStatus() & STATUS_HIZ); else stepperE3->softFree();}while(0)
  #define E3_ENABLE_READ              (stepperE3->getStatus() & STATUS_HIZ)
  #define E3_DIR_INIT                 NOOP
  #define E3_DIR_WRITE(STATE)         stepperE3->Step_Clock(STATE)
  #define E3_DIR_READ                 (stepperE3->getStatus() & STATUS_DIR)
#else
  #if E3_HAS_DRV(TMC26X)
    extern TMC26XStepper stepperE3;
    #define E3_ENABLE_INIT            NOOP
    #define E3_ENABLE_WRITE(STATE)    stepperE3->setEnabled(STATE)
    #define E3_ENABLE_READ            stepperE3->isEnabled()
  #else
    #define E3_ENABLE_INIT            SET_OUTPUT(E3_ENABLE_PIN)
    #define E3_ENABLE_WRITE(STATE)    WRITE(E3_ENABLE_PIN,STATE)
    #define E3_ENABLE_READ            READ(E3_ENABLE_PIN)
  #endif
  #define E3_DIR_INIT                 SET_OUTPUT(E3_DIR_PIN)
  #define E3_DIR_WRITE(STATE)         WRITE(E3_DIR_PIN,STATE)
  #define E3_DIR_READ                 READ(E3_DIR_PIN)
#endif
#define E3_STEP_INIT                  SET_OUTPUT(E3_STEP_PIN)
#define E3_STEP_WRITE(STATE)          WRITE(E3_STEP_PIN,STATE)
#define E3_STEP_READ                  READ(E3_STEP_PIN)

// E4 Stepper
#if E4_HAS_DRV(L6470)
  extern L6470 stepperE4;
  #define E4_ENABLE_INIT              NOOP
  #define E4_ENABLE_WRITE(STATE)      do{ if (STATE) stepperE4->Step_Clock(stepperE4->getStatus() & STATUS_HIZ); else stepperE4->softFree(); }while(0)
  #define E4_ENABLE_READ              (stepperE4->getStatus() & STATUS_HIZ)
  #define E4_DIR_INIT                 NOOP
  #define E4_DIR_WRITE(STATE)         stepperE4->Step_Clock(STATE)
  #define E4_DIR_READ                 (stepperE4->getStatus() & STATUS_DIR)
#else
  #if E4_HAS_DRV(TMC26X)
    extern TMC26XStepper stepperE4;
    #define E4_ENABLE_INIT            NOOP
    #define E4_ENABLE_WRITE(STATE)    stepperE4->setEnabled(STATE)
    #define E4_ENABLE_READ            stepperE4->isEnabled()
  #else
    #define E4_ENABLE_INIT            SET_OUTPUT(E4_ENABLE_PIN)
    #define E4_ENABLE_WRITE(STATE)    WRITE(E4_ENABLE_PIN,STATE)
    #define E4_ENABLE_READ            READ(E4_ENABLE_PIN)
  #endif
  #define E4_DIR_INIT                 SET_OUTPUT(E4_DIR_PIN)
  #define E4_DIR_WRITE(STATE)         WRITE(E4_DIR_PIN,STATE)
  #define E4_DIR_READ                 READ(E4_DIR_PIN)
#endif
#define E4_STEP_INIT                  SET_OUTPUT(E4_STEP_PIN)
#define E4_STEP_WRITE(STATE)          WRITE(E4_STEP_PIN,STATE)
#define E4_STEP_READ                  READ(E4_STEP_PIN)

// E5 Stepper
#if E5_HAS_DRV(L6470)
  extern L6470 stepperE5;
  #define E5_ENABLE_INIT              NOOP
  #define E5_ENABLE_WRITE(STATE)      do{if(STATE) stepperE5->Step_Clock(stepperE5->getStatus() & STATUS_HIZ); else stepperE5->softFree();}while(0)
  #define E5_ENABLE_READ              (stepperE5->getStatus() & STATUS_HIZ)
  #define E5_DIR_INIT                 NOOP
  #define E5_DIR_WRITE(STATE)         stepperE5->Step_Clock(STATE)
  #define E5_DIR_READ                 (stepperE5->getStatus() & STATUS_DIR)
#else
  #if E5_HAS_DRV(TMC26X)
    extern TMC26XStepper stepperE5;
    #define E5_ENABLE_INIT            NOOP
    #define E5_ENABLE_WRITE(STATE)    stepperE5->setEnabled(STATE)
    #define E5_ENABLE_READ            stepperE5->isEnabled()
  #else
    #define E5_ENABLE_INIT            SET_OUTPUT(E5_ENABLE_PIN)
    #define E5_ENABLE_WRITE(STATE)    WRITE(E5_ENABLE_PIN,STATE)
    #define E5_ENABLE_READ            READ(E5_ENABLE_PIN)
  #endif
  #define E5_DIR_INIT                 SET_OUTPUT(E5_DIR_PIN)
  #define E5_DIR_WRITE(STATE)         WRITE(E5_DIR_PIN,STATE)
  #define E5_DIR_READ                 READ(E5_DIR_PIN)
#endif
#define E5_STEP_INIT                  SET_OUTPUT(E5_STEP_PIN)
#define E5_STEP_WRITE(STATE)          WRITE(E5_STEP_PIN,STATE)
#define E5_STEP_READ                  READ(E5_STEP_PIN)

/**
 * Extruder indirection for the single E axis
 */
#if DRIVER_EXTRUDERS > 5
  #define E_STEP_WRITE(E,V)     do{ switch (E) { case 0: E0_STEP_WRITE(V); break; case 1: E1_STEP_WRITE(V); break; case 2: E2_STEP_WRITE(V); break; case 3: E3_STEP_WRITE(V); break; case 4: E4_STEP_WRITE(V); break; case 5: E5_STEP_WRITE(V); } }while(0)
  #define   NORM_E_DIR(E)       do{ switch (E) { case 0: E0_DIR_WRITE(!isStepDir(E0_AXIS)); break; case 1: E1_DIR_WRITE(!isStepDir(E1_AXIS)); break; case 2: E2_DIR_WRITE(!isStepDir(E2_AXIS)); break; case 3: E3_DIR_WRITE(!isStepDir(E3_AXIS)); break; case 4: E4_DIR_WRITE(!isStepDir(E4_AXIS)); break; case 5: E5_DIR_WRITE(!isStepDir(E5_AXIS)); } }while(0)
  #define    REV_E_DIR(E)       do{ switch (E) { case 0: E0_DIR_WRITE( isStepDir(E0_AXIS)); break; case 1: E1_DIR_WRITE( isStepDir(E1_AXIS)); break; case 2: E2_DIR_WRITE( isStepDir(E2_AXIS)); break; case 3: E3_DIR_WRITE( isStepDir(E3_AXIS)); break; case 4: E4_DIR_WRITE( isStepDir(E4_AXIS)); break; case 5: E5_DIR_WRITE( isStepDir(E5_AXIS)); } }while(0)
#elif DRIVER_EXTRUDERS > 4
  #define E_STEP_WRITE(E,V)     do{ switch (E) { case 0: E0_STEP_WRITE(V); break; case 1: E1_STEP_WRITE(V); break; case 2: E2_STEP_WRITE(V); break; case 3: E3_STEP_WRITE(V); break; case 4: E4_STEP_WRITE(V); } }while(0)
  #define   NORM_E_DIR(E)       do{ switch (E) { case 0: E0_DIR_WRITE(!isStepDir(E0_AXIS)); break; case 1: E1_DIR_WRITE(!isStepDir(E1_AXIS)); break; case 2: E2_DIR_WRITE(!isStepDir(E2_AXIS)); break; case 3: E3_DIR_WRITE(!isStepDir(E3_AXIS)); break; case 4: E4_DIR_WRITE(!isStepDir(E4_AXIS)); } }while(0)
  #define    REV_E_DIR(E)       do{ switch (E) { case 0: E0_DIR_WRITE( isStepDir(E0_AXIS)); break; case 1: E1_DIR_WRITE( isStepDir(E1_AXIS)); break; case 2: E2_DIR_WRITE( isStepDir(E2_AXIS)); break; case 3: E3_DIR_WRITE( isStepDir(E3_AXIS)); break; case 4: E4_DIR_WRITE( isStepDir(E4_AXIS)); } }while(0)
#elif DRIVER_EXTRUDERS > 3
  #define E_STEP_WRITE(E,V)     do{ switch (E) { case 0: E0_STEP_WRITE(V); break; case 1: E1_STEP_WRITE(V); break; case 2: E2_STEP_WRITE(V); break; case 3: E3_STEP_WRITE(V); } }while(0)
  #define   NORM_E_DIR(E)       do{ switch (E) { case 0: E0_DIR_WRITE(!isStepDir(E0_AXIS)); break; case 1: E1_DIR_WRITE(!isStepDir(E1_AXIS)); break; case 2: E2_DIR_WRITE(!isStepDir(E2_AXIS)); break; case 3: E3_DIR_WRITE(!isStepDir(E3_AXIS)); } }while(0)
  #define    REV_E_DIR(E)       do{ switch (E) { case 0: E0_DIR_WRITE( isStepDir(E0_AXIS)); break; case 1: E1_DIR_WRITE( isStepDir(E1_AXIS)); break; case 2: E2_DIR_WRITE( isStepDir(E2_AXIS)); break; case 3: E3_DIR_WRITE( isStepDir(E3_AXIS)); } }while(0)
#elif DRIVER_EXTRUDERS > 2
  #define E_STEP_WRITE(E,V)     do{ switch (E) { case 0: E0_STEP_WRITE(V); break; case 1: E1_STEP_WRITE(V); break; case 2: E2_STEP_WRITE(V); } }while(0)
  #define   NORM_E_DIR(E)       do{ switch (E) { case 0: E0_DIR_WRITE(!isStepDir(E0_AXIS)); break; case 1: E1_DIR_WRITE(!isStepDir(E1_AXIS)); break; case 2: E2_DIR_WRITE(!isStepDir(E2_AXIS)); } }while(0)
  #define    REV_E_DIR(E)       do{ switch (E) { case 0: E0_DIR_WRITE( isStepDir(E0_AXIS)); break; case 1: E1_DIR_WRITE( isStepDir(E1_AXIS)); break; case 2: E2_DIR_WRITE( isStepDir(E2_AXIS)); } }while(0)
#elif DRIVER_EXTRUDERS > 1
  #if ENABLED(DUAL_X_CARRIAGE)
    #define E_STEP_WRITE(E,V)   do{ if (mechanics.extruder_duplication_enabled) { E0_STEP_WRITE(V); E1_STEP_WRITE(V); } else if ((E) == 0) { E0_STEP_WRITE(V); } else { E1_STEP_WRITE(V); } }while(0)
    #define   NORM_E_DIR(E)     do{ if (mechanics.extruder_duplication_enabled) { E0_DIR_WRITE(!isStepDir(E0_AXIS)); E1_DIR_WRITE(!isStepDir(E1_AXIS)); } else if ((E) == 0) { E0_DIR_WRITE(!isStepDir(E0_AXIS)); } else { E1_DIR_WRITE(!isStepDir(E1_AXIS)); } }while(0)
    #define    REV_E_DIR(E)     do{ if (mechanics.extruder_duplication_enabled) { E0_DIR_WRITE( isStepDir(E0_AXIS)); E1_DIR_WRITE( isStepDir(E1_AXIS)); } else if ((E) == 0) { E0_DIR_WRITE( isStepDir(E0_AXIS)); } else { E1_DIR_WRITE( isStepDir(E1_AXIS)); } }while(0)
  #else
    #define E_STEP_WRITE(E,V)   do{ if (E == 0) { E0_STEP_WRITE(V); } else { E1_STEP_WRITE(V); } }while(0)
    #define   NORM_E_DIR(E)     do{ if (E == 0) { E0_DIR_WRITE(!isStepDir(E0_AXIS)); } else { E1_DIR_WRITE(!isStepDir(E1_AXIS)); } }while(0)
    #define    REV_E_DIR(E)     do{ if (E == 0) { E0_DIR_WRITE( isStepDir(E0_AXIS)); } else { E1_DIR_WRITE( isStepDir(E1_AXIS)); } }while(0)
  #endif
#elif DRIVER_EXTRUDERS > 0
  #if ENABLED(DONDOLO_SINGLE_MOTOR)
    #define E_STEP_WRITE(E,V)   E0_STEP_WRITE(v)
    #define NORM_E_DIR(E)       do{ E0_DIR_WRITE(E ?  isStepDir(E0_AXIS) : !isStepDir(E0_AXIS)); }while(0)
    #define  REV_E_DIR(E)       do{ E0_DIR_WRITE(E ? !isStepDir(E0_AXIS) :  isStepDir(E0_AXIS)); }while(0)
  #else
    #define E_STEP_WRITE(E,V)   E0_STEP_WRITE(V)
    #define   NORM_E_DIR(E)     E0_DIR_WRITE(!isStepDir(E0_AXIS))
    #define    REV_E_DIR(E)     E0_DIR_WRITE( isStepDir(E0_AXIS))
  #endif
#endif // DRIVER_EXTRUDERS

#endif /* _STEPPER_INDIRECTION_H_ */
