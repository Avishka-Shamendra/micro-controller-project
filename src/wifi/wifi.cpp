#include <Arduino.h>
#include <WiFi.h>
#include "config.h"

/*initilize wifi connection*/
void initWIFI(){
    WiFi.begin(SSID, PASSWORD);
    while (WiFi.status() != WL_CONNECTED){
        delay(1000);
        Serial.print("Connecting to WIFI.....");
    }
    Serial.print("Connected to WIFI");
}

/* auto connect if wifi disconnect*/
bool isWIFI(){
    if(WiFi.status() != WL_CONNECTED){
        WiFi.begin(SSID, PASSWORD);
        if (WiFi.status() == WL_CONNECTED){
            Serial.print("Connected to WIFI");
            return true;
        }
        Serial.println("WIFI disconnected");
        return false;
    }else{
        return true;
    }
}
