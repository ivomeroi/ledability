#ifndef SENSOR_H
#define SENSOR_H

#include <stdint.h>

extern bool sensorValue; 
extern int sensorPin;

void initIR(int sensorPin);
void apagarSecuencia();


#endif // SENSOR_H
