// Purpose : Show how to invoke interrupt functions for both HW interrupts 0 and 1
// on pins 2 and 3 of the Arduino UNO respectively
// Used in conjunction with Sleep to wake the device
// (What about the ESP ?)

#define ButtonA 2
#define ButtonB 3

#include <avr/sleep.h>

void setup() {
	Serial.begin(9600);
	pinMode(ButtonA,INPUT_PULLUP);
	pinMode(ButtonB,INPUT_PULLUP);
	// Select most power saving sleeping mode
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);


	noInterrupts(); //Stop interrupts while configuring
	//Activate interrupt on rising edge for both HW Interrupts 0 and 1
	EICRA = 0;
	EICRA |= (1 << ISC01) | (1 << ISC11); 
	EIMSK |= (1 << INT1) | (1 << INT0); 
	interrupts(); // Re-enable interrupts

	// Function-based method of attaching interrupts (not-used)
	//attachInterrupt(digitalPinToInterrupt(ButtonA), lightSwitchA,RISING);
	//attachInterrupt(digitalPinToInterrupt(ButtonB), lightSwitchB,RISING);
}


ISR(INT0_vect) // INT0 Interrupt Function
{ 
}

ISR(INT1_vect) // INT1 Interrupt Function
{
}


  

void loop() {
  
  // Put device to sleep until waken up by an interrupt
  sleep_mode(); 
}