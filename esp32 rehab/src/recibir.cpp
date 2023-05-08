#include <WiFi.h>
#include <esp_now.h>
#include <cstring>
#include "secuencias.h"
#include "recibir.h"
#include <Adafruit_NeoPixel.h>
#include "enviar.h"

struct_message message;

struct_message esp2;
struct_message esp3;

struct_message boardsStruct[2]={esp2,esp3};

void OnDataRecv(const uint8_t *macAddr, const uint8_t *incomingData, int len) {
//--------------------------------------------------------------------
      memcpy(&broadcastAddress, macAddr, sizeof(broadcastAddress));          
      char macStr[18];  
      Serial.print("Packet received from: ");
      snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
      macAddr[0], macAddr[1], macAddr[2], macAddr[3], macAddr[4], macAddr[5]);
      Serial.println(macStr);
      //---------------------------------------------------------------------
      Serial.println("Packet received");
      memcpy(&message, incomingData, sizeof(message));
      boardsStruct[message.id-1].recibir = message.recibir;

}
  

