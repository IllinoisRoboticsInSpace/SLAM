/*******
Description: Collection bin trigger for RF transmission
Inputs: 5KHz
Outputs: 8KHz, then switches back to 5KHz
*******/

#include <TimerOne.h>
#include <FreqPeriodCounter.h>
const byte counterPin = 3; // connect pin 3 to pin 9
const byte counterInterrupt = 1; // = pin 3

double val = 0;
FreqPeriodCounter counter(counterPin, micros);

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(10,OUTPUT);
Timer1.initialize(500);
Timer1.pwm(10,512);
Timer1.attachInterrupt(callback);
attachInterrupt(counterInterrupt, counterISR, CHANGE);
pinMode(3, INPUT);
}
void callback()
{
 digitalWrite(10,digitalRead(10)^1); 
}
void loop() {
  // put your main code here, to run repeatedly:

Timer1.setPeriod(500/5); //always generates 5KHz to RF receiver to cancel noise
val = counter.hertz(); //Read frequency in
Serial.println(val);
if (val >4900 && val < 5100) // Check range 
{
        Timer1.setPeriod(500/8); //Alter the period of timer = 8KHz
        //delayMicroseconds(10);
         // Serial.println("Reached 1");
          
}
else if (val < 4900 || val > 5100) //Otherwise reset back to 5KHz
{
  //Serial.println("Reached 2");
Timer1.setPeriod(500/5);
}
val = 0;
}
void counterISR()
{ 
  counter.poll();
}

