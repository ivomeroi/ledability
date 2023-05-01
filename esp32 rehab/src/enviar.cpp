#include <WiFi.h>
#include <esp_now.h>
#include <cstring>
#include "strmessage.h" //Check si está bien implementado
//--------------------Matriz de MACs--------------------
uint8_t allBroadcastAddresses[2][6] = {
        {0x0C, 0xB8, 0x15, 0xCB, 0xEE, 0x00},
        {0x0C, 0xB8, 0x15, 0xCB, 0xFF, 0x84},
    }; //completar
//--------------------Funciones--------------------
//--Emparejar-- (ver si lo pongo en otro archivo)--
void peering(uint8_t direcciones[2][6]){
    // Init ESP-NOW - Peer
    esp_now_peer_info_t peer[2];

    for (int i = 0; i < 2; i++) {
        peer[i].channel = i;  //registro de un canal por cada direccion
        peer[i].encrypt = false; 
        memcpy(peer[i].peer_addr, direcciones[i], 6);
        if (esp_now_add_peer(&peer[i]) != ESP_OK){ //registro de cada direccion
            Serial.println("Failed to add peer");
            return;
        }
    }
}
//--Enviar-- (de server a otros ESP32)--------------------
void sendpads(uint8_t direcciones[2][6],struct_message dupla){
        // send data
    for(int i = 0; i < 2; i++){
        esp_err_t result = esp_now_send(direcciones[i], (uint8_t *) &dupla, sizeof(dupla));
        if (result == ESP_OK) {
            Serial.println("Sent with success");
        }
        else {
            Serial.println("Error sending the data");
        }
    }
}
