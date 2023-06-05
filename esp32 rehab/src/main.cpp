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
SoftwareSerial BTSerial(3); 
//------------------------------------------------------------
void setup() {
  
// --- Iniciar Variables ---
  counter=0;
  esp2.recibir=false;
  esp3.recibir=false;
  esp4.recibir=false;
  patron=numeros;
// --- Iniciar Serial ---
  Serial.begin(9600); 
  BTSerial.begin(9600);
// --- Iniciar WiFi ---
  WiFi.mode(WIFI_STA);
// --- ESP NOW ---
  if (esp_now_init() != ESP_OK) {
  return; 
  }
//--- Peering: Emparejamiento ---
  peering();
//--- Call back de Recibir ---
  esp_now_register_recv_cb(OnDataRecv);
//--- Init IR ---
  initIR(23);
}

//--------------Fin del Setup-------------------------------------
void loop() {
  listening_bt();

}
   
