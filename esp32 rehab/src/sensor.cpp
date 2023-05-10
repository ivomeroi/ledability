#include <Arduino.h>
#include <secuencias.h>
#include <sensor.h>
#include <WiFi.h>
#include <esp_now.h>
#include <enviar.h>

int sensorPin;

bool sensorValue;

bool siguiente;

void initIR(int Pin){
    pinMode(Pin, INPUT);
    sensorPin = Pin;
}

void apagarSecuencia(){
      sensorValue = digitalRead(sensorPin);// lee el valor del sensor
      if (sensorValue==LOW) {
        toMaster.interact = true;
        enviar();
            tira.clear();
            tira.show();
            delay(1000);
        toMaster.interact = false;
        } 
    } 