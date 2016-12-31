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
	int iImageWidth=640; // Width of the  displayed video
	int iImageHeight=480;// Same Height;
	int QWidth=40;       // These next two are about where, on screen, to draw the window. 
	int QHeight=50;
	int iButtonPad=30;   // Space between buttons (make it larger than iButtonHeight!)
	int iButtonHeight = 25;
	int iButtonWidth = 100;
        
	//create the app
	QApplication a( argc, argv );
	
	QWidget *myWidget = new QWidget;
	myWidget->setGeometry(QWidth, QHeight, iImageWidth+iButtonPad/2, iImageHeight+4*iButtonHeight+2*iButtonPad);

	//create an image placeholder for myLabel
	//fill the top left corner with red, just bcuz
	QImage myImage;
	myImage = QImage(iImageWidth, iImageHeight, QImage::Format_RGB888);
	QRgb red = qRgb(255,0,0);
	for(int i=0;i<80;i++) {
		for(int j=0;j<60;j++) {
			myImage.setPixel(i, j, red);
		}
	}

	//create a label, and set it's image to the placeholder
	MyLabel myLabel(myWidget);
	myLabel.setGeometry(10, 10, iImageWidth, iImageHeight);
	myLabel.setPixmap(QPixmap::fromImage(myImage));

	//create a FFC button
	QPushButton *button1 = new QPushButton("Run FFC", myWidget);
	button1->setGeometry(iButtonPad, iImageHeight+iButtonPad, iButtonWidth, iButtonHeight);

	//create a Record button
	QPushButton *button2 = new QPushButton("Record", myWidget);
	button2->setGeometry(iImageWidth-iButtonWidth-iButtonPad, iImageHeight+iButtonPad, iButtonWidth, iButtonHeight);

///////

	//create UpLeft button
	//QPushButton *button3 = new QPushButton("UpLeft", myWidget);
	//button3->setGeometry(iButtonPad, iImageHeight+2*iButtonPad, iButtonWidth, iButtonHeight);

	//create Up button
	QPushButton *button4 = new QPushButton("Up", myWidget);
	button4->setGeometry((iImageWidth-iButtonWidth)/2, iImageHeight+2*iButtonPad, iButtonWidth, iButtonHeight);

	//create UpRight button
	//QPushButton *button5 = new QPushButton("UpRight", myWidget);
	//button5->setGeometry(iImageWidth-iButtonWidth-2*iButtonPad, iImageHeight+2*iButtonPad, iButtonWidth, iButtonHeight);

///////

	//create Left button
	QPushButton *button6 = new QPushButton("Left", myWidget);
	button6->setGeometry(3*iButtonPad, iImageHeight+3*iButtonPad, iButtonWidth, iButtonHeight);

	//create stop button
	QPushButton *button7 = new QPushButton("STOP", myWidget);
	button7->setGeometry((iImageWidth-iButtonWidth)/2, iImageHeight+3*iButtonPad, iButtonWidth, iButtonHeight);

	//create Right button
	QPushButton *button8 = new QPushButton("Right", myWidget);
	button8->setGeometry(iImageWidth-iButtonWidth-3*iButtonPad, iImageHeight+3*iButtonPad, iButtonWidth, iButtonHeight);

///////

	//create Down Left button
	//QPushButton *button9 = new QPushButton("Down Left", myWidget);
	//button9->setGeometry(2*iButtonPad, iImageHeight+4*iButtonPad, iButtonWidth, iButtonHeight);

	//create  Down button
	QPushButton *button10 = new QPushButton("Down", myWidget);
	button10->setGeometry((iImageWidth-iButtonWidth)/2, iImageHeight+4*iButtonPad, iButtonWidth, iButtonHeight);

	//create Down Right button
	//QPushButton *button11 = new QPushButton("DownRight", myWidget);
	//button11->setGeometry(iImageWidth-iButtonWidth-2*iButtonPad, iImageHeight+4*iButtonPad, iButtonWidth, iButtonHeight);

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

