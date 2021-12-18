#ifndef CAP_H
#define CAP_H
#include <Arduino.h>
void generateCAP(char* buffer, String randID,String datetime, double temp_mean,double temp_std,double humidity_mean,double humidity_std,
double pressure_mean,double pressure_std,double light_mean,double light_std);

#endif