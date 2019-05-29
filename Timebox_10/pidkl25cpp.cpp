#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "rpm-detect.h"
#include "servo_driver.h"

// Filtrering
double alpha = 0.2;
double measuredSpeed = 0;

// Koefficienter
double kp = 0.001;
double ki = 0.0514;
double kd = -1.4946;
double K1;
double K2;
double K3;

// Vægtning af koefficienter
double setpointWeight = 0.2;
double lowpassSpeed;
double setpointSpeed;

// Diverse
double output;
double throttleopen = 1.0;
float throttlePos;

int rpmch;
int MAX_RPM = 9000;

// Initialiering
double lastSetpointSpeed = 0;
double lastMeasuredSpeed = 0;
double lastLowpassSpeed = 0;
double lastOutput = 0;
double lastLastMeasuredSpeed = 0;

void velPID(int setpointSpeed, int measuredSpeed) {
	lowpassSpeed = alpha * lastLowpassSpeed + (1 - alpha) * measuredSpeed;
	K1 = kp * setpointWeight * (setpointSpeed - lastSetpointSpeed)
			+ kp * (lastMeasuredSpeed - lowpassSpeed);
	K2 = ki * (setpointSpeed - lowpassSpeed);
	K3 = kd * (2 * lastMeasuredSpeed - lowpassSpeed - lastLastMeasuredSpeed);
	output = lastOutput - K1 - K2 - K3;
	if (output < 0) {
		output = 0;
	}
	throttlePos = output / MAX_RPM;
	lastLowpassSpeed = lowpassSpeed;
	lastLastMeasuredSpeed = lastMeasuredSpeed;
	lastMeasuredSpeed = lowpassSpeed;
	lastSetpointSpeed = setpointSpeed;
	lastOutput = output;
	angle_throttle(throttlePos);
}

int main(void) {
	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
	/* Init FSL debug console. */
	BOARD_InitDebugConsole();
	// init_read_rpm();
	rpmch = 7000;
	init_read_rpm();
	init_pwm();
	while (1) {
		int measure_rpm = get_rpm();
		velPID(5000, measure_rpm); // set rpm to 5000 as setpoint
		}
	return 0;
}
