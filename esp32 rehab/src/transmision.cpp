#include <WiFi.h>
#include <esp_now.h>
#include <cstring>

uint8_t allBroadcastAddresses[2][6] = {
        {0x0C, 0xB8, 0x15, 0xCB, 0xEE, 0x00},
        {0x0C, 0xB8, 0x15, 0xCB, 0xFF, 0x84},
    };

typedef struct var_struct {
  char direccion;
  int color;
} var_struct;
var_struct dupla;

void peering(uint8_t direcciones[][6]){
  // register peer
    esp_now_peer_info_t peer[2];

    for (int i = 0; i < 2; i++) {
        peer[i].channel = 0;  
        peer[i].encrypt = false;
        memcpy(peer[i].peer_addr, direcciones[i], 6);
        if (esp_now_add_peer(&peer[i]) != ESP_OK){
            Serial.println("Failed to add peer");
            return;
        }
    }
}

void sendpads(uint8_t direcciones[][6], var_struct dupla){
    // send data
    esp_err_t result = esp_now_send(direcciones[0], (uint8_t *) &dupla, sizeof(dupla));
    if (result == ESP_OK) {
        Serial.println("Sent with success");
    }
    else {
        Serial.println("Error sending the data");
    }
}