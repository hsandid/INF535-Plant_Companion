#define ARDUINOJSON_ENABLE_PROGMEM 0

#include <FS.h>
#include <ArduinoJson.h>    //https://github.com/bblanchon/ArduinoJson
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>  //https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266HTTPClient

#define LED 4
#define DEBUG 1
#define SSID_FILE "ssd.txt"
#define PASSWORD_FILE "password.txt"
#define STATUS_FILE "status.txt"
#define PLANT_TYPE_FILE "plant.txt"
#define DEFAULT_SSID "Scan"
#define DEFAULT_PASSWORD "fZ845(09"
#define DEFAULT_PLANT_STAUS "0"
#define DEFAULT_PLANT_TYPE "0"

String manualPump = "0";  //To pump water manually 1 == Pump, 0 == do not pump

const String SERVER_ADDRESS  = "129.104.95.82";
const String PLANT_ID =  "COMPANION-000001";

const char* ssid     = "Scan";
const char* password = "fZ845(09";
String status;
String plantType;

//Store received values from DB as Strings here
String receivedSsid = "";
String receivedPassword = "";
String receivedStatus = "";
String receivedPlantType = "";

//Store received values from DB as Strings here
String storedSsid = "";
String storedPassword = "";
String storedStatus = "";
String storedPlantType = "";

//Use dummy values for sensors, actual values to be provided by Hadi
float temperature = random(0, 100);;
float humidity = random(0, 100);;
float light = random(0, 100);;
float color = random(0, 100);;
float moisture = random(0, 100);;

bool activated = false;

unsigned long previous_time = 0;
int minDelay = 1000;  // 1 seconds delay

HTTPClient http;
WiFiClient client;




void setup() {
#ifdef DEBUG
  Serial.begin(9600);
#endif

  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
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
  storedPlantType = getPlantType();

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

  if (storedPlantType == "") {
    plantType = DEFAULT_PLANT_TYPE;
  } else {
    plantType = storedPlantType;
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
}














void loop() {
  if (!activated) {
    /*Add code to run when system is not yet activated*/

    getSystemUpdate(); //Keep checking for updates but more frequently
    delay(5000);

  } else {
    /*Add code to run when system is activated*/

    if (manualPump == "1") {
      digitalWrite(LED, HIGH);
      delay(5000);
      digitalWrite(LED, LOW);
    }

    String updateString = "plant_id=" + PLANT_ID + "&temperature=" + temperature + "&humidity=" + humidity + "&light=" + light + "&color=" + color + "&moisture=" + moisture;
    updateSensorData(updateString);
    getSystemUpdate();
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

String getPlantType() {
  return readFile(SPIFFS, PLANT_TYPE_FILE);
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

void setPlantType(const char * plantType) {
  writeFile(SPIFFS, PLANT_TYPE_FILE, plantType);
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
    receivedPlantType = doc["plant_type"].as<String>();
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

    if (receivedPlantType != storedPlantType) {
      setPlantType(receivedPlantType.c_str());
    }

#ifdef DEBUG
    Serial.println(String("Received SSID: " + receivedSsid + " Received Password: " + receivedPassword + " Received Status: " + receivedStatus + " Received Plant Type: " + receivedPlantType));
#endif

    if (receivedStatus != storedStatus || receivedSsid != storedSsid  || receivedPassword != storedPassword || receivedPlantType != storedPlantType) {

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
