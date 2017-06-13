#include "drive-arm.h"

/* ----------------------------------------------------------- */


//
// Initializes Bone for io and set which pins we will use.
// This is where we choose which motor to drive.
// 

DriveArm::DriveArm() {
        iolib_init();
};

DriveArm::~DriveArm() {
        iolib_free();
};

void DriveArm::setMyArm(int myarm) {
	printf("DriveArm::setMyArm\n");
	DriveArm::iMyArm = myarm;

        BBBIO_sys_Enable_GPIO(BBBIO_GPIO2);

        if (getMyArm()) {
	    pin_high(P8,XPWR);
            iolib_setdir(P8,XPWR, BBBIO_DIR_OUT); // EHRPWM2A  Pin to use for speed control
            iolib_setdir(P8,XPIN1, BBBIO_DIR_OUT); // GPIO_45  in1 on H-Bridge
            iolib_setdir(P8,XPIN2, BBBIO_DIR_OUT); // GPIO_47   in2 on H-Bridge
        } else {
	    pin_high(P8,YPWR);
            iolib_setdir(P8,YPWR, BBBIO_DIR_OUT); // EHRPWM2B  Pin to use for speed control
            iolib_setdir(P8,YPIN1, BBBIO_DIR_OUT); // GPIO_66  in3 on H-Bridge 
            iolib_setdir(P8,YPIN2, BBBIO_DIR_OUT); // GPIO_67  in4 on H-Bridge
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
        if (getMyArm() == XAXIS) { // Activate X Axis arm
		if (isClockwise) {
		 	printf("X Axis Clockwise\n");
			pin_high(P8,XPIN2);
			printf("pin P8-XPIN2 high\n");
			pin_low(P8,XPIN1);
			printf("pin P8-XPIN1 low\n");
	   	
		} else {
			printf("X Axis Counter Clockwise\n");
			pin_low(P8,XPIN2);
			printf("pin P8-XPIN2 low\n");
			pin_high(P8,XPIN1);
			printf("pin P8-XPIN1 high\n");
		}
	} else { // YAXIS so activate the Y Axis arm 
		if (isClockwise) {
		 	printf("Y Axis Clockwise\n");
			pin_high(P8,YPIN2);
			printf("pin P8-YPIN2 high\n");
			pin_low(P8,YPIN1);
			printf("pin P8-YPIN1 low\n");
	   	
		} else {
			printf("Y Axis Counter Clockwise\n");
			pin_low(P8,YPIN2);
			printf("pin P8-YPIN2 low\n");
			pin_high(P8,YPIN1);
			printf("pin P8-YPIN1 high\n");
		}
	}

	emit;
};


void  DriveArm::runStop(void) {
	printf("DriveArm:runStop\n");
	pin_low(P8,XPWR);
	pin_low(P8,XPIN1);
	pin_low(P8,XPIN1);
	pin_low(P8,YPWR);
	pin_low(P8,YPIN1);
	pin_low(P8,YPIN1);
};


