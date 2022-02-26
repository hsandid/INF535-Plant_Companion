
#define ARDUINOJSON_ENABLE_PROGMEM 0

#include <ArduinoJson.h>    //https://github.com/bblanchon/ArduinoJson
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>


const char* ssid     = "Scan";
const char* password = "fZ845(09";
String plant_id = "XXXX";

float temperature = 0.0;
float humidity = 0.0;
float light = 0.0;
float color = 0.0;
float moisture = 0.0;

HTTPClient http;



WiFiClient client;

int  iterations = 1800;

void setup()
{

  Serial.begin(9600);

  connectToWifi();

}

void loop() {

  delay(2);

  if (iterations == 1800) //We check for updated weather forecast once every hour
  {
    iterations = 0;
    getSystemUpdate();
    updateSensorData();
  }
  iterations++;
}

void connectToWifi()
{
  WiFi.enableSTA(true);

  delay(2000);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
}

void getSystemUpdate() {
  String url = "http://129.104.95.82/api/activate.php?plant_id=" + plant_id;
  http.useHTTP10(true);
  http.begin(url);

  int res = http.GET();
  if (res > 0)
  {
    // Get the request response payload
    String payload = http.getString();
    Serial.println(payload);

    const size_t capacity = JSON_OBJECT_SIZE(3) + JSON_ARRAY_SIZE(2) + 60;
    DynamicJsonDocument doc(capacity);

    // Parse JSON object
    DeserializationError error = deserializeJson(doc, payload);
    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      http.end();
      return;
    }

    // Extract values
    Serial.println(F("Response:"));
    Serial.println(doc["status"].as<int>());
    Serial.println(doc["ssid"].as<String>());
    Serial.println(doc["password"].as<String>());

    // Disconnect
    http.end();
  }
}

void updateSensorData() {
  String url = "http://129.104.95.82/api/insert_data.php";
  http.useHTTP10(true);
  http.begin(url);

  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  int httpResponseCode = http.POST("plant_id="+ plant_id+ "&temperature=" + temperature + "&humidity=" + humidity + "&light=" + light + "&color=" + color + "&moisture=" + moisture);

  // Disconnect
  http.end();
}
