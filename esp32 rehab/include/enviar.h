#ifndef ENVIAR_H
#define ENVIAR_H

#include <stdint.h>
//void readMac(bool isServer);


extern uint8_t broadcastAddress[2][6];

extern esp_now_peer_info_t peerInfo[2];

void peering();

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);

#endif // ENVIAR_H