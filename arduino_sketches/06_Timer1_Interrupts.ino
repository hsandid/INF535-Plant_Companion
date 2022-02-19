// Purpose : Shows how to use Timer1 with Interrupts


ISR(TIMER1_COMPA_vect) // TIMER1 COMPARATOR FUNCTION
{
}

void setup() {
  Serial.begin(9600);
 
  // Stop interrupts while configuring
  // Remember that it only stops for 4 clock cycles
  noInterrupts(); 
 
  //set Timer1 interrupt at 1Hz (15624 factor)
  TCCR1A = 0; // set entire TCCR1A register to 0
  TCCR1B = 0; // same for TCCR1B
  TCNT1 = 0; //initialize counter value to 0
  
  // set compare match register for 1Hhz increments 
  OCR1A = 15624; // = (16*10^6) / (1*1024) - 1 (must be less than 65536) 
  // OCR1A = 31248; // = ((16*10^6) / (1*1024) - 1)*2 -> THIS IS FOR 2HZ 
  // OCR1A = 62496; // = ((16*10^6) / (1*1024) - 1)*4 (must be less than 65536) -> THIS IS FOR 4HZ 
  
  interrupts(); //allow interrupts again
  
  noInterrupts(); // Stop interrupts while configuring
  // turn on CTC mode 
  TCCR1B |= (1 << WGM12); 
  // Set CS10 and CS12 bits for 1024 prescaler 
  TCCR1B |= (1 << CS12) | (1 << CS10); 
  // enable timer compare interrupt 
  TIMSK1 |= (1 << OCIE1A); 
  
  interrupts(); //allow interrupts again
}


void loop() {
 
	// Following routine is to reset the timer counter to zero
	// Should not be used unless useful in code

	noInterrupts(); //stop interrupts while configuring
	TCCR1A = 0; // set entire TCCR1A register to 0
	TCCR1B = 0; // same for TCCR1B
	TCNT1 = 0; //initialize counter value to 0
	interrupts(); //allow interrupts again
}