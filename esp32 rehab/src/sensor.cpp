#include <Arduino.h>
#include <secuencias.h>
#include <sensor.h>
#include <WiFi.h>
#include <esp_now.h>
#include <enviar.h>

int sensorPin;

bool sensorValue=true;

void initIR(int Pin){
    pinMode(Pin, INPUT);
    sensorPin = Pin;
}

void apagarSecuencia(){
    sensorValue = digitalRead(sensorPin);// lee el valor del sensor
    if (sensorValue==LOW)
    {
      if (flag==true)
      {
      esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &sensorValue, sizeof(sensorValue)); //enviar respuesta
      tira.clear();
      tira.show();
      delay(1000);
      flag=false;
      }
    } 
}