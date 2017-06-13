#ifndef DRIVE_ARM_H
#define DRIVE_ARM_H
#include "../BBBIOlib/BBBio_lib/BBBiolib.h"
#include <QtCore>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define LEFT 0
#define RIGHT 1
#define XAXIS 1
#define YAXIS 0

#define P8 8

#define XPWR 19   // Indigo
#define XPIN2 17  // Blue	
#define XPIN1 15  // Green
#define YPWR  13  // Red
#define YPIN1 9   // Orange
#define YPIN2 11  // Yellow


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
    static const int delay = 150; // delay in milliseconds... how long to wait for bus, CPU, etc... 
    static const float PWM_HZ = 50.0f;    /* Hz */
    static const float duty_A = 80.0f;    /* % Duty cycle for PWM 0_A output */
    static const float duty_B = 80.0f;    /* % Duty cycle for PWM 0_B output*/

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
