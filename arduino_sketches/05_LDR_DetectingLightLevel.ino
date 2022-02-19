// Purpose : Sample analog value of an LDR connected to A0.
// Be warned that a proper resistor value must be selected in the circuit
// Also the LDR value we are aiming for can be tweaked.
#define LDR A0
int analogLDRValue = 0;

void setup() {
	Serial.begin(9600);
}

void loop(){
	analogLDRValue = analogRead(LDR);
	Serial.println("LDR Value: "+String(analogLDRValue));
}