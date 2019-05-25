/*
 * rpm_detect.c
 *
 *  Created on: 25. apr. 2019
 *      Author: Søren Korsgaard
 */

#include "rpm_detect.h"
#define TPM_CH 0    // TPM channel for PTE 20
#define RPM_PIN 20  //PTE 20 is used to detect rpm

enum {
	wait, set_data
} state;
volatile int count;
void TPM1_IRQHandler() {
	static uint32_t overflows = 0;
	static uint32_t prev_count = 0;
	uint32_t timer_val;

	if (TPM1->STATUS & TPM_STATUS_TOF_MASK) {
		overflows++;
	}

	if (TPM1->STATUS & TPM_STATUS_CH0F_MASK) {
		timer_val = TPM1->CONTROLS[TPM_CH].CnV;
		timer_val |= (overflows << 16);
		count = timer_val - prev_count;
		prev_count = timer_val;
		state = set_data;
	}
	// reset all flags
	TPM1->STATUS |= TPM_STATUS_TOF_MASK | TPM_STATUS_CH0F_MASK
			| TPM_STATUS_CH1F_MASK;
}

void init_read_rpm() {
	//set clock
	SIM->SCGC6 |= SIM_SCGC6_TPM1_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
	//set clock source to TPM
	SIM->SOPT2 |= (SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK);
	//load counter to max value 2^16
	TPM1->MOD = 0xffff;
	//set channel to input capture and enable intterupt
	TPM1->CONTROLS[TPM_CH].CnSC = TPM_CnSC_ELSA_MASK | TPM_CnSC_CHIE_MASK;
	//set pin to timer TPM
	PORTE->PCR[RPM_PIN] |= (3UL << 8);
	// Enable0 interrupts, with 128 prescaler. so count freq is 48MHz /128 = 375 kHz
	TPM1->SC = TPM_SC_CMOD(1) | TPM_SC_PS(7) | TPM_SC_TOIE_MASK;

	NVIC_SetPriority(TPM1_IRQn, 3);
	NVIC_ClearPendingIRQ(TPM1_IRQn);
	NVIC_EnableIRQ(TPM1_IRQn);

}
int get_rpm() {
	int data = 0;
	while (state != set_data)
		;
	// 60 sek * frekvens 375000/input capture værdien
	data = 60 * 375000 / count;
	printf("rpm is: %d and count is : %d \n", data, count);
	state = wait;

	return data;
}
