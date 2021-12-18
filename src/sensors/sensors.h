#ifndef SENSORS_H
#define SENSORS_H

void initiPressureSensor();
float readPressureSensor();

void initDHTSensor();
float readDHTHumidity();
float readDHTTemperature();

float readLDR();

#endif