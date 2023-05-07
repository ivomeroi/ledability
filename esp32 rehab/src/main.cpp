#include <Arduino.h>
#include "secuencias.h"
#include <Adafruit_NeoPixel.h>
#include <WiFi.h>
#include <esp_now.h>
#include <recibir.h>
#include <enviar.h>
#include <sensor.h>

bool flag=false;
//int enviado;

//------------------------------------------------------------

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

    initIR(23);

}
//------------------------------------------------------------
void loop() {
  /*enviado = random(0, 100);
  Serial.println("Datos recibidos: ");
  Serial.println(myData.patron);
  Serial.println(myData.color); */
  apagarSecuencia();
  Serial.print("Sensor: ");
  Serial.print(digitalRead(23));
  Serial.println();
  delay(500);
}
