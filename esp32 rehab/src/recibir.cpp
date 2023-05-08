#include <WiFi.h>
#include <esp_now.h>
#include <cstring>
#include "secuencias.h"
#include "recibir.h"
#include <Adafruit_NeoPixel.h>
#include "enviar.h"
#include "sensor.h"
/*
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
*/
//--------------------Funcion de recibir-------------------------------------------

struct_message myData;


bool recibido;

void OnDataRecv(const uint8_t *macAddr, const uint8_t *incomingData, int len) {


    //------------- Copio la direccion MAC del emisor-------------------------
    if(flag==false){
      memcpy(&broadcastAddress, macAddr, sizeof(broadcastAddress));
      flag=true;
    
    char macStr[18];  
    Serial.print("Packet received from: ");
    snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           macAddr[0], macAddr[1], macAddr[2], macAddr[3], macAddr[4], macAddr[5]);
    Serial.println(macStr);
    //------------------------------------------------------------
    Serial.println("Packet received");
    memcpy(&myData, incomingData, sizeof(myData));
    //------------------------------------------------------------
    recibido = true;
    //------------- Imprimo los datos recibidos-------------------------
    Serial.println();
    Serial.println(myData.patron);
    Serial.println(myData.color);
    // Uso mi secuencia de tiras leds
    flechas(myData.patron, myData.color); 
    //------------- Estado de flag-------------------------
    flag=true;
    }
  } 

