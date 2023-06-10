#include <WiFi.h>
#include <esp_now.h>
#include <cstring>
#include "counter.h"
#include "enviar.h"
#include "recibir.h"

//--------------------Variables---------------------------------
//SoftwareSerial BTSerial;  //controlar esta parte. 


void OnDataRecv(const uint8_t * mac_addr, const uint8_t *incomingData, int len) {
  //----------------Solo muestra la MAC---------------------------------
    char macStr[18];
    snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
            mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  //--------------------Recibir datos-----------------------------------
    memcpy(&message, incomingData, sizeof(message)); 
    boardsStruct[message.id-1].recibir = message.recibir; 
  //---------------------Enviar Proximos --------------------------------
    enviarMensaje(mac_addr);

    writeBT(checkID(mac_addr), patron[counter], BTmessage.color);
  //--------------------Control de Counter--------------------------------
    counter++; //actualizo el valor del contador para que el proximo valor a enviar.
    if (counter>=strlen(patron)){ //controlo el contador. Si llega al final del array, lo reinicio y se repite el patron.
      counter=0;
    } 
}
