#include <Arduino.h>
#include <string>  


const char* CAP_TEMP = 
"<?xml version = \"1.0\" encoding = \"utf8\"?>"
"<alert>"
    "<identifier>%s</identifier>"
    "<sender>AVISHKA'S NODE_MCU</sender>"
    "<sent> %s</sent>"
    "<status>Actual</status>"
    "<msgType>Alert</msgType>"
    "<scope>Private</scope>"
    "<info>"
    "<category>Env</category>"
    "<event>SENSOR_READINGS</event>"
    "<urgency> Past</urgency>"
    "<severity> Minor</severity>"
    "<certainty> Observed</certainty>"
    "<senderName>AVISHKA'S NODE_MCU DEVICE</senderName>"
    "<parameter><valueName>TEMP_MEAN</valueName><value>%s</value></parameter>"
    "<parameter><valueName>TEMP_STD</valueName><value>%s</value></parameter>"
    "<parameter><valueName>HUMIDITY_MEAN</valueName><value>%s</value></parameter>"
    "<parameter><valueName>HUMIDITY_STD</valueName><value>%s</value></parameter>"
    "<parameter><valueName>PRESSURE_MEAN</valueName><value>%s</value></parameter>"
    "<parameter><valueName>PRESSURE_STD</valueName><value>%s</value></parameter>"
    "<parameter><valueName>LIGHT_MEAN</valueName><value>%s</value></parameter>"
    "<parameter><valueName>LIGHTSTD</valueName><value>%s</value></parameter>"
    "</info>"
"</alert>";

void generateCAP(char* buffer,String randID,String datetime, double temp_mean,double temp_std,double humidity_mean,double humidity_std,
double pressure_mean,double pressure_std,double light_mean,double light_std){
        sprintf(buffer,CAP_TEMP,randID,datetime, 
        String(temp_mean).c_str(), String(temp_std).c_str(), 
        String(humidity_mean).c_str(), String(humidity_std).c_str(), 
        String(pressure_mean).c_str(), String(pressure_std).c_str(), 
        String(light_mean).c_str(), String(light_std).c_str()
    );

}




