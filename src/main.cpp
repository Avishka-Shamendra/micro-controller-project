/* import all neccessary libraries*/
#include <SPI.h>
#include <Arduino.h>
#include <wifi.h>
#include <queue>
#include "time.h"

#include "./sensors/sensors.h"
#include "./network/http.h"
#include "./wifi/wifi.h"
#include "./wifi/config.h"
#include "./cap/cap.h"
#include "./ntp/ntp.h"
#include "./stat/stat.h";
using namespace std;

#define SERVER_UPDATE_FREQUENCY 15*60*1000
#define MAX_SAMPLES 15

const float SAMPLE_PERIOD = SERVER_UPDATE_FREQUENCY / MAX_SAMPLES;
long lastSampleTimeMillis;
char cap_string[3000];
int currentSampleNumber = 0;

queue<String> capQueue;
float temperatureSamples[MAX_SAMPLES];
float humiditySamples[MAX_SAMPLES];
float pressureSamples[MAX_SAMPLES];
float lightSamples[MAX_SAMPLES];


void clearBuffer(float* buffer) {
  for (int i = 0; i < MAX_SAMPLES; i++) {
    buffer[i] = NULL;
  }
}

void clearSamples() {
  clearBuffer(temperatureSamples);
  clearBuffer(humiditySamples);
  clearBuffer(pressureSamples);
  clearBuffer(lightSamples);
}

void setup() {
  Serial.begin(115200);
  initWIFI();
  initNTP();
  initiPressureSensor();
  initDHTSensor();
}
void loop() {

  while(!capQueue.empty()) {
      String cap_front = capQueue.front();
      bool isSent = postData(cap_front);
      if(isSent){capQueue.pop();}
      else{
          break;
      }
  }
  if(SAMPLE_PERIOD>millis()-lastSampleTimeMillis){return;}

  if(currentSampleNumber==MAX_SAMPLES){
      Serial.println("Updating server.....");
      float temp_mean = mean(temperatureSamples, MAX_SAMPLES);
      float temp_std_dev = stdDev(temperatureSamples, MAX_SAMPLES, temp_mean);
      float humidity_mean = mean(humiditySamples, MAX_SAMPLES);
      float humidity_std_dev = stdDev(humiditySamples, MAX_SAMPLES, humidity_mean);
      float pressure_mean = mean(pressureSamples, MAX_SAMPLES);
      float pressure_std_dev = stdDev(pressureSamples, MAX_SAMPLES, pressure_mean);
      float light_mean = mean(lightSamples, MAX_SAMPLES);
      float light_std_dev = stdDev(lightSamples, MAX_SAMPLES, light_mean);

      generateCAP(cap_string,"datetime",temp_mean,temp_std_dev,humidity_mean,humidity_std_dev,
      pressure_mean,pressure_std_dev,light_mean,light_std_dev);

      bool isSent = postData(cap_string);
      if(isSent){Serial.println("Senor data uploded successfully");}
      else{
          Serial.println("Senor data added to cache");
          capQueue.push(cap_string);
      }
      clearSamples();
  }

  lastSampleTimeMillis=millis();
  Serial.println("Reading sensors...");
  float temperature = readDHTTemperature();
  float humidity = readDHTHumidity();
  float pressure = readPressureSensor();
  float light = readLDR();
  temperatureSamples[currentSampleNumber] = temperature;
  humiditySamples[currentSampleNumber] = humidity; 
  pressureSamples[currentSampleNumber] = pressure;
  lightSamples[currentSampleNumber] = light;
  currentSampleNumber++;
}







