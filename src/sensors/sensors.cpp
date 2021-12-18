#include <Arduino.h>
#include <Adafruit_BMP085.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

Adafruit_BMP085 bmp;

void initiPressureSensor() {
  if (!bmp.begin()) {
    Serial.println("Failed to find BMP sensor");
  }
}

float readPressureSensor() {
  if (!bmp.begin()) {
    Serial.println("Failed to read BMP sensor.");
    return -1;
  }
  float pressure = bmp.readPressure();
  if (isnan(pressure)){
        Serial.println("Failed to read BMP sensor");
        return 0;
  }
  Serial.printf("BMP Pressure Reading: %f\n", pressure);
  return pressure;
}

/*-----------------------------------------------------------------------------------------------------*/

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void initDHTSensor(){ 
    dht.begin();
}

float readDHTHumidity() {
  float humidity = dht.readHumidity();
  if (isnan(humidity)) {
    Serial.println("Failed to read humidity from DHT sensor.");
    return -1;
  }

  Serial.printf("DHT Humidity Reading: %f\n", humidity);
  return humidity;
}

float readDHTTemperature() {
  float temperature = dht.readTemperature();
  if (isnan(temperature)) {
    Serial.println("Failed to read temp. from DHT sensor.");
    return -1;
  }

  Serial.printf("DHT Temperature Reading: %f\n", temperature);
  return temperature;
}

/*----------------------------------------------------------------------------------------*/

#define LDRPIN 5

float readLDR(){ 
    return analogRead(LDRPIN); 
}