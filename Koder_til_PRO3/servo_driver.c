/*
 * pwm.c
 *
 *  Created on: 7. nov. 2018
 *      Author: Søren Korsgaard
 */
/**
 * @file pwm.c
 * @brief Indeholder init filer til pwm og start funktion
 */
#include "pwm.h"

#define PERIOD 60000
#define MIN_VAL_SERVO 3000             // 1 ms to start servo
#define MAX_VALUE_SERVO 6000     // 2 ms to turn max on servo
#define START 3750               // Set duty cycle to 1.25 ms for 500 cranking rpm

#define START_BTN (1)      // PIN PTD1 Start button
#define SERVO_THROTTLE (2) // PIN PTD2 channel TPM0
#define ESC_SIGNAL (3)     // PIN PTD3 channel TPM0

#define PWM_CH_SERVO (2)   // PTD2 PWM Servo channel on TPM0
#define PWM_CH_ESC (3)     // PTD3 PWM ESC channel on TPM0

volatile int i = 0;

void SysTick_Handler(void) {
	i++;
}

void init_pwm() {
	/*
	 * Vi ønsker et 50 Hz signal. og vores clock er 48 Mhz.
	 * 48Mhz/50Hz = 960000, da vores counter er en 16 bit, dvs max decimal 65536.
	 * vores prescaler værdi er = 960000/65536 = 14,648, så vi sætter den til 16.
	 * vores count værdi bliver (960000/16)-1 = 59999 for at få en 50Hz frekvens
	 */
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;

	/*
	 * enable TPM in mux (4UL << 8);
	 */

	PORTD->PCR[SERVO_THROTTLE] |= (4UL << 8);
	PORTD->PCR[ESC_SIGNAL] |= (4UL << 8);
	/*Selects the clock source for the TPM counter clock:
	 * 01 MCGFLLCLK clock or MCGPLLCLK/2 = (1UL << 24)
	 Selects the MCGPLLCLK or MCGFLLCLK clock for various peripheral clocking options:
	 1 MCGPLLCLK clock with fixed divide by two = (1UL << 16)
	 */

	SIM->SOPT2 |= ((1UL << 24) | (1UL << 16));

	// Set count value in reach for 2^16 = 65536
	TPM0->MOD = PERIOD - 1;

	/*
	 * Prescale Factor Selection:
	 * 100 Divide by 16 = (1UL << 0)
	 */
	TPM0->SC = (4UL << 0);

	/*
	 * Debug Mode:
	 * 11 LPTPM counter continues in debug mode = (3UL << 6)
	 */

	TPM0->CONF |= (3UL << 6);

	/*
	 * Channel Mode Select: active HIGH
	 * ELSB = (1UL << 5)
	 * MSB = (1UL << )
	 * check side number 555 in manual for channel options
	 */
	TPM0->CONTROLS[PWM_CH_SERVO].CnSC = ((1UL << 3) | (1UL << 5));
	TPM0->CONTROLS[PWM_CH_ESC].CnSC = ((1UL << 3) | (1UL << 5));
	/*
	 * set duty cycle to 0
	 */
	TPM0->CONTROLS[PWM_CH_SERVO].CnV = MIN_VAL_SERVO;
	TPM0->CONTROLS[PWM_CH_ESC].CnV = MIN_VAL_SERVO;
	/*
	 * Clock Mode Selection
	 Selects the LPTPM counter clock modes. When disabling the counter, this field remain set until
	 acknolwedged in the LPTPM clock domain.

	 01 LPTPM counter increments on every LPTPM counter clock =  (1UL << 3)
	 */
	TPM0->SC |= (1UL << 3);

}
void angle_throttle(unsigned int procent) {

	if (procent > 0 && procent < 100) {
		int res = (MIN_VAL_SERVO * procent) / 100;
		TPM0->CONTROLS[PWM_CH_SERVO].CnV = MIN_VAL_SERVO + res;
	}

}
void init_start() {
	// set clock to PORTD
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
	// set pin too gpio
	PORTD->PCR[START_BTN] |= (1UL << 8);
	// set pin to input
	PTD->PDDR = (0UL << START_BTN);

}
void start() {
	init_start();
	while (1) {
		if (PTD->PDIR & (1UL << START_BTN)) {
			// Lave et interrupt for 500 ms
			initSystickTmr(1500000);
			//Sætter vores pwm signal med en puls på 1,25ms, dette genere 500 rpm +- 100 rpm
			TPM0->CONTROLS[PWM_CH_ESC].CnV = START;
			// Den skal starte så længe knappen er trykket ned og må maks cranke i 15 s
			while (i != 30 && PTD->PDIR != (0UL << START_BTN))
				;
			__disable_irq();
			//Sætter vores pwm signal puls til 1 ms, hvilket stopper Starteren
			TPM0->CONTROLS[PWM_CH_ESC].CnV = MIN_VAL_SERVO;
			break;

		} else
			continue;

	}

}

int initSystickTmr(unsigned int ticks) {

	if (ticks < 16777216) { //2^24
		SysTick->LOAD = (ticks);
		NVIC_SetPriority(SysTick_IRQn, 3); //enable interrupt
		SysTick->VAL = 0;                  // reload value
		SysTick->CTRL = SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
		return 0;
	} else
		return -1;
}
