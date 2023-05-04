#include <Arduino.h>
#include "secuencias.h"
#include <Adafruit_NeoPixel.h>
#include <WiFi.h>
#include <esp_now.h>
#include <recibir.h>
#include "globales.h"

//------------------------------------------------------------
//Adafruit_NeoPixel strip = Adafruit_NeoPixel(49, 16, NEO_GRB + NEO_KHZ800);

void setup() {

  Serial.begin(115200); 

  WiFi.mode(WIFI_STA);//Configura el modo de WiFi como estación (cliente)
  
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
  return; 
  //strip.setBrightness(20);
  //strip.begin(); 
  //strip.clear(); 

  //peering(allBroadcastAddresses);
  }
    
    esp_now_register_recv_cb(OnDataRecv);

}
//------------------------------------------------------------
void loop() {

  Serial.println(dupla.patron);
  Serial.println(dupla.color);

  delay(1000);

}
