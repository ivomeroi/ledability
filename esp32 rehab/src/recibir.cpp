#include <WiFi.h>
#include <esp_now.h>
#include <cstring>
#include "strstruct.h"
#include "secuencias.h"

//--------------------MAC del server (suponiendo 1 como server)--------------------
uint8_t MACaddressServer[][6] = {
        {0x0C, 0xB8, 0x15, 0xCB, 0xEE, 0x00}
    };
//--------------------Funciones: Determinar si es servidor-----------------------
void readMac(bool isServer){
  WiFi.mode(WIFI_MODE_STA);
  uint8_t mac[6];
  esp_efuse_mac_get_default(mac);
  if (mac[6]==MACaddressServer[0][6]){
   isServer = true;
  }
  else{
   isServer = false;
  }
}
//--------------------Funcion de recibir-----------------------
void OnDataRecv(const uint8_t *incomingData, int len,bool isServer) {
  if (isServer=false){

  memcpy(&myData, incomingData, sizeof(myData));
  //Uso mi secuencia de tiras leds
  flechas(myData.patron, myData.color); 
  //Si no es el server, recibo la información necesaria para mostrar la secuencia
  } else{ 
      //si es el server, recibo el estado de los pads(si ya se apagó o no)
      memcpy(&estadoPad, incomingData, sizeof(estadoPad));
      boardpads[estadoPad.id-1].state = estadoPad.state;
  }
}
//--------------------Funcion de recibir--------------------
//la readMac sirve para identificar si el ESP32 es el server
//o si es un pad (el que recibe del server. En este caso, el server es el ESP32 1)Recibe el estado de los otros ESP que son pads. 
//En caso que no sea el server recibo la informacion de color y patron a mostrar. 
