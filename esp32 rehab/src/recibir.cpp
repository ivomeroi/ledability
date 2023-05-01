#include <WiFi.h>
#include <esp_now.h>
#include <cstring>
#include "strmessage.h"

//--------------------MAC del server (suponiendo 1 como server)--------------------
uint8_t MACaddressServer[][6] = {
        {0x0C, 0xB8, 0x15, 0xCB, 0xEE, 0x00}
    };
bool isServer;

//--------------------Bool de pads--------------------
bool pad2;
bool pad3;
bool pad4;
// Si es 1, entonces el pad esta prendido (tira leds)
//si es 0, entonces el pad esta apagado (interactuo el paciente)

//--------------------Funciones-----------------------
void readMac(){
  WiFi.mode(WIFI_MODE_STA);
  uint8_t mac[6];
  esp_efuse_mac_get_default(mac);
  if (mac[6]==MACaddressServer[0][6]){
    bool isServer = true;
  }
  else{
    bool isServer = false;
  }
} 
//la readMac sirve para identificar si el ESP32 es el server
//o si es un pad (el que recibe del server. En este caso, el server es el ESP32 1)Recibe el estado de los otros ESP que son pads. 
//En caso que no sea el server recibo la informacion de color y patron a mostrar. 
void 