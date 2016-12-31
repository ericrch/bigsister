#include <QApplication>
#include <QThread>
#include <QMutex>
#include <QMessageBox>

#include <QColor>
#include <QLabel>
#include <QtDebug>
#include <QString>
#include <QPushButton>

#include "LeptonThread.h"
#include "MyLabel.h"
#include "drive-arm.h"

int main( int argc, char **argv )
{
	int wWidth=640; //320;
	int wHeight=480;// 240;
	int QWidth=800;//400;
	int QHeight=600;//300;
	int wPad=25;

        
	//create the app
	QApplication a( argc, argv );
	
	QWidget *myWidget = new QWidget;
	myWidget->setGeometry(QWidth, QHeight, wWidth+20, wHeight+50);

	//create an image placeholder for myLabel
	//fill the top left corner with red, just bcuz
	QImage myImage;
	myImage = QImage(wWidth, wHeight, QImage::Format_RGB888);
	QRgb red = qRgb(255,0,0);
	for(int i=0;i<80;i++) {
		for(int j=0;j<60;j++) {
			myImage.setPixel(i, j, red);
		}
	}

	//create a label, and set it's image to the placeholder
	MyLabel myLabel(myWidget);
	myLabel.setGeometry(10, 10, wWidth, wHeight);
	myLabel.setPixmap(QPixmap::fromImage(myImage));

	//create a FFC button
	QPushButton *button1 = new QPushButton("Run FFC", myWidget);
	button1->setGeometry(20, wHeight+wPad, 100, 20);

	//create a Record button
	QPushButton *button2 = new QPushButton("Record", myWidget);
	button2->setGeometry(200, wHeight+wPad, 100, 20);

///////

	//create UpLeft button
	QPushButton *button3 = new QPushButton("UpLeft", myWidget);
	button3->setGeometry(20, wHeight+2*wPad, 100, 20);

	//create Up button
	QPushButton *button4 = new QPushButton("Up", myWidget);
	button4->setGeometry(200, wHeight+2*wPad, 100, 20);

	//create UpRight button
	QPushButton *button5 = new QPushButton("UpRight", myWidget);
	button5->setGeometry(380, wHeight+2*wPad, 100, 20);

///////

	//create Left button
	QPushButton *button6 = new QPushButton("Left", myWidget);
	button6->setGeometry(20, wHeight+3*wPad, 100, 20);

	//create stop button
	QPushButton *button7 = new QPushButton("stop", myWidget);
	button7->setGeometry(200, wHeight+3*wPad, 100, 20);

	//create Right button
	QPushButton *button8 = new QPushButton("Right", myWidget);
	button8->setGeometry(380, wHeight+3*wPad, 100, 20);

///////

	//create Down Left button
	QPushButton *button9 = new QPushButton("Down Left", myWidget);
	button9->setGeometry(20, wHeight+4*wPad, 100, 20);

	//create  Down button
	QPushButton *button10 = new QPushButton("Down", myWidget);
	button10->setGeometry(200, wHeight+4*wPad, 100, 20);

	//create Down Right button
	QPushButton *button11 = new QPushButton("DownRight", myWidget);
	button11->setGeometry(380, wHeight+4*wPad, 100, 20);

///////
	// Create a robot arm
	DriveArm *myArm = new DriveArm();

	//create a thread to gather SPI data
	//when the thread emits updateImage, the label should update its image accordingly
	LeptonThread *thread = new LeptonThread();
	QObject::connect(thread, SIGNAL(updateImage(QImage)), &myLabel, SLOT(setImage(QImage)));
	
	//connect ffc button to the thread's ffc action
	QObject::connect(button1, SIGNAL(clicked()), thread, SLOT(performFFC()));
	thread->start();
	
	//connect record button to   global in the thread ...
	QObject::connect(button2, SIGNAL(clicked()), thread, SLOT(startRecording()));
	thread->start();
	
        //  Drive up...
	QObject::connect(button4, SIGNAL(clicked()), myArm, SLOT(runYClockwise()));
	thread->start();

        //  Drive left...
	QObject::connect(button6, SIGNAL(clicked()), myArm, SLOT(runXClockwise()));
	thread->start();
	
	//  Stop motor 
	QObject::connect(button7, SIGNAL(clicked()), myArm, SLOT(runStop()));
	thread->start();
	
	// Drive right...
	QObject::connect(button8, SIGNAL(clicked()), myArm, SLOT(runXCounterClockwise()));
	thread->start();
	
	// Drive down...
	QObject::connect(button10, SIGNAL(clicked()), myArm, SLOT(runYCounterClockwise()));
	thread->start();
	
	myWidget->show();

	return a.exec();
}

