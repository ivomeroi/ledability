#include <WiFi.h>
#include <esp_now.h>
#include <cstring>
#include "strstruct.h" 

//--------------------Funciones--------------------
//--Emparejar-- (ver si lo pongo en otro archivo)--
void peering(uint8_t direcciones[4][6]){

    // Init ESP-NOW - Peer
    esp_now_peer_info_t peer[3];
    //Leer su propia MAC
    WiFi.mode(WIFI_MODE_STA);
    uint8_t ownmac[6];
    esp_efuse_mac_get_default(ownmac);

    //Emparejar con los otros ESP32
    for (int i = 0; i < 3; i++) {
        if (ownmac[6]!=direcciones[i][6]){
            peer[i].channel = i;  //registro de un canal por cada direccion
            peer[i].encrypt = false; 
            memcpy(peer[i].peer_addr, direcciones[i], 6);
                if (esp_now_add_peer(&peer[i]) != ESP_OK){ //registro de cada direccion
                    Serial.println("Failed to add peer");
                    return;
                    }
        }
    }
}
//--Enviar-- (de server a otros ESP32)--------------------
void sendpads(uint8_t direcciones[3][6],struct_message dupla){
        // send data
    for(int i = 0; i < 3; i++){
        
        esp_err_t result = esp_now_send(direcciones[i], (uint8_t *) &dupla, sizeof(dupla));
        if (result == ESP_OK) {
            Serial.println("Sent with success");
        }
        else {
            Serial.println("Error sending the data");
        }
    }
}
