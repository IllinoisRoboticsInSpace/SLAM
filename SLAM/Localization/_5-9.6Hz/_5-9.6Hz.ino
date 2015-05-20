/******
Description: Generates frequencies from 5-10KHz in sync with the stepper motor step
Input: None
Output: 5-10KHz with a slight delay to synchronize with stepper motor
******/

#include <TimerOne.h>

void setup() {
pinMode(10, OUTPUT);
Timer1.initialize(500);
Timer1.pwm(9,512);
Timer1.attachInterrupt(callback);
}
void callback()
{
  digitalWrite(10,digitalRead(10)^1);
}
double t = 5;
bool flag=false; //flag allow change between increment and decrement

void loop() { 
if(flag==false)
{
Timer1.setPeriod(500/t); // f = 1kHz //increment t to change period to allow different frequency generation
t = t+0.01;
delay(10);
if(t>=9.6)
{
    flag=true;
}
}
if(flag==true)
{
Timer1.setPeriod(500/t); // f = 1kHz //decrement t to change period to allow different frequency generation
delay(10);
if(t<=5)
{
    flag=false;
}
}
}
