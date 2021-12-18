#include <Arduino.h>
#include <WiFi.h>
#include "config.h"

void initWIFI(){
    WiFi.begin(SSID, PASSWORD);
    while (WiFi.status() != WL_CONNECTED){
        delay(1000);
        Serial.print("Connecting to WIFI.....");
    }
    Serial.print("Connected to WIFI");
}

bool refreshWIFI(){
    WiFi.begin(SSID, PASSWORD);
    if (WiFi.status() == WL_CONNECTED){
        Serial.print("Connected to WIFI");
        return true;
    }
    Serial.println("WIFI disconnected");
    return false;
}
