#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "./wifi/config.h"

bool postData(char *CAP_XML_STR){
    HTTPClient http;
    if (WiFi.status() != WL_CONNECTED){return false;}
    String DEST_URL = (String)SERVER + "/update";
    http.begin(DEST_URL);

    int res = http.POST(CAP_XML_STR);
    if (res != HTTP_CODE_OK){        
        Serial.printf(http.errorToString(res).c_str());
        http.end();
        return false;
    }
    http.end();
    Serial.printf("Data uploaded to server successfully.");
    return true;
}