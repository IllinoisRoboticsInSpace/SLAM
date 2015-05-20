/******
Description: Generates frequencies from 1-5KHz and 5-10KHz in sync with the stepper motor step
Input: None
Output: 1-5KHz and 5-10KHz with a slight delay to synchronize with stepper motor
******/

#include <arduino.h>
#include "TimerOne.h"
#include "TimerThree.h"
#include "TimerFour.h"
#include "TimerFive.h"
#include "FreqPeriodCounter.h"

//Frequency generation
double t_1_5 = 1;
double t_5_10 = 5;
bool flag_1_5 =false; //flag allow change between increment and decrement
bool flag_5_10 = false;

//Orientation
const byte counterPin = 3; // connect pin 3 to pin 9
const byte counterInterrupt = 1; // = pin 3

double val = 0;
FreqPeriodCounter counter(counterPin, micros);

void setup()
{
	//Pinout and timers for frequency generation
	pinMode(10, OUTPUT);				//1-5KHz pin
	pinMode(11, OUTPUT);				//5-10KHz pin

	Timer1.initialize(500);
	//Timer1.pwm(9,512);
	Timer1.attachInterrupt(callback_1_5); 	//attach callback
	Timer3.initialize(500);
	Timer3.attachInterrupt(callback_5_10);

	//Pinout and timers for stepper motor control
	pinMode(6, OUTPUT);
	pinMode(44, OUTPUT);

	Timer4.initialize(500);
	//Timer4.pwm(6, 512);
	Timer4.attachInterrupt(callback_m0);
	Timer5.initialize(500);
	Timer5.attachInterrupt(callback_m1);
}

void callback_1_5()
{
	digitalWrite(10, digitalRead(10)^1);
}

void callback_5_10()
{
	digitalWrite(11, digitalRead(11)^1);
}

void callback_m0()
{
	digitalWrite(6,digitalRead(6)^1);
}

void callback_m1()
{
	digitalWrite(44,digitalRead(44)^1);
}

void loop()
{ 
	if(flag_1_5 == false)
	{
		Timer1.setPeriod(500/t_1_5); // f = 1kHz //increment t to change period to allow different frequency generation
		t_1_5 += 0.01;
		delay(10);
		if(t_1_5 >= 4.6)
		{
    		flag_1_5 = true;
		}
	}
	if(flag_1_5 == true)
	{
		Timer1.setPeriod(500/t_1_5); // f = 1kHz
		t_1_5 -= 0.01; //decrement t to change period to allow different frequency generation
		delay(10);
		if(t_1_5 <= 1)
		{
    		flag_1_5 = false;
		}
	}

	if(flag_5_10 == false)
	{
		Timer3.setPeriod(500/t_5_10); // f = 5kHz //increment t to change period to allow different frequency generation
		t_5_10 += 0.01;
		delay(10);
		if(t_5_10 >= 9.6)
		{
    		flag_5_10 = true;
		}
	}
	if(flag_5_10 == true)
	{
		Timer3.setPeriod(500/t_5_10); // f = 5kHz
		t_5_10 -= 0.01; //decrement t to change period to allow different frequency generation
		delay(10);
		if(t_5_10 <= 1)
		{
    		flag_5_10 = false;
		}
	}

	//Increment stepper motors
	Timer4.setPeriod(500/.00020);
	Timer5.setPeriod(500/.17);

	/*******
	Orientation system
	Description: Collection bin trigger for RF transmission
	Inputs: 5KHz
	Outputs: 8KHz, then switches back to 5KHz
	*******/

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
		if (val > 4900 && val < 5100) // Check range 
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
}
