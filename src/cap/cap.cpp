#include <Arduino.h>
#include <string>  


const char* CAP_TEMP = 
"<?xml version = \"1.0\" encoding = \"utf8\"?>"
"<alert xmlns = \"urn:oasis:names:tc:emergency:cap:1.2\">"
    "<identifier>%s</identifier>"
    "<sender>180594V_NODE_MCU</sender>"
    "<sent>%s</sent>"
    "<status>Actual</status>"
    "<msgType>Alert</msgType>"
    "<scope>Private</scope>"
    "<info>"
    "<category>Env</category>"
    "<event>SENSOR_READINGS</event>"
    "<urgency>Past</urgency>"
    "<severity>Minor</severity>"
    "<certainty>Observed</certainty>"
    "<senderName>180594V_NODE_MCU DEVICE</senderName>"
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

String gen_random_id() {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    String tmp_s;
    tmp_s.reserve(32);

    for (int i = 0; i < 32; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    
    return tmp_s;
}

void generateCAP(char* buffer,String datetime, float temp_mean,float temp_std,float humidity_mean,float humidity_std,
float pressure_mean,float pressure_std,float light_mean,float light_std){
        sprintf(buffer,CAP_TEMP,gen_random_id(),datetime, 
        String(temp_mean).c_str(), String(temp_std).c_str(), 
        String(humidity_mean).c_str(), String(humidity_std).c_str(), 
        String(pressure_mean).c_str(), String(pressure_std).c_str(), 
        String(light_mean).c_str(), String(light_std).c_str()
    );

}




