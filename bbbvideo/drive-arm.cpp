#include "drive-arm.h"
#include "../BBBIOlib/BBBio_lib/BBBiolib.h"

/* ----------------------------------------------------------- */


//
// Initializes Bone for io and set which pins we will use.
// This is where we choose which motor to drive.
// 

DriveArm::DriveArm() {}
DriveArm::~DriveArm() {}

void DriveArm::setMyArm(int myarm) {
	printf("DriveArm::setMyArm\n");
	DriveArm::iMyArm = myarm;
	printf("DriveArm::iMyArm\n");

	iolib_init();
	printf("iolib_init\n");
        BBBIO_sys_Enable_GPIO(BBBIO_GPIO2);
	printf("BBBIO sys Enable GPIO\n");

        if (getMyArm()) {
	    pin_high(8,19);
	printf("A 10\n");
            iolib_setdir(8,19, BBBIO_DIR_OUT); // EHRPWM2A  Pin to use for speed control
	printf("A 20\n");
            iolib_setdir(8,13, BBBIO_DIR_OUT); // EHRPWM2B  in1
	printf("A 30\n");
            iolib_setdir(8,15, BBBIO_DIR_OUT); // GPIO_47   in2
	printf("A 40\n");
        } else {
	    pin_high(8,19);
	printf("B 10\n");
            iolib_setdir(8,19, BBBIO_DIR_OUT); // EHRPWM2A  Pin to use for speed control
	printf("B 20\n");
            iolib_setdir(8,13, BBBIO_DIR_OUT); // EHRPWM2B  in1 
	printf("B 30\n");
            iolib_setdir(8,15, BBBIO_DIR_OUT); // GPIO_47   in2
	printf("B 40\n");
        }
};

void  DriveArm::runXClockwise() {
	printf("Run X Clockwise\n");
	setMyArm(XAXIS);
	runArm (RIGHT);
};

void  DriveArm::runXCounterClockwise() {
	printf("Run X Counter Clockwise\n");
	setMyArm(XAXIS);
	runArm (LEFT);
};

void  DriveArm::runYClockwise() {
	printf("Run Y Clockwise\n");
	setMyArm(YAXIS);
	runArm (RIGHT);
};

void  DriveArm::runYCounterClockwise() {
	printf("Run Y Counter Clockwise\n");
	setMyArm(YAXIS);
	runArm (LEFT);
};

void  DriveArm::runArm(int isClockwise) {
	if (isClockwise) {
		printf("Clockwise\n");
		pin_high(8,15);
		printf("pin 8-15\n");
		pin_low(8,13);
		printf("pin 8-13\n");
	   	
	} else {
		printf("Counter Clockwise\n");
		pin_low(8,15);
		pin_high(8,13);
	}

	iolib_delay_ms(delay);
	printf("PWMSS setting..PWMSS setting....\n");
	if(BBBIO_PWMSS_Setting(BBBIO_PWMSS2 , PWM_HZ, duty_B, duty_B)){
		printf("ERCH PWMSS is Set\n");
	} else {
		printf("ERCH PWMSS FAILED!!!!\n");
	};

	iolib_delay_ms(delay);
	BBBIO_ehrPWM_Enable(BBBIO_PWMSS2);
		printf("110\n");
	emit ;
};


void  DriveArm::runStop(void) {
	pin_low(8,19);
	pin_low(8,13);
	pin_low(8,13);

        BBBIO_ehrPWM_Disable(BBBIO_PWMSS2);
	iolib_free();
};


