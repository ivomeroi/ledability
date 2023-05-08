#include <WiFi.h>
#include <esp_now.h>
#include <cstring>
#include "enviar.h"
#include "recibir.h"

//--------------------Variables---------------------------------
esp_now_peer_info_t peerInfo[2];

uint8_t broadcastAddress[2][6]={
    {0x0C,0xB8,0x15,0xCB,0xFF,0x84},
    {0x0C,0xB8,0x15,0xCB,0xFA,0x1C}
};

//----------------Funciones peer---------------------------------
    void peering() {
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
//--------------------Funcion onDatasent-------------------------------

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

