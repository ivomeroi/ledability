#include <WiFi.h>
#include <esp_now.h>
#include <cstring>
#include "enviar.h"
#include "recibir.h"
#include "sensor.h"
//--------------------Variables---------------------------------
esp_now_peer_info_t peerInfo;

uint8_t broadcastAddress[6]={0x0C,0xB8,0x15,0xCB,0xEE,0x00};
                            

//----------------Funciones peer---------------------------------
    void peering(){
        // Register peer
        memcpy(peerInfo.peer_addr,broadcastAddress, 6);
        peerInfo.channel = 0;  
        peerInfo.encrypt = false;
        // Add peer        
        if (esp_now_add_peer(&peerInfo) != ESP_OK){
            Serial.println("Failed to add ESP");
            return;
        } else{
            Serial.println("Added ESP");
    }
    }
//--------------------Funcion onDatasent-------------------------------

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

