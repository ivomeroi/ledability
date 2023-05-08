#include <WiFi.h>
#include <esp_now.h>
#include <cstring>
#include "enviar.h"
#include "recibir.h"

esp_now_peer_info_t peerInfo[2];

uint8_t broadcastAddress[3][6]={{0x0C,0xB8,0x15,0xCB,0xEE,0x00},
                                {0x0C,0xB8,0x15,0xCB,0xFF,0x84},
                                {0x0C,0xB8,0x15,0xCB,0xFA,0x1C}};

bool isServer; 

struct_message dataSlave;
//----------------Funciones peer---------------------------------
    void peering() {
    // Register peer
    uint8_t mac[6];
    WiFi.macAddress(mac);

    for (int i = 0; i < 2; i++) {
        if (memcmp(mac, broadcastAddress[i], 6) != 0) {
        memcpy(peerInfo[i].peer_addr, broadcastAddress[i], 6);
        peerInfo[i].channel = 0;
        peerInfo[i].encrypt = false;

        // Add peer
        if (esp_now_add_peer(&peerInfo[i]) != ESP_OK) {
            Serial.println("Failed to add peer");
            return;
        } else {
            Serial.println("Added peer");
        }
        }
    }
    }
//--------------------Funcion onDatasent-------------------------------

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
//--------------------Funcion defineServer------------------------------
void defineServer(){
    uint8_t mac[6];
    WiFi.macAddress(mac);
    if (mac[6]==broadcastAddress[0][6]){
        isServer = true;
    }
    else{
        isServer = false;
    }
}
//--------------------Funcion enviar-------------------------------------
void enviar(){
    if(isServer){
    for (int i = 0; i < 3; i++) {
        dataSlave.id = i;
        dataSlave.patron = random(97,112);
        dataSlave.color = random(0,2);
        esp_err_t result = esp_now_send(broadcastAddress[i+1], (uint8_t *) &dataSlave, sizeof(dataSlave));

        }
    }
}