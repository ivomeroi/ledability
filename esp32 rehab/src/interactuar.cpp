#include <Arduino.h>
#include "secuencias.h"
#include <secuencias.h>
#include "globales.h"

void interaccion(int sensorPin){
    pinMode(sensorPin, INPUT);
    int sensorValue = 0;
    sensorValue = digitalRead(sensorPin);  // lee el valor del sensor
    while (sensorValue==HIGH)
    {
      tira.clear();
    }
    
}


