#include <Arduino.h>
#include "secuencias.h"
#include <Adafruit_NeoPixel.h>
#include <WiFi.h>
#include <esp_now.h>
#include <recibir.h>
#include <enviar.h>
#include <SoftwareSerial.h>
#include <hc05.h>
#include <sensor.h>
#include <counter.h>
//------------------------------------------------------------

void setup() {
  
  counter=0;
  esp2.recibir=false;
  esp3.recibir=false;
  patron=numeros;

  Serial.begin(9600); 

  WiFi.mode(WIFI_STA);//Configura el modo de WiFi como estación (cliente)
  
   if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
  return; 
  } else {
    Serial.println("ESP-NOW initialization OK");
  }
   
  peering();

  esp_now_register_recv_cb(OnDataRecv);
  
  beginBT(16,17);

  initIR(23);
}
//------------------------------------------------------------
void loop() {
  readBT();
  apagarSecuencia();
}
