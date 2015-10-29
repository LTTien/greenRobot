uint32_t sensor[8];  //Array for Sensor Values
uint32_t sumValues = 0;  //Sum of the Sensor Values
uint32_t color = 0;  //Will be used as a Color flag for black or white lines. Not Implemented
uint32_t valueOut = 0;  //Output value for Analog Output
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
 
valueOut = 0;  //Initialize the variables to calculate the weighted average
sumValues = 0;
for(int i = 0; i < 8; i++) //Loop through each of the Sensors
{
valueOut += sensor[i]*128*(i);  //Weight the Sensor Values
sumValues += sensor[i];         //Calculate the Sum of the Sensor Values
}
if(sumValues <= 400)  //This is the cut to throw away data if no line is detected.
{
valueOut = 0;
}
valueOut /= sumValues;  //Calculate the weighted average
//Serial.println(valueOut);  //For debugging
OCR2B = (valueOut/4)%256;    //Generate the Analog Output on Pin 3
delayMicroseconds(100);      //Wait a bit so things can settle
}

