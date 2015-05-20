/******
Description: Pins 10 and 3 control the two stepper motors 
Inputs: None
Outputs: Speed - 3, Direction - 10
Note: For 360 degree turning, change the value in the main loop from .00020 to .00010

******/
#include <TimerOne.h>
#include <TimerThree.h>


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(10,OUTPUT);
pinMode(3,OUTPUT);
Timer1.initialize(500);
Timer3.initialize(500);
Timer1.pwm(10,512);
Timer3.pwm(3,512);
Timer1.attachInterrupt(callback);
Timer3.attachInterrupt(callback2);
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
Timer1.setPeriod(500/.00020);
Timer3.setPeriod(500/.17);
}
