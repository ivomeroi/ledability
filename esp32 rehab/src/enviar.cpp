#include <WiFi.h>
#include <esp_now.h>
#include <cstring>
#include "enviar.h"
#include "recibir.h"
#include "hc05.h"

//--------------------Variables---------------------------------
esp_now_peer_info_t peerInfo[2];

uint8_t broadcastAddress[2][6]={
    {0x0C,0xB8,0x15,0xCB,0xFF,0x84}, //ESP2
    {0x0C,0xB8,0x15,0xCB,0xFA,0x1C} //ESP3
};

struct_send enviar;

int counter;
struct_BTmessage BTmessage;
//----------------Funciones peer---------------------------------
void peering() { //funcion de peer que empareja el ESPmaster con los slaves. peerInfo como matriz igual a la cantidad de ESPs slaves
    for (int i = 0; i < 2; i++) {
        memcpy(peerInfo[i].peer_addr, broadcastAddress[i], 6); 
        peerInfo[i].channel = 0;
        peerInfo[i].encrypt = false;

        if (esp_now_add_peer(&peerInfo[i]) != ESP_OK) {
        Serial.println("Failed to add ESP");
        return;
        } else {
        Serial.println("Added ESP");
        }
    }
}
//--------------------Funcion enviar----------------------------------
void enviarMensaje(const uint8_t *MACAddr) {
    
    enviar.patron=patron[counter];
    enviar.color=BTmessage.color;

    esp_now_send(MACAddr, (uint8_t *) &enviar, sizeof(enviar));


}