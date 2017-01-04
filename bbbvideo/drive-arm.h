#ifndef DRIVE_ARM_H
#define DRIVE_ARM_H
#include <QtCore>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../BBBIOlib/BBBio_lib/BBBiolib.h"

#define LEFT 0
#define RIGHT 1
#define XAXIS 1
#define YAXIS 0

#define P8 8

#define XPWR 19
#define XPIN1 11
#define XPIN2 15
#define YPWR 13
#define YPIN1 7
#define YPIN2 8


//
// Create the drive_arm class
//
using namespace std;
class DriveArm : public QObject {

Q_OBJECT;

  public:
    DriveArm();
    ~DriveArm();

    int getMyArm () {return iMyArm;};
    void setMyArm (int myarm);

  private:
    int iMyArm;
    static const int delay = 5; // delay in milliseconds... how long to wait for bus, CPU, etc... 
    static const float PWM_HZ = 100.0f;   /* 100 Hz */
    static const float duty_A = 00.0f;    /* 20% Duty cycle for PWM 0_A output */
    static const float duty_B = 80.0f;    /* 50% Duty cycle for PWM 0_B output*/

    void runArm(int isClockwise);


  public slots:
    void runXClockwise();
    void runXCounterClockwise();
    void runYClockwise();
    void runYCounterClockwise();
    void runStop();

  signals:
    void doStuff(); 
};

#endif
