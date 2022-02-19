// Purpose : Configure Watchdog Duty Cycling (4 sec default)

#include <avr/wdt.h>
#include <avr/sleep.h>

void setup() {
  Serial.begin(9600);
  
  // Setting sleep mode (Most powersaving value)
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	
  //Stop interrupts while configuring
  noInterrupts();
  // Set bits to enable watchdog timer configuration
  WDTCSR = (1<< WDCE) | (1<<WDE);
  // Set watchdog timeout at 4s; Enable interrupt; Disable reset on interrupt
  WDTCSR = (1 << WDP3) | (0 << WDE) | (1 << WDIE) | (0 << WDP2) | (0 << WDP1) | (0 << WDP0);
  //Enable interrupts again
  interrupts();
}

ISR(WDT_vect) // Watchdog ISR
{

}

void loop() {
	
	// The following two instructions do not make much sense out of a complete program
	// They are provided for reference
	
	// Reset Watchdog
	wdt_reset();
    
	//Go to sleep
    sleep_mode();
}