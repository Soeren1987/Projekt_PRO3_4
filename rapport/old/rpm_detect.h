/*
 * rpm_detect.h
 *
 *  Created on: 25. apr. 2019
 *      Author: Søren Korsgaard
 */

#ifndef RPM_DETECT_H_
#define RPM_DETECT_H_
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"



void init_read_rpm();
int get_rpm();


#endif /* RPM_DETECT_H_ */
