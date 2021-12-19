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

#define SERVER_UPDATE_FREQUENCY 15*60*1000 //15 minutes in millisec
#define MAX_SAMPLES 15

const float SAMPLE_PERIOD = SERVER_UPDATE_FREQUENCY / MAX_SAMPLES; // gap between to readings
long lastSampleTimeMillis;
char cap_string[3000]; // to store CAP string
int currentSampleNumber = 0;
char timestamp[32] = {};

queue<String> capQueue; // to store failed CAP recors to send

//sample buffer to hold sample readings
float temperatureSamples[MAX_SAMPLES];
float humiditySamples[MAX_SAMPLES];
float pressureSamples[MAX_SAMPLES];
float lightSamples[MAX_SAMPLES];


//clearing a buffer
void clearBuffer(float* buffer) {
  for (int i = 0; i < MAX_SAMPLES; i++) {
    buffer[i] = NULL;
  }
}

// clearing sample arrays
void clearSamples() {
  clearBuffer(temperatureSamples);
  clearBuffer(humiditySamples);
  clearBuffer(pressureSamples);
  clearBuffer(lightSamples);
}

void getTimestamp(char *timestamp){
  struct tm details;
  if (getLocalTime(&details))
  {
    char string[32];
    time_t t = time(NULL);
    strftime(string, sizeof(string), "%Y-%m-%dT%H:%M:%S%z", localtime(&t));
    sprintf(timestamp, string);
    
  }
  else{
    Serial.println("Error while getting the time");
  }
}

//setting up wifi and sensor modules
void setup() {
  Serial.begin(115200);
  initWIFI();
  initNTP();
  initiPressureSensor();
  initDHTSensor();
}
void loop() {

    //if there are failed record send, send then now 
  while(!capQueue.empty()) {
      String cap_front = capQueue.front();
      bool isSent = postData(cap_front);
      if(isSent){capQueue.pop();}
      else{
          break;
      }
  }
  //sample only if the gap is more than the sample period otherwise do nothing
  if(SAMPLE_PERIOD>millis()-lastSampleTimeMillis){return;}

  //if arrays full create CAP record and try to send it to server
  if(currentSampleNumber==MAX_SAMPLES){
      Serial.println("Updating server.....");
      //calculate means and std_devs
      float temp_mean = mean(temperatureSamples, MAX_SAMPLES);
      float temp_std_dev = stdDev(temperatureSamples, MAX_SAMPLES, temp_mean);
      float humidity_mean = mean(humiditySamples, MAX_SAMPLES);
      float humidity_std_dev = stdDev(humiditySamples, MAX_SAMPLES, humidity_mean);
      float pressure_mean = mean(pressureSamples, MAX_SAMPLES);
      float pressure_std_dev = stdDev(pressureSamples, MAX_SAMPLES, pressure_mean);
      float light_mean = mean(lightSamples, MAX_SAMPLES);
      float light_std_dev = stdDev(lightSamples, MAX_SAMPLES, light_mean);

      getTimestamp(timestamp);
      generateCAP(cap_string,String(timestamp),temp_mean,temp_std_dev,humidity_mean,humidity_std_dev,
      pressure_mean,pressure_std_dev,light_mean,light_std_dev);

      //try to send generated CAP
      bool isSent = postData(cap_string);
      if(isSent){Serial.println("Senor data uploded successfully");}
      else{
          Serial.println("Senor data added to cache");
          capQueue.push(cap_string);
      }
      clearSamples();
  }

  // create a sample reading by reading all sensors
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







