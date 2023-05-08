#ifndef ENVIAR_H
#define ENVIAR_H

#include <stdint.h>
//void readMac(bool isServer);

extern esp_now_peer_info_t peerInfo[3][6];

void peering();
void OnDataRecv(const uint8_t *macAddr, const uint8_t *incomingData, int len);

#endif // ENVIAR_H