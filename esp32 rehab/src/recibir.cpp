#include <WiFi.h>
#include <esp_now.h>
#include <cstring>
#include "secuencias.h"
#include "recibir.h"
#include <Adafruit_NeoPixel.h>
#include "enviar.h"
#include "sensor.h"

struct_message myData; //Estructura que recibo del Master. Contiene la información de patrón y color a mostrar en las tiras.

char convertASCII(int asciiValue) {
    // Check if the ASCII value represents a number
    if (asciiValue >= 48 && asciiValue <= 57) {
        // Convert ASCII value to number
        return static_cast<char>(asciiValue);
    }
    // Check if the ASCII value represents an uppercase letter
    else if (asciiValue >= 65 && asciiValue <= 90) {
        // Convert ASCII value to uppercase letter
        return static_cast<char>(asciiValue);
    }
    // Check if the ASCII value represents a lowercase letter
    else if (asciiValue >= 97 && asciiValue <= 122) {
        // Convert ASCII value to lowercase letter
        return static_cast<char>(asciiValue);
    }
    else {
        // Invalid ASCII value, return a default character
        return '?';
    }
}
void OnDataRecv(const uint8_t *macAddr, const uint8_t *incomingData, int len) {
    //------------- Copio la direccion MAC del emisor-------------------------
    memcpy(&broadcastAddressMaster, macAddr, sizeof(broadcastAddressMaster));          
        char macStr[18];  
        macAddr[0], macAddr[1], macAddr[2], macAddr[3], macAddr[4], macAddr[5];
        Serial.println(macStr); //esta parte solo sirve para mostrar en el Monitor la dirección MAC del esp emisor. Descartarlo para el proyecto final.
    //---------------------------------------------------------------------
    memcpy(&myData, incomingData, sizeof(myData)); //Copio los datos recibidos en la estructura myData 
    //------------------Imprimo flechas-------------------------------------
    patrones(convertASCII(myData.patron), myData.color);  //Pasa a mostrar el patron con el color usando la función FLECHAS
    }   

    
  

