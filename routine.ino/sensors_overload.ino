//DHT (Temp/Hum. sensor) Configuration & Variables
#include <DHT.h>
#define DHTPIN D1 // PIN D1
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
float temperatureMeasurement = 0.0;
float humidityMeasurement = 0.0;

//Moisture Sensor
#define sensor_pin A0  /* Connect Soil moisture analog sensor pin to A0 of NodeMCU */
float moisture_percentage = 0.0;

// LCD
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Color Sensor Config
#define S0 D5
#define S1 D6
#define S2 D7
#define S3 D8
#define sensorOut D4

int redVal = 0;
int greenVal = 0;
int blueVal = 0;

void setup() {
  
// DHT library function to initialize DHT
  dht.begin();
  // Init for LCD
  Wire.begin(D2,D3);
  lcd.init();   // initializing the LCD

  // Init for Color Sensor
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  // Trying to fix the DeepSleep issues
  pinMode(D0, WAKEUP_PULLUP);

  Serial.begin(115200);

}

void loop() {
  
   // READING #1 & #2: Temperature & Humidity from DHT11 sensor
  temperatureMeasurement = dht.readTemperature();
  humidityMeasurement =  dht.readHumidity();
  Serial.println("Measurement : "+String(temperatureMeasurement)+" C, "+String(humidityMeasurement)+" % Humidity");
  
  lcd.backlight(); // Enable or Turn On the backlight
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp. "+String(temperatureMeasurement)+" C"); // Start Printing
  lcd.setCursor(0, 1);
  lcd.print(String(temperatureMeasurement)+" % Humidity"); // Start Printing
  delay(2000);
  lcd.noBacklight();
  delay(2000);
  
  // READING #3 MOISTURE
   moisture_percentage = ( 100.00 - ( (analogRead(sensor_pin)/1023.00) * 100.00 ) );

  Serial.print("Soil Moisture(in Percentage) = ");
  Serial.print(moisture_percentage);
  Serial.println("%");

  lcd.backlight(); // Enable or Turn On the backlight
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Soil Moisture " + String(moisture_percentage)+"%"); // Start Printing
  delay(2000);
  lcd.noBacklight();
  delay(2000);

  // READING #4 COLOR SENSOR
   // Set frequency scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);

   // Reading RED value
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  redVal = pulseIn(sensorOut, LOW);
  delay(100);
//  Serial.print("redVal = ");
//  Serial.print(redVal);
  

// Reading Green Value
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  greenVal = pulseIn(sensorOut, LOW);
  delay(100); 
//  Serial.print("greenVal = ");
//  Serial.print(greenVal);
 
  // Reading BLUE value
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  blueVal = pulseIn(sensorOut, LOW);
  delay(100);
//  Serial.print(" blueVal = ");
//  Serial.println(blueVal);

  lcd.backlight(); // Enable or Turn On the backlight
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Color : ");
  if(greenVal < 2000 && greenVal < blueVal && greenVal < redVal)
  {
    Serial.println("Green");
    lcd.print("Green");
  }
  else if (greenVal < 1100 && blueVal < 1100 && redVal < 1100)
  {
    Serial.println("Yellow");
    lcd.print("Yellow");
  }
  else if (redVal < 1000 && greenVal*0.85 < blueVal)
  {
    Serial.println("Orange");
    lcd.print("Orange");
  }
  else if (redVal < 1000 & greenVal*0.85 > blueVal)
  {
    Serial.println("Red");
    lcd.print("Red");
  }
  else
  {
    Serial.println("Unknown");
    lcd.print("Unknown");
  }
  

  // Setting frequency scaling to off
  digitalWrite(S0,LOW);
  digitalWrite(S1,LOW);

  delay(2000);
  lcd.noBacklight();
  delay(2000);

  
  ESP.deepSleep(5e6);
  delay(10);

  

}