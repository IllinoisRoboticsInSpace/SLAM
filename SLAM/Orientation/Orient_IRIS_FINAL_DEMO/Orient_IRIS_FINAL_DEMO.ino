/*****
Description: Step the motor and detect if frequency is between 7900 and 8100 to record angle
Inputs: 7900 < Frequency < 8100
Outputs: Angle - Theta for direction
*****/

#include <TimerOne.h>
#include <TimerThree.h>
#include <FreqPeriodCounter.h>
const byte counterPin = 3; // connect pin 3 to pin 9
const byte counterInterrupt = 1; // = pin 3
//double buffer[n];

FreqPeriodCounter counter(counterPin, micros);
double Steps = 0,Orient = 0,val = 0;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(10,OUTPUT);
pinMode(5,OUTPUT);
Timer1.initialize(500);
Timer3.initialize(500);
Timer1.pwm(10,512);
Timer3.pwm(5,512);
Timer1.attachInterrupt(callback);
Timer3.attachInterrupt(callback2);
attachInterrupt(counterInterrupt, counterISR, CHANGE);
pinMode(3, INPUT);
}
void callback()
{
 digitalWrite(10,digitalRead(10)^1); 
}
void callback2()
{
 digitalWrite(11,digitalRead(10)^1); 
}
void loop() 
{
  // put your main code here, to run repeatedly:
Timer1.setPeriod(500/.000085); //direction of stepper
Timer3.setPeriod(500/.14); //speed of stepper; larger value for speed, smaller for direction 
Steps=Steps+1; //increment steps of stepper
if(Steps == 3600) //reset upon 360 degrees 
{
  Steps = 0;
}
val = counter.hertz(); //read in frequency
//Serial.println(val);
if (val > 7900 && val < 8100) // Read in 1 from RF receiver
 {
    Orient = Steps/10 - (Steps/10 - (Steps - 5)/10); //subtract 5 steps due to lag
    Serial.println(Orient); //Angle for direction
    //Serial.write(Orient, 4);
 }
}
/* Function to poll the interrupt service routine*/
void counterISR()
{ 
  counter.poll();
}

