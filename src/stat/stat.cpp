#include <Arduino.h>
/*methods to calculate mean and standard deviation of samples*/
float mean(float arr[], int length)
{
    float total = 0;
    for (int i = 0; i < length; i++){
        total += arr[i];
    }
    return round((total / length));
}

float stdDev(float arr[], int length, float mean)
{
    float var = 0;
    for (int i = 0; i < length; i++){
        var += pow((arr[i] - mean), 2);
    }
    return round(sqrt(var)) / length;
}