#pragma config(Sensor, in1,    lineSensor,     sensorLineFollower)
#pragma config(Sensor, I2C_1,  LE,             sensorNone)
#pragma config(Sensor, I2C_2,  RE,             sensorNone)
#pragma config(Motor,  port4,           driveFrontLeft, tmotorVex393HighSpeed, openLoop)
#pragma config(Motor,  port5,           driveFrontRight, tmotorVex393HighSpeed, openLoop)
#pragma config(Motor,  port6,           driveRearLeft, tmotorVex393HighSpeed, openLoop)
#pragma config(Motor,  port7,           driveRearRight, tmotorVex393HighSpeed, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
#include "serialCortex.h"

//Pivoting is for the gyro

void pivotClockwise (int goRight)    {
	while(SensorValue[leftEncoder] < goRight)   {
  	motor[driveFrontRight] = -40;	// 5
		motor[driveRearRight] = -40;
		motor[driveFrontLeft] = 40;	// 5
		motor[driveRearLeft] = 40;
    }
}

void pivotCounterClockwise (int goLeft)  {
    while(SensorValue[leftEncoder] < goLeft)    {
		  motor[driveFrontRight] = 40;	// 5
			motor[driveRearRight] = 40;
			motor[driveFrontLeft] = -40;	// 5
			motor[driveRearLeft] = -40;
    }
}

//Turning

void turnClockwise (int goRight)    {
	while(SensorValue[leftEncoder] < goRight)   {
  	motor[driveFrontRight] = 0;	// 5
		motor[driveRearRight] = 0;
		motor[driveFrontLeft] = 40;	// 5
		motor[driveRearLeft] = 40;
    }
}

void turnCounterClockwise (int goLeft)  {
    while(SensorValue[leftEncoder] < goLeft)    {
		  motor[driveFrontRight] = 40;	// 5
			motor[driveRearRight] = 40;
			motor[driveFrontLeft] = 0;	// 5
			motor[driveRearLeft] = 0;
    }
}

void goForward (int goCount)    {
    while(SensorValue[leftEncoder] < goCount)   {       //goCount is 1 block
		  motor[driveFrontRight] = 56;	// 5
			motor[driveRearRight] = 56;
			motor[driveFrontLeft] = 102;	// 5
			motor[driveRearLeft] = 102;
        }  // end while(SensorValue(TouchSensor) == 1)
    }

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

// task autonomous()	{
task main()	{
	StartTask(serialRxTask);
	while(true)        {
		if(SensorValue(lineSensor) > 128) {           	 // 128 to 255 is left side
		turnCounterClockwise(15);
            }
	else if (SensorValue(lineSensor) < 127) {           // 0 to 127 is the right side.
		turnClockwise(15);
		}
	else    {               // BREAK
    motor[RIGHT] = 0;
    motor[LEFT] = 0;
        }   // end else statement
    }   // end  while(true)
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

// task userControl()	{
task main()	{
	StartTask(serialRxTask);
	while (true)	{
		motor[driveFrontRight] = 40;
		motor[driveRearRight] = 50;
		motor[driveFrontLeft] = 40;
		motor[driveRearLeft] = 50;
		}	// end while statement
}	//end program

	/*
	int X2 = 0, Y1 = 0, X1 = 0,Y2 = 0, threshold = 15;

	// If value is in deadzone set to zero else set to channel value.
	if(abs(vexRT[Ch3]) > threshold) // up down
		Y1 = vexRT[Ch3];
	else
		Y1 = 0;
	if(abs(vexRT[Ch4]) > threshold) // left right 1
		X1 = vexRT[Ch4];
	else
		X1 = 0;
	if(abs(vexRT[Ch1]) > threshold)  //left righbgt 2
		X2 = vexRT[Ch1];
	else
		X2 = 0;
	if(abs(vexRT[Ch2])>threshold)
		Y2 = vexRT[Ch2];
	else
		Y2 = 0;
	motor[driveFrontRight] = Y1 + X2 + X1;	// 5
	motor[driveRearRight] =  Y1 - X2 - X1; // 7
	motor[driveFrontLeft] = Y1 + X2 - X1;	// 4
	motor[driveRearLeft] =  Y1 - X2 + X1;	// 6

	*/






/*
	if(vexRT[Btn5U] == 1)
		motor[magazine] = 50;
	else if(vexRT[Btn5D] == 1)
		motor[magazine] = -50;
	else
		motor[magazine] = 0;
*/
	//if(vexRT[Btn6U] == 1)
	//	motor[intake] = 100;
	//else if(vexRT[Btn6D] == 1)
	//	motor[intake] = -100;
	//else
	//	motor[intake] = 0;
	/*motor[intake] = 100; */

/*{

//}
/*
task main(){ 		/// SHOOTER
	int shooterSpeed = 80;
	int shooterSpeedPrevious = 80;
	shooterStartSoft( shooterSpeed );
	while(true){
	  userDrive( );
	  if( vexRT[Btn7U] == 1 ){
	  	shooterSpeedPrevious = shooterSpeed;
	  	shooterSpeed = shooterSpeed + 2;
	  	shooterAdjust( shooterSpeedPrevious, shooterSpeed );
	  }
	  if( vexRT[Btn7D] == 1 ){
	  	shooterSpeedPrevious = shooterSpeed;
	  	shooterSpeed = shooterSpeed - 2;
	  	shooterAdjust( shooterSpeedPrevious, shooterSpeed );
	  }
	  wait1Msec(20);
	}
}*/
