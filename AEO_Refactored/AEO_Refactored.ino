#include "AEO_Refactored.h"

int counter = 0;
int loopCounter = 0;


void setup()
{
	Serial.begin(9600);
	//setup_wifi();
	setup_motor();	
}

void loop() 
{
	for(int deg = 0; deg < 90; deg++){
		for (loopCounter = 0; loopCounter < 500; loopCounter++){
			Serial.println(loopCounter);
			step_backward();
		}
	}
	delay(4000);
	
	for(int deg = 0; deg < 90; deg++){
		for (loopCounter = 0; loopCounter < 500; loopCounter++){
			Serial.println(loopCounter);
			step_forward();
		}
	}
	delay(4000);
}

//Reboot the device
void reboot()
{
	Watchdog.enable(2);
}
