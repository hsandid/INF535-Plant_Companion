// Chinonso & Hadi
// Purpose : Collect data from our sensor back-to-back
//"Includes" : required for the sensors & other functions
//Defining Pins : Must be modified for ESP8266

//DHT (Temp/Hum. sensor) Configuration & Variables
#include "DHT.h"
#define DHTPIN 3
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
float temperatureMeasurement = 0.0;
float humidityMeasurement = 0.0;

//LDR (Light-Dependant Resistor) Configuration & Variables
#define LDR A0
int analogLDRValue = 0;

//Moisture Sensor Configuration & Variables
#define MOISTUREPIN A1
int analogMoistureValue = 0;

//Color Sensor Configuration
//Reference : https://create.arduino.cc/projecthub/SurtrTech/color-detection-using-tcs3200-230-84a663
#define S0 8
#define S1 9
#define S2 10
#define S3 11
#define COLOROUT 12
int ColorSensRed=0;
int ColorSensGreen=0;
int ColorSensBlue=0;

//LCD Module configuration
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#define LCD_DEVICE_ID 0x27
LiquidCrystal_I2C lcd(LCD_DEVICE_ID, 16, 2); // (characters per line, #lines)


void setup() {
  // Initializing Serial interface on baud rate 9600
  Serial.begin(9600);
  
  // DHT library function to initialize DHT
  dht.begin();
  
  //Initializing Color Sensor Digital Pins
  pinMode(s0,OUTPUT);
  pinMode(s1,OUTPUT);
  pinMode(s2,OUTPUT);
  pinMode(s3,OUTPUT);
  pinMode(out,INPUT);
  //Putting S0/S1 on HIGH/HIGH levels means the output frequency scalling is at 100%
  //LOW/LOW is off HIGH/LOW is 20% and LOW/HIGH is  2%
  digitalWrite(s0,HIGH);
  digitalWrite(s1,HIGH);
  
  //For the Initializing pin 2 as an output
  pinMode(2, OUTPUT);
  
  //Initialization of LCD Module
  lcd.init(); 
}


void loop() {
  
  // READING #1 & #2: Temperature & Humidity from DHT11 sensor
  temperatureMeasurement = dht.readTemperature();
  humidityMeasurement =  dht.readHumidity();
  Serial.println("Measurement : "+String(temperatureMeasurement)+" C, "+String(humidityMeasurement)+" % Humidity");

  // READING #3 : LDR (Light-Dependant Resistor) for Light level
  analogLDRValue = analogRead(LDR);
  Serial.println("LDR Value: "+String(analogLDRValue));
  
  // READING #4 : Moisture Sensor
  analogMoistureValue = analogRead(MOISTUREPIN)
  Serial.println("Moisture Value: "+String(analogMoistureValue));
  
  // READING #5 : Color Sensor
  // S2/S3 levels define which set of photodiodes we are using 
  // LOW/LOW is for RED LOW/HIGH is for Blue and HIGH/HIGH is for green
  // Here we wait until "out" go LOW, we start measuring the duration and stops when "out" is HIGH again
  // It's a time duration measured, which is related to frequency as the sensor gives a frequency depending on the color
  digitalWrite(s2,LOW);
  digitalWrite(s3,LOW);
  ColorSensRed=pulseIn(out,digitalRead(out) == HIGH ? LOW : HIGH); 
  Serial.print("Red value= "); 
  Serial.println(ColorSensRed);
  delay(20);
  digitalWrite(s2,LOW);
  digitalWrite(s3,HIGH);
  ColorSensBlue=pulseIn(out,digitalRead(out) == HIGH ? LOW : HIGH);
  Serial.println("Blue value= ");
  Serial.println(ColorSensBlue);
  delay(20);
  digitalWrite(s2,HIGH);
  digitalWrite(s3,HIGH);
  ColorSensGreen=pulseIn(out,digitalRead(out) == HIGH ? LOW : HIGH); 
  Serial.print("Green value= ");
  Serial.println(ColorSensGreen);
  delay(20);
  
   if (ColorSensRed <=15 && ColorSensGreen <=15 && ColorSensBlue <=15)         //If the values are low it's likely the white color (all the colors are present)
      Serial.println("White");                    
  else if (ColorSensRed<ColorSensBlue && ColorSensRed<=ColorSensGreen && ColorSensRed<23)      //if Red value is the lowest one and smaller thant 23 it's likely Red
      Serial.println("Red");
  else if (ColorSensBlue<ColorSensGreen && ColorSensBlue<ColorSensRed && ColorSensBlue<20)    //Same thing for Blue
      Serial.println("Blue");
  else if (ColorSensGreen<ColorSensRed && ColorSensGreen-ColorSensBlue<= 8)           //Green it was a little tricky, you can do it using the same method as above (the lowest), but here I used a reflective object
      Serial.println("Green");                    //which means the blue value is very low too, so I decided to check the difference between green and blue and see if it's acceptable
  else
     Serial.println("Unknown");                  //if the color is not recognized, you can add as many as you want
  
  // DISPLAY #1 : Onboard LED on the ESP12
  digitalWrite(2, LOW);   // Turn the LED on by making the voltage LOW
  delay(1000);            // Wait for a second
  digitalWrite(2, HIGH);  // Turn the LED off by making the voltage
  
  // DISPLAY #2 : Display message on LCD
  lcd.backlight(); // turns on and off the backlight of the display
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("LCD: Just Booted!      ");
  lcd.setCursor(0, 1);
  lcd.print("Color: ");
  lcd.print(status);
  delay(3000);
  lcd.clear();
  lcd.backlight();
  
  //  Serial.flush();
  //  delay(1000);
}
