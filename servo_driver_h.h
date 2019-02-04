/*
 * pwm.h
 *
 *  Created on: 7. nov. 2018
 *      Author: Søren Korsgaard
 */

#ifndef PWM_H_
#define PWM_H_
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"

/*
 * set TPM0 channel up to PWM signal.
 * active low
 */
void init_pwm();
/*
 * Function to control servo motor angle
 */
void angle_throttle(unsigned int procent);
/*
 * Initialize start routine
 */
void init_start();
/*
 * Function to start engine, by setting pwm signal to control ESC, which controlled the BLDC motor
 */
void start();
/*
 * Setup timer interrupt
 */
int initSystickTmr(unsigned int ticks);

#endif /* PWM_H_ */
