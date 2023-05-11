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
  
void OnDataRecv(const uint8_t * mac_addr, const uint8_t *incomingData, int len) {
  //----------------Solo muestra la MAC---------------------------------
    char macStr[18];
    Serial.print("Packet received from: ");
    snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
            mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
    Serial.println(macStr);
  //--------------------Recibir datos-----------------------------------
    memcpy(&message, incomingData, sizeof(message));
      Serial.printf("Board ID %u: %u bytes\n", message.id, len);
    // Update the structures with the new incoming data
    boardsStruct[message.id-1].recibir = message.recibir;
    Serial.printf("recibio: %d \n", boardsStruct[message.id-1].recibir); 
  //---------------------Enviar Proximos --------------------------------

  enviarMensaje (mac_addr);

    Serial.println();
  }