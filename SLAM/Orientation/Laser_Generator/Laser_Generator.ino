/******
Description: Generates 5KHz through laser
Inputs: None
Outputs: 5KHz
******/

#include <TimerOne.h>

void setup() 
{
Serial.begin(9600);
pinMode(10,OUTPUT);
Timer1.initialize(500);
Timer1.pwm(9,512);
Timer1.attachInterrupt(callback);
}

void callback()
{
 digitalWrite(10,digitalRead(10)^1); 
}

void loop() 
{
Timer1.setPeriod(500/5.23); //Adjust accordingly to get 5KHz precisely
}

