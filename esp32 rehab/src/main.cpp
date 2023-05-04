#include <Arduino.h>
#include "secuencias.h"
#include <Adafruit_NeoPixel.h>
#include <WiFi.h>
#include <esp_now.h>
#include <recibir.h>
#include <enviar.h>


int enviado;

//------------------------------------------------------------
//Adafruit_NeoPixel strip = Adafruit_NeoPixel(49, 16, NEO_GRB + NEO_KHZ800);


void setup() {

  Serial.begin(115200); 

  WiFi.mode(WIFI_STA);//Configura el modo de WiFi como estación (cliente)
  
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
  return; 
  } else {
    Serial.println("ESP-NOW initialization OK");
  }
    peering();
    esp_now_register_recv_cb(OnDataRecv);

}
//------------------------------------------------------------
void loop() {
  enviado = random(0, 100);
  Serial.println("Datos recibidos: ");
  Serial.println(myData.patron);
  Serial.println(myData.color);
  delay(1000);
  if(recibido==true){
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &enviado, sizeof(enviado));
    Serial.println("enviado: ");
    Serial.println(enviado);
  }
  delay(1000);
}
