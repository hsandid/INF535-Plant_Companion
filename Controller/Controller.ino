#define ARDUINOJSON_ENABLE_PROGMEM 0

#include <FS.h>
#include <ArduinoJson.h>    //https://github.com/bblanchon/ArduinoJson
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>  //https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266HTTPClient

//#define LED 4
#define DEBUG 1
#define SSID_FILE "ssd.txt"
#define PASSWORD_FILE "password.txt"
#define STATUS_FILE "status.txt"
#define MOISTURE_THRESHOLD_FILE "threshold.txt"
#define DEFAULT_SSID "Scan"
#define DEFAULT_PASSWORD "fZ845(09"
#define DEFAULT_PLANT_STAUS "0"
#define DEFAULT_MOISTURE_THRESHOLD "50"

//DHT (Temp/Hum. sensor) Configuration & Variables
#include <DHT.h>
#define DHTPIN D1  // PIN D1
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

//Moisture Sensor
#define sensor_pin A0  /* Connect Soil moisture analog sensor pin to A0 of NodeMCU */

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

String manualPump = "0";  //To pump water manually 1 == Pump, 0 == do not pump

const String SERVER_ADDRESS  = "129.104.245.192";
const String PLANT_ID =  "COMPANION-000001";

const char* ssid     = "";
const char* password = "";
String status;
String moistureThreshold;

//Store received values from DB as Strings here
String receivedSsid = "";
String receivedPassword = "";
String receivedStatus = "";
String receivedMoistureThreshold = "";

//Store received values from DB as Strings here
String storedSsid = "";
String storedPassword = "";
String storedStatus = "";
String storedMoistureThreshold = "";

//Use dummy values for sensors, actual values to be provided by Hadi
//float temperature = random(0, 100);
//float humidity = random(0, 100);
//float light = random(0, 100);
//float color = random(0, 100);
//float moisture = random(0, 100);

float temperature = 0.0;
float humidity = 0.0;
int light = 0;
String color = " "; // String -> Green, Yellow, Red, Orange
float moisture = 0.0;

bool activated = false;

unsigned long previous_time = 0;
int minDelay = 1000;  // 1 seconds delay

HTTPClient http;
WiFiClient client;




void setup() {
#ifdef DEBUG
  Serial.begin(9600);
#endif

//  pinMode(LED, OUTPUT);
//  digitalWrite(LED, LOW);
  /*Mount file reader*/
  if (!SPIFFS.begin()) {
#ifdef DEBUG
    Serial.println("An Error has occurred while mounting SPIFFS");
#endif
    return;
  }

  storedSsid = getSsid().c_str();
  storedPassword = getPassword().c_str();
#ifdef DEBUG
  Serial.println(storedSsid);
  Serial.println(storedPassword);
#endif

  storedStatus = getStatus();
  storedMoistureThreshold = getMoistureThreshold();
  Serial.println(String(storedMoistureThreshold) + "Stored threshold");

  if (storedSsid == "" || storedPassword == "" || storedSsid == "null" || storedPassword == "null") {
    ssid = DEFAULT_SSID;
    password = DEFAULT_PASSWORD;
  } else {
    ssid = storedSsid.c_str();
    password = storedPassword.c_str();
  }

  if (storedStatus == "") {
    status = DEFAULT_PLANT_STAUS;
  } else {
    status = storedStatus;
  }

  if (storedMoistureThreshold == "") {
    moistureThreshold = DEFAULT_MOISTURE_THRESHOLD;
  } else {
    moistureThreshold = storedMoistureThreshold;
  }
  if (status == "0") {
    activated = false;
  } else {
    activated = true;
  }
  connectToWifi();


#ifdef DEBUG
  Serial.println("Booted...");
#endif

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
  //pinMode(D0, WAKEUP_PULLUP);

}
void loop() {
  if (!activated) {
    /*Add code to run when system is not yet activated*/
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Not Configured"); // Start Printing
    lcd.setCursor(0, 1);
    lcd.print("Fetching Config"); // Start Printing
    getSystemUpdate(); //Keep checking for updates but more frequently
    delay(5000);

  } else {
    /*Add code to run when system is activated*/

//    if (manualPump == "1") {
//      digitalWrite(LED, HIGH);
//      delay(5000);
//      digitalWrite(LED, LOW);
//    }

       // READING #1 & #2: Temperature & Humidity from DHT11 sensor
  temperature = dht.readTemperature();
  humidity =  dht.readHumidity();
  Serial.println("Measurement : "+String(temperature)+" C, "+String(humidity)+" % Humidity");
  
  lcd.backlight(); // Enable or Turn On the backlight
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp. "+String(temperature)+" C"); // Start Printing
  lcd.setCursor(0, 1);
  lcd.print(String(temperature)+" % Humidity"); // Start Printing
  
  // READING #3 MOISTURE
   moisture = ( 100.00 - ( (analogRead(sensor_pin)/1023.00) * 100.00 ) );

  Serial.print("Soil Moisture(in Percentage) = ");
  Serial.print(moisture);
  Serial.println("%");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Soil Moist. "); // Start Printing
  lcd.setCursor(0, 1);
  lcd.print(String(moisture)+"%"); // Start Printing

  delay(2000);

  // READING #4 COLOR SENSOR
   // Set frequency scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  delay(2000);

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

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Color : ");
  if(greenVal < 2000 && greenVal < blueVal && greenVal < redVal)
  {
    Serial.println("Green");
    lcd.print("Green");
  color="Green";
  }
  else if (greenVal < 1100 && blueVal < 1100 && redVal < 1100)
  {
    Serial.println("Yellow");
    lcd.print("Yellow");
  color="Yellow";
  }
  else if (redVal < 1000 && greenVal*0.85 < blueVal)
  {
    Serial.println("Orange");
    lcd.print("Orange");
  color="Orange";
  }
  else if (redVal < 1000 & greenVal*0.85 > blueVal)
  {
    Serial.println("Red");
    lcd.print("Red");
  color="Red";
  }
  else
  {
    Serial.println("Unknown");
    lcd.print("Unknown");
  color="Unknown";
  }
  

  // Setting frequency scaling to off
  digitalWrite(S0,LOW);
  digitalWrite(S1,LOW);

  delay(2000);
  

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Fetching Server"); // Start Printing
  lcd.setCursor(0, 1);
  lcd.print("Update"); // Start Printing

  delay(2000);

  // Add ticker to make system go to sleep if it doesn't work
  getSystemUpdate();
  
  // Check if we should irrigate (CHECK HUMIDITY THRESHOLD / CHECK IF USER REQUESTED IRRIGATION)
  float myMoistureValueToCompare = moistureThreshold.toFloat();
  Serial.println("myMoistureValueToCompare: " +String(myMoistureValueToCompare) +"Moisture: "+moisture);
  if(moisture < myMoistureValueToCompare && manualPump=="1")
  {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("LowMoist/UserReq"); // Start Printing
  lcd.setCursor(0, 1);
  lcd.print("Irrigating!"); // Start Printing
  }
  else if( moisture < myMoistureValueToCompare)
  {
      lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Low Moisture"); // Start Printing
  lcd.setCursor(0, 1);
  lcd.print("Irrigating!"); // Start Printing
  }
  else if (manualPump=="1")
  {
      lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("User Request"); // Start Printing
  lcd.setCursor(0, 1);
  lcd.print("Irrigating!"); // Start Printing
  }
  else
  {
   lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("No Irrigation"); // Start Printing
  lcd.setCursor(0, 1);
  lcd.print("Above "+String(myMoistureValueToCompare)+"%"); // Start Printing
  }

  delay(5000);
  
   lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Pushing Server"); // Start Printing
  lcd.setCursor(0, 1);
  lcd.print("Update"); // Start Printing

  // do a string plantid and 
  //Use an Integer encyption
    String updateString = "plant_id=" + PLANT_ID + "&temperature=" + temperature + "&humidity=" + humidity + "&light=" + light + "&color=" + color + "&moisture=" + moisture;

    // Add ticker to make system go to sleep if it doesn't work
    updateSensorData(updateString);

    delay(2000);
    lcd.noBacklight();
    
    delay(10000);
  }
  reconnectWifi();
}

/*Write data into file*/
void writeFile(fs::FS &fs, const char * path, const char * message) {

#ifdef DEBUG
  Serial.printf("Writing file: %s\r\n", path);
#endif
  File file = fs.open(path, "w");
  if (!file) {
#ifdef DEBUG
    Serial.println("- failed to open file for writing");
#endif
    return;
  }
  if (file.print(message)) {
#ifdef DEBUG
    Serial.println("- file written");
#endif
  } else {
#ifdef DEBUG
    Serial.println("- write failed");
#endif
  }
  file.close();
}

/*Read data from file*/
String readFile(fs::FS &fs, const char * path) {
#ifdef DEBUG
  Serial.printf("Reading file: %s\r\n", path);
#endif
  File file = fs.open(path, "r");
  if (!file) {
#ifdef DEBUG
    Serial.println("- empty file or failed to open file");
#endif
    return String();
  }

#ifdef DEBUG
  Serial.println("- read from file:");
#endif
  String fileContent;
  while (file.available()) {
    fileContent += String((char)file.read());
  }
  file.close();
#ifdef DEBUG
  Serial.println(fileContent);
#endif
  return fileContent;
}

String getSsid() {
  return readFile(SPIFFS, SSID_FILE);
}

String getPassword() {
  return readFile(SPIFFS, PASSWORD_FILE);
}

String getStatus() {
  return readFile(SPIFFS, STATUS_FILE);
}

String getMoistureThreshold() {
  return readFile(SPIFFS, MOISTURE_THRESHOLD_FILE);
}

void setSsid(const char * ssid) {
  writeFile(SPIFFS, SSID_FILE, ssid);
}

void setPassword(const char * password) {
  writeFile(SPIFFS, PASSWORD_FILE, password);
}

void setStatus(const char * status) {
  writeFile(SPIFFS, STATUS_FILE, status);
}

void setMoistureThreshold(const char * moisture) {
  writeFile(SPIFFS, MOISTURE_THRESHOLD_FILE, moisture);
}

void reconnectWifi() {
  unsigned long current_time = millis(); // number of milliseconds since the upload
  if ((WiFi.status() != WL_CONNECTED) && (current_time - previous_time >= minDelay)) {
#ifdef DEBUG
    Serial.print(millis()); Serial.println("Reconnecting to WIFI network");
#endif
    WiFi.disconnect();
    WiFi.reconnect();
    previous_time = current_time;
  }
}

//Connect to WiFi
void connectToWifi()
{
  WiFi.enableSTA(true);

  delay(2000);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
#ifdef DEBUG
    Serial.print(".");
#endif
  }
}

//Pull config data from DB
void getSystemUpdate() {
  String url = "http://" + SERVER_ADDRESS + "/pc/api/activate.php?plant_id=" + PLANT_ID;
  http.useHTTP10(true);
  http.begin(url);

  int res = http.GET();
  if (res > 0)
  {
    // Get the request response payload
    String payload = http.getString();

#ifdef DEBUG
    Serial.println(payload);
#endif

    const size_t capacity = JSON_OBJECT_SIZE(5) + JSON_ARRAY_SIZE(2) + 100;
    DynamicJsonDocument doc(capacity);

    // Parse JSON object
    DeserializationError error = deserializeJson(doc, payload);
    if (error) {
#ifdef DEBUG
      Serial.print(F("deserializeJson() failed: "));
#endif

      http.end();
      return;
    }

    // Extract values
    receivedStatus = doc["status"].as<String>();
    receivedSsid = doc["ssid"].as<String>();
    receivedPassword = doc["password"].as<String>();
    receivedMoistureThreshold = doc["moisture_threshold"].as<String>();
    manualPump = doc["manual_pump"].as<String>();

    if (receivedStatus != storedStatus) {
      setStatus(receivedStatus.c_str());
    }
    if (receivedSsid != storedSsid) {
      setSsid(receivedSsid.c_str());
    }
    if (receivedPassword != storedPassword) {
      setPassword(receivedPassword.c_str());
    }

    if (receivedMoistureThreshold != storedMoistureThreshold) {
      setMoistureThreshold(receivedMoistureThreshold.c_str());
    }

#ifdef DEBUG
    Serial.println(String("Received SSID: " + receivedSsid + " Received Password: " + receivedPassword + " Received Status: " + receivedStatus + " Received Moisture Threshold: " + receivedMoistureThreshold));
#endif

    if (receivedStatus != storedStatus || receivedSsid != storedSsid  || receivedPassword != storedPassword || receivedMoistureThreshold != storedMoistureThreshold) {

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("System Update"); // Start Printing
    lcd.setCursor(0, 1);
    lcd.print("Restarting..."); // Start Printing
    delay(3000);
    lcd.noBacklight();
      ESP.restart(); //ESP.reset();

    }
    // Disconnect
    http.end();
  }
}


//Send sensor data to DB
void updateSensorData(String updateString) {
  String url = "http://" + SERVER_ADDRESS + "/pc/api/insert_data.php";
  http.useHTTP10(true);
  http.begin(url);

  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  int httpResponseCode = http.POST(updateString);

  // Disconnect
  http.end();
}
