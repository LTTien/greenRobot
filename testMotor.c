#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_3,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_4,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_5,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_6,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port3,           shooterLeft,   tmotorVex393HighSpeed, openLoop, encoder, encoderPort, I2C_1, 1000)
#pragma config(Motor,  port4,           driveFrontLeft, tmotorVex393HighSpeed, openLoop, encoder, encoderPort, I2C_2, 1000)
#pragma config(Motor,  port5,           driveFrontRight, tmotorVex393HighSpeed, openLoop, encoder, encoderPort, I2C_5, 1000)
#pragma config(Motor,  port6,           driveRearLeft, tmotorVex393HighSpeed, openLoop, encoder, encoderPort, I2C_3, 1000)
#pragma config(Motor,  port7,           driveRearRight, tmotorVex393HighSpeed, openLoop, encoder, encoderPort, I2C_4, 1000)
#pragma config(Motor,  port8,           shooterRight,  tmotorVex393HighSpeed, openLoop, encoder, encoderPort, I2C_6, 1000)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()	{
	while (true)	{
		//SensorValue[I2C_1] = 0;
		//SensorValue[I2C_1] = 0;
		//motor[shooterLeft] = 100;
	 //	motor[shooterRight] = 100;


		motor[driveFrontRight] = 100;
		motor[driveRearRight] = 100;
		motor[driveFrontLeft] = 100;
		motor[driveRearLeft] = 100;
		wait1Msec(10);
		}	// end while statement
}	//end program