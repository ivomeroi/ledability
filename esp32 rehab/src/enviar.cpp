#include <WiFi.h>
#include <esp_now.h>
#include <cstring>
#include "enviar.h"
#include <cstdint>
#include <macaddresses.h>
esp_now_peer_info_t peerInfo[3][6];

uint8_t MAC1[6]={0x0C,0xB8,0x15,0xCB,0xEE,0x00};
uint8_t MAC2[6]={0x0C,0xB8,0x15,0xCB,0xFF,0x84};
uint8_t MAC3[6]={0x0C,0xB8,0x15,0xCB,0xFA,0x1C};
uint8_t UNIVm[6]={0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

struct_message3 MatrixMac[3]={{MAC2[6]},{MAC3[6]},{UNIVm[6]}};   ///son para peering que hace el master

//----------------Funciones-------------------------------------------
void peering(){
    // Register peer
    memset(peerInfo, 0, sizeof(peerInfo));
    peerInfo[0][0].channel = 0;
    peerInfo[0][0].encrypt = false;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 6; j++) {
        // Copy the MAC address from MatrixMac to peerInfo
        peerInfo[i][j].peer_addr[j] = MatrixMac[i].mac[j];
    }
        peerInfo[i][0].channel = peerInfo[0][0].channel;
        peerInfo[i][0].encrypt = peerInfo[0][0].encrypt;
        if (esp_now_add_peer(&peerInfo[i][0]) != ESP_OK){
            Serial.printf("Failed to add ESP32 - %u", i);
            return;
    } else{
        Serial.printf("Added ESP32 - %u", i);
    }
    }
}
//hola
//--------------------Funcion onDatasent------------------------------

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}