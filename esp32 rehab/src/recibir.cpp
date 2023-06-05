#include <WiFi.h>
#include <esp_now.h>
#include <cstring>
#include "secuencias.h"
#include "recibir.h"
#include <Adafruit_NeoPixel.h>
#include "enviar.h"
#include "sensor.h"

struct_message myData; //Estructura que recibo del Master. Contiene la información de patrón y color a mostrar en las tiras.

void OnDataRecv(const uint8_t *macAddr, const uint8_t *incomingData, int len) {
    //------------- Copio la direccion MAC del emisor-------------------------
    memcpy(&broadcastAddressMaster, macAddr, sizeof(broadcastAddressMaster));          
        char macStr[18];  
        Serial.print("Packet received from: ");
        snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
        macAddr[0], macAddr[1], macAddr[2], macAddr[3], macAddr[4], macAddr[5]);
        Serial.println(macStr); //esta parte solo sirve para mostrar en el Monitor la dirección MAC del esp emisor. Descartarlo para el proyecto final.
    //---------------------------------------------------------------------
    Serial.println("Packet received");
    memcpy(&myData, incomingData, sizeof(myData)); //Copio los datos recibidos en la estructura myData 
    //------------- Imprimo los datos recibidos----------------------------
        Serial.println();
        Serial.println(myData.patron);  //esta parte se descarta para el proyecto final. Solo sirve para mostrar en el Monitor el patrón recibido.
        Serial.println(myData.color);
    //------------------Imprimo flechas-------------------------------------
    patrones(myData.patron, myData.color);  //Pasa a mostrar el patron con el color usando la función FLECHAS
    
    }   

    
  

