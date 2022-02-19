// Purpose : Using LCD, we want to display a message

#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#define LCD_DEVICE_ID 0x27

LiquidCrystal_I2C lcd(LCD_DEVICE_ID, 16, 2); // (characters per line, #lines)

void setup() {
	Serial.begin(9600);
	// Wait for serial
	while (!Serial) {}
	Serial.print("Sketch:   ");   Serial.println(__FILE__);
	Serial.print("Uploaded: ");   Serial.println(__DATE__);
	
	lcd.init(); 
	lcd.backlight(); // turns on and off the backlight of the display

	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("LCD: Just Booted!      ");
	lcd.setCursor(0, 1);
	lcd.print("Color: ");
	lcd.print(status);
}

void loop() {
  // No code here
  // Can add features related to LCD...
}