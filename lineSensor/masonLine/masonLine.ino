uint16_t sensor[8];  //Array for Sensor Values
uint32_t sumValues = 0;  //Sum of the Sensor Values
uint8_t color = 0;  //Will be used as a Color flag for black or white lines. Not Implemented
uint32_t valueOut = 0;  //Output value for Analog Output

// Storage for the vex communications data

void setup()
{
Serial.begin(9600);  //Initialize the Serial Output
pinMode(3, OUTPUT);  //Define Pin3 as low impedance suitable for analog Output
TCCR2A = 0b10100011;  //Setup Fast PWM on timer 2 to run at 56KHz
TCCR2B = 0b00000001;
OCR2B = 128;          //Set Pin3 to run at 50% duty cycle since 8bit.
}
 
void loop()
{
sensor[0] = analogRead(A0);  //Read in analog Values
sensor[1] = analogRead(A1);
sensor[2] = analogRead(A2);
sensor[3] = analogRead(A3);
sensor[4] = analogRead(A4);
sensor[5] = analogRead(A5);
sensor[6] = analogRead(A6);
sensor[7] = analogRead(A7);

//INVERTED SENSORS flipped from x,y y,x
for(int i = 0; i < 8; i++) {
sensor[i] = map(constrain(sensor[i],40, 750), 40, 750, 255, 0);      // input, output. CRUDE calibration mechanism. 
} 

//clearing the values
valueOut = 0;  
sumValues = 0; 


//telling me where the location it is at
for(int i = 0; i < 8; i++) //Loop through each of the Sensors
{ 
 valueOut += sensor[i]*36*(i);  //Weight the Sensor Values *
 sumValues += sensor[i];         //Calculate the Sum of the Sensor Values
 // valueOut -= 400;
}

//if all of them dont see a line then we throw it away
/*
if(sumValues <= 80)  //This is the cut to throw away data if no line is detected.
{
	valueOut = 0;
}*/

valueOut /= sumValues;  //Calculate the weighted average
valueOut = constrain(valueOut, 0,255);
Serial.println(valueOut);  //For debugging

/*for(int i=0; i<8; i++)
{
  Serial.print(sensor[i]);
  Serial.print('\t');
}
Serial.print('\n');
*/

OCR2B = valueOut;
delayMicroseconds(100); //100     //Wait a bit so things can settle

}
