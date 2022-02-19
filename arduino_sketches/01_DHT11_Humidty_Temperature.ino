// Purpose : Configure DHT11 sensor (connected to Pin 3) and read Humidity/Temperature values

#define DHTPIN 3
#define DHTTYPE DHT11
#include "DHT.h"

DHT dht(DHTPIN, DHTTYPE);

float temperatureMeasurement = 0.0;
float humidityMeasurement = 0.0;

void setup() {
  Serial.begin(9600);
  dht.begin();
}


void loop() {
    temperatureMeasurement = dht.readTemperature();
    humidityMeasurement =  dht.readHumidity();
	
    Serial.println("Measurement : "+String(temperatureMeasurement)+" C, "+String(humidityMeasurement)+" % Humidity");
    Serial.flush();
	
	delay(1000);
}