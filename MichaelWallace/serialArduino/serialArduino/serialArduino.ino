/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*                        Copyright (c) James Pearman                          */
/*                                   2013                                      */
/*                            All Rights Reserved                              */
/*                                                                             */
/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*        Module:     serialArduino.c                                          */
/*        Author:     James Pearman                                            */
/*        Created:    5 August 2013                                            */
/*                                                                             */
/*        Revisions:  V0.1                                                     */
/*                                                                             */
/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*    Description:                                                             */
/*                                                                             */
/*    Demonstration code for serial comms transmition from Arduino to          */
/*    VEX cortex.                                                              */
/*                                                                             */
/*    Licensed under the Apache License, Version 2.0 (the "License");          */
/*    you may not use this file except in compliance with the License.         */
/*    You may obtain a copy of the License at                                  */
/*                                                                             */
/*    http://www.apache.org/licenses/LICENSE-2.0                               */
/*                                                                             */
/*    Unless required by applicable law or agreed to in writing, software      */
/*    distributed under the License is distributed on an "AS IS" BASIS,        */
/*    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. */
/*    See the License for the specific language governing permissions and      */
/*    limitations under the License.                                           */
/*                                                                             */
/*-----------------------------------------------------------------------------*/


#include <SoftwareSerial.h>
#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050_6Axis_MotionApps20.h>
#include "Gyro.h"

Gyro myGyro;

// Storage for the vex communications data
typedef struct _vdata {
      unsigned char  header_aa;
      unsigned char  header_55;
      unsigned char  message_type;
      unsigned char  datalen;
      int angle;
      int stick_1x;   // right stick 
      int stick_2y;   // right stick
      int stick_3y;   // left stick 
      int stick_4x;   // left stick 
      int button_567; // 
      int button_8etc;  // 
      unsigned char  id;
      unsigned char  checksum;
      } vdata;

#define  VEXDATAOFFSET         4
#define  VEX_DATA_BUFFER_SIZE  sizeof(vdata)
     
typedef union _vexdata { 
      vdata data;  
      unsigned char    buffer[VEX_DATA_BUFFER_SIZE];  
      } vexdata;

vexdata  MyVexDataTx;

/*-----------------------------------------------------------------------------*/
/*  Initialize the software serial port                                        */
/*-----------------------------------------------------------------------------*/

SoftwareSerial mySerial(6, 7); // RX, TX

void
serialInit( long baud )
{
    mySerial.begin( baud );
}

/*-----------------------------------------------------------------------------*/
/*  Transmit one character                                                     */
/*-----------------------------------------------------------------------------*/

void
serialTxChar(unsigned char c)
{
    // software send
     mySerial.write( c );
    
    // hardware send
    //Serial.write( c );  
}

/*-----------------------------------------------------------------------------*/
/*  Arduino setup function                                                     */
/*-----------------------------------------------------------------------------*/

void setup()
{
    // initialize the digital pin 13 as an output.
    pinMode(13, OUTPUT);  
    
    // Initialize the VEX data structures
    VexDataInit( &MyVexDataTx );
 
    // Open the software serial port, luckily it defaults to 8bit, 1 stop, no parity
    // as this is not easily changed
    serialInit(115200);    
        
    // console
    Serial.begin( 115200 );  

    // Do not use any debug print statements as we are using the serial
    // port for the VEX communications

    Serial.print(F("\r\nSerial demo code"));
	myGyro.init();
}


/*-----------------------------------------------------------------------------*/
/*  Arduino main loop                                                          */
/*-----------------------------------------------------------------------------*/

void loop()
{
	myGyro.update();
	
    static  uint32_t  timer = 0;

    // Run every 20mS (50x per second)
    if(millis() - timer < 20)
      return;     
    timer =  millis();
        
    // dummy data - the real variables would be set here
    MyVexDataTx.data.angle = myGyro.getXDegrees();
    MyVexDataTx.data.stick_1x = myGyro.getXDegrees();
    MyVexDataTx.data.stick_2y = 90;
    MyVexDataTx.data.stick_3y = 270;
    MyVexDataTx.data.stick_4x = 180;
    MyVexDataTx.data.button_567 = 4;
    MyVexDataTx.data.button_8etc = 13;    
    // next id
    MyVexDataTx.data.id++;
    
    // Calculate checksum   
    VexDataChecksum( &MyVexDataTx );

    // Transmit data
    VexDataTransmit( &MyVexDataTx );
}

/*-----------------------------------------------------------------------------*/
/*  Initialize the VEX data                                                    */
/*-----------------------------------------------------------------------------*/

void
VexDataInit( union _vexdata *v )
{
    int  i;
    
    // clear all
    for(i=0;i<VEX_DATA_BUFFER_SIZE;i++)
      v->buffer[i] = 0;
    
    // Initialize packet  
    v->data.header_aa    = 0xAA;
    v->data.header_55    = 0x55;
    v->data.message_type = 0x01; // Only one type of message
    v->data.datalen      = 0x10; // 16 bytes of data
    v->data.id           = 0x00;
}

/*-----------------------------------------------------------------------------*/
/*  Calculate the checksum for the VEX data                                    */
/*-----------------------------------------------------------------------------*/

void
VexDataChecksum( union _vexdata  *v )
{
    int  i;
    int  cs = 0;
   
    for(i=0;i<(VEX_DATA_BUFFER_SIZE-1);i++)
      cs += v->buffer[i];
    
    v->data.checksum = 0x100 - (cs & 0xFF);
}

/*-----------------------------------------------------------------------------*/
/*  send the VEX data to the serial port                                       */
/*-----------------------------------------------------------------------------*/

void
VexDataTransmit( union _vexdata  *v )
{
    int  i;
    
    for(i=0;i<VEX_DATA_BUFFER_SIZE;i++)
      serialTxChar( v->buffer[i] );
}

