#include <Arduino.h>


#define TIME_ZONE ((11*3600)/2)
#define NTP_SERVER "pool.ntp.org"
#define DATE_FORMAT "%Y-%m-%dT%H:%M:%S%z"
void initNTP(){
    configTime(TIME_ZONE, 0 , NTP_SERVER);
}