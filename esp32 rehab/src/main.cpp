#include <Arduino.h>
#include "secuencias.h"
#include <Adafruit_NeoPixel.h>
#include <WiFi.h>
#include <esp_now.h>
#include <SoftwareSerial.h>
#include "counter.h"
#include "enviar.h"
#include "hc05.h"
#include "recibir.h"
#include "sensor.h"


//------------------------------------------------------------
void setup() {
  
// --- Iniciar Variables ---
  counter=0;
  color_counter=0;
  esp2.recibir=false;
  esp3.recibir=false;
  esp4.recibir=false;
  randomValue=false;
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
  delay(100);
  apagarSecuencia();
  delay(100);

}
  