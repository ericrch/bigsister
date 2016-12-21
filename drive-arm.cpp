
#include <stdio.h>
#include <stdlib.h>
#include "../../BBBio_lib/BBBiolib.h"
/* ----------------------------------------------------------- */
int main(void)
{

	iolib_init();
	int delay = 5; // delay in milliseconds... how long to wait for bus, CPU, etc...

 	BBBIO_sys_Enable_GPIO(BBBIO_GPIO2);

	iolib_setdir(8,19, BBBIO_DIR_OUT); // EHRPWM2A  Pin to use for speed control
	iolib_setdir(8,13, BBBIO_DIR_OUT); // EHRPWM2B  in1 
	iolib_setdir(8,15, BBBIO_DIR_OUT); // GPIO_47   in2

        const float PWM_HZ = 100.0f ;   /* 100 Hz */
        const float duty_A = 00.0f ;    /* 20% Duty cycle for PWM 0_A output */
        const float duty_B = 75.0f ;    /* 50% Duty cycle for PWM 0_B output*/

	int isClockwise = 1;         // Rotation direction 0 == counter clockwise

	pin_high(8,19);

	if (isClockwise) {
		printf("Clockwise\n");
		pin_high(8,15);
		pin_low(8,13);
	   	
	} else {
		printf("Counter Clockwise\n");
		pin_low(8,15);
		pin_high(8,13);
	}

	iolib_delay_ms(delay);
	if(BBBIO_PWMSS_Setting(BBBIO_PWMSS2 , PWM_HZ, duty_B, duty_B)){
		printf("ERCH PWMSS is Set\n");
	} else {
		printf("ERCH PWMSS FAILED!!!!\n");
	};

	iolib_delay_ms(delay);
	BBBIO_ehrPWM_Enable(BBBIO_PWMSS2);
		printf("110\n");

	sleep(3);

	pin_low(8,19);
	pin_low(8,13);
	pin_low(8,13);

        BBBIO_ehrPWM_Disable(BBBIO_PWMSS2);
	iolib_free();
	return(0);
}


