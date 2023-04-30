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
    esp_now_peer_info_t peerInfo;
    peerInfo.channel = 0;  
    peerInfo.encrypt = false;
    
    for (int i = 0; i < 2; i++) {
        memcpy(peerInfo.peer_addr, direcciones[i], 6);
    }
}
