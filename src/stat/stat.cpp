#include <Arduino.h>

double mean(double arr[], int length)
{
    double total = 0;
    for (int i = 0; i < length; i++){
        total += arr[i];
    }
    return round((total / length));
}

double stdDev(double arr[], int length, double mean)
{
    double var = 0;
    for (int i = 0; i < length; i++){
        var += pow((arr[i] - mean), 2);
    }
    return round(sqrt(var)) / length;
}