/******
Description: Generates frequencies from 1-5KHz in sync with the stepper motor step
Input: None
Output: 1-5KHz with a slight delay to synchronize with stepper motor
******/

#include <TimerOne.h>

void setup() {
pinMode(10, OUTPUT);
Timer1.initialize(500);
Timer1.pwm(9,512);
Timer1.attachInterrupt(callback); //attach callback
}
void callback()
{
  digitalWrite(10,digitalRead(10)^1);
}
double t = 1;
bool flag=false; //flag allow change between increment and decrement

void loop() { 
if(flag==false)
{
Timer1.setPeriod(500/t); // f = 1kHz //increment t to change period to allow different frequency generation
t = t+0.01;
delay(10);
if(t>=4.6)
{
    flag=true;
}
}
if(flag==true)
{
Timer1.setPeriod(500/t); // f = 1kHz
t = t-0.01; //decrement t to change period to allow different frequency generation
delay(10);
if(t<=1 )
{
    flag=false;
}
}
}

