#include <WiFi.h>
#include <esp_now.h>
#include <cstring>
#include "globales.h"
#include "secuencias.h"

//--------------------Funciones: Determinar si es servidor------------------------
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
//--------------------Funcion de recibir-------------------------------------------
void OnDataRecv(const uint8_t *macAddr, const uint8_t *incomingData, int len) {

    //------------- Copio la direccion MAC del emisor-------------------------
    char macStr[18];  
    Serial.print("Packet received from: ");
    snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           macAddr[0], macAddr[1], macAddr[2], macAddr[3], macAddr[4], macAddr[5]);
    Serial.println(macStr);
    //------------------------------------------------------------
    Serial.println("Packet received");
    memcpy(&dupla, incomingData, sizeof(dupla));
    /*boardsStruct[dupla.id-1].id = dupla.id;
    boardsStruct[dupla.id-1].patron = dupla.patron;
    boardsStruct[dupla.id-1].color = dupla.color;
    //------------------------------------------------------------
    Serial.printf("patron value: %d \n", boardsStruct[dupla.id-1].patron);
    Serial.printf("color value: %d \n", boardsStruct[dupla.id-1].color);*/
    Serial.println();
    // Uso mi secuencia de tiras leds
    flechas(dupla.patron, dupla.color); 

}
//--------------------Funcion de recibir-------------------------------------------
//la readMac sirve para identificar si el ESP32 es el server
//o si es un pad (el que recibe del server. En este caso, el server es el ESP32 1)Recibe el estado de los otros ESP que son pads. 
//En caso que no sea el server recibo la informacion de color y patron a mostrar. 
