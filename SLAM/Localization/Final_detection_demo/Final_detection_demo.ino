/*******

Description: Function to detect frequency and produce x,y
Inputs: 1-5KHz and 5-9.6KHz generators to determine angle between 0 to 180 degrees respectively
Output: x,y

********/

#include <FreqPeriodCounter.h>
#include <Albert.h>
#include <TimerOne.h> 
#include <StopWatch.h>
#include <math.h>
 
const byte counterPin = 3; // connect pin 3 to pin 9
const byte counterInterrupt = 1; // = pin 3
double a,b,c,d,x,y,f,g,h,l,temp,temp2; //temporary variables 
StopWatch Stop; 

FreqPeriodCounter counter(counterPin, micros); //library that detects frequency
 
void setup(void) 
{
Serial.begin(9600); 
attachInterrupt(counterInterrupt, counterISR, CHANGE); //interrupt whenever a change from 1->0 or 0->1 occurs
pinMode(3, INPUT);
} 
void loop ()
{
x = interrupt1(); //function calling
delay(10);
y = interrupt2(); //function calling
if(x && y) //condition only if both angles are received, else wait
{
f = (145 * tan(x * 3.14159265359/180))/(tan(x* 3.14159265359/180) + tan((180-y)* 3.14159265359/180));
g = f * tan( y* 3.14159265359/180);
Serial.println("x = ");
Serial.println(f);
Serial.println("y = ");
Serial.println(g);
/* Use the above trig formulas where (0,0) is at the outermost laser (if sweeping clockwise then left laser is (0,0))*/
}
x = 0;
y = 0; //reset both to 0 so that new values are recorded
}
double interrupt1() 
{  
  a = counter.hertz(); //gets the frequency from photodiode
  if(counter.ready() && (a > 1000 && a < 5000))
  {
  temp = (a - 1000)/20; //maps frequency to angle 0 to 180
  //Serial.println("angle1 = ");
  //Serial.println(temp); //uncomment only to debug when measuring angles generated 
  } 
  return temp;
}
double interrupt2() 
{
  b = counter.hertz(); //same as above
  if(counter.ready() && (b > 5000 && b < 10000)) //different range of frequency
  {
  temp2 = (b - 5000)/20;
  Serial.println("angle2 = ");
  Serial.println(temp2);   
  return temp2;
  }
}
void counterISR()
{ 
  counter.poll();
}

