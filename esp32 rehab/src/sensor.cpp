#include <Arduino.h>
#include <secuencias.h>
#include <WiFi.h>
#include <esp_now.h>
#include "counter.h"
#include "sensor.h"


//-------------------------------------------------------------
bool sensorValue; //Variable que guarda el valor de la entrada del sensor
int sensorPin; //Variable que guarda el PIN de la entrada del sensor.
//-------------------------------------------------------------
void initIR(int Pin){
    pinMode(Pin, INPUT);
    sensorPin = Pin;
}
//Función que inicializa la entrada digital del sensor. Requiere un valor entero que es la entrada del PIN. Se guarda la información del PIN 
//en sensorPin paara la función apagarSecuencia
//-------------------------------------------------------------
void apagarSecuencia(){
    sensorValue = digitalRead(sensorPin);// lee el valor del sensor
      if (sensorValue==LOW) {
        tira.clear();
        counter++;
        patrones(patron[counter],BTmessage.color);
       // Serial.print('1');
       // Serial.print(patron[counter]);
       // Serial.print(BTmessage.color);
       // Serial.print('\n');
        } 
    } 
//La función principal es leer constantemente la entrada del sensor. Si la salida es LOW, hay un obstaculo y el la variable toMaster 
//(la que irá del slave al master) se pondrá en true. Entonces esta información irá al master. Luego se limpian las tiras y se espera a que lleguen nuevos valores
//Al final, se reestablece  el valor de la variable toMaster a False. 