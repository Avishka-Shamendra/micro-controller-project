#ifndef CAP_H
#define CAP_H
#include <Arduino.h>
void generateCAP(char* buffer,String datetime, float temp_mean,float temp_std,float humidity_mean,float humidity_std,
float pressure_mean,float pressure_std,float light_mean,float light_std);

#endif