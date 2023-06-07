#include <Arduino.h>
#include "secuencias.h"
#include <Adafruit_NeoPixel.h>
#include <WiFi.h>
#include <esp_now.h>
#include <recibir.h>
#include <enviar.h>
#include <sensor.h>


//--------------Set-Up----------------------------------------

void setup() {
//----- Iniciar Variables------------------------------------  
  toMaster.interact = false;
  Serial.begin(9600); 
//----- Iniciar WiFi------------------------------------------
  WiFi.mode(WIFI_STA);//Configura el modo de WiFi como estación (cliente)
  
   if (esp_now_init() != ESP_OK) {
    return; 
}
//--Definición de ID------------------------------------------
    defID();
//----- Emparejar---------------------------------------------
    peering();
//----- Callbacks de Recibir-----------------------------------
    esp_now_register_recv_cb(OnDataRecv);
//----- Iniciar IR --------------------------------------------
    initIR(23);
}
//------------------------------------------------------------
void loop() {
  apagarSecuencia();   
}
