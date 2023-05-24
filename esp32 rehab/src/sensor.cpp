#include <Arduino.h>
#include <secuencias.h>
#include <sensor.h>
#include <WiFi.h>
#include <esp_now.h>
#include <enviar.h>
#include <hc05.h>
#include <counter.h>

//-------------------------------------------------------------
int sensorPin; //Variable que guarda el PIN de la entrada del sensor.
bool sensorValue; //Variable que guarda el valor de la entrada del sensor
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
        int randomColor = random(0,3);
        tira.clear();
        counter++;
        patrones(patron[counter],randomColor);
        writeBT(0,patron[counter],randomColor);
        } 
    } 
//La función principal es leer constantemente la entrada del sensor. Si la salida es LOW, hay un obstaculo y el la variable toMaster 
//(la que irá del slave al master) se pondrá en true. Entonces esta información irá al master. Luego se limpian las tiras y se espera a que lleguen nuevos valores
//Al final, se reestablece  el valor de la variable toMaster a False. 