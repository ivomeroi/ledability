#include <WiFi.h>
#include <esp_now.h>
#include <cstring>
#include "recibir.h"
#include "enviar.h"
#include "hc05.h"
#include "counter.h"

//--------------------Variables---------------------------------
SoftwareSerial BTSerial;  //controlar esta parte. 

struct_message message;

struct_message esp2;
struct_message esp3;

struct_message boardsStruct[2]={esp2,esp3}; //Creo una subestructura de la estructura boardsStruct para cada ESP slave

void OnDataRecv(const uint8_t * mac_addr, const uint8_t *incomingData, int len) {
  //----------------Solo muestra la MAC---------------------------------
    char macStr[18];
    Serial.print("Packet received from: ");
    snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
            mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
    Serial.println(macStr); //Muestra la MAC del ESP slave que envió el mensaje (descartar para el fin de proyecto)
  //--------------------Recibir datos-----------------------------------
    memcpy(&message, incomingData, sizeof(message));
      Serial.printf("Board ID %u: %u bytes\n", message.id, len); 
    // Update the structures with the new incoming data (eliminar para el fin de proyecto)
    boardsStruct[message.id-1].recibir = message.recibir; //DEJAR ESTO SI O SI 
    Serial.printf("recibio: %d \n", boardsStruct[message.id-1].recibir); 
    //Esta parte del codigo es para que el ESP master reciba el mensaje de los ESP slaves. 
    //La información es la ID del ESP slave y el boolenano que representa que se interactuo.
  //---------------------Enviar Proximos --------------------------------
    enviarMensaje (mac_addr);
  //--------------------Enviar datos BT--------------------------------
    writeBT(message.id,enviar.patron,enviar.color);
  //--------------------Control de Counter--------------------------------
    if (counter==strlen(patron)){ //controlo el contador. Si llega al final del array, lo reinicio y se repite el patron.
      counter=0;
    } else {
      counter++;//actualizo el valor del contador para que el proximo valor a enviar.
    }
}
