#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "./wifi/config.h"
#include "./wifi/wifi.h"

/*method to post the CAP XML string to the remote server*/
bool postData(String CAP_XML_STR){
    HTTPClient http;
    if (!isWIFI()){return false;}
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