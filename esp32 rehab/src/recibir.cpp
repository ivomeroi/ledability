#include <WiFi.h>
#include <esp_now.h>
#include <cstring>
#include "secuencias.h"
#include "recibir.h"
#include <Adafruit_NeoPixel.h>
#include "enviar.h"
#include "sensor.h"

struct_message myData;


void OnDataRecv(const uint8_t *macAddr, const uint8_t *incomingData, int len) {
    if (){
    //------------- Copio la direccion MAC del emisor-------------------------
    memcpy(&broadcastAddressMaster, macAddr, sizeof(broadcastAddressMaster));          
        char macStr[18];  
        Serial.print("Packet received from: ");
        snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
        macAddr[0], macAddr[1], macAddr[2], macAddr[3], macAddr[4], macAddr[5]);
        Serial.println(macStr);
    //---------------------------------------------------------------------
    Serial.println("Packet received");
    memcpy(&myData, incomingData, sizeof(myData));
    //------------- Imprimo los datos recibidos----------------------------
    Serial.println();
    Serial.println(myData.patron);
    Serial.println(myData.color);
    // Uso mi secuencia de tiras leds
    flechas(myData.patron, myData.color); 
    }

    }
  

