#ifndef ENVIAR_H
#define ENVIAR_H

#include <stdint.h>
//void readMac(bool isServer);


extern uint8_t broadcastAddress[3][6];

extern esp_now_peer_info_t peerInfo[2];

extern bool isServer; //Flag que indica si este ESP es el Master y le permite acceder a ciertas funciones 

void peering();
void OnDataRecv(const uint8_t *macAddr, const uint8_t *incomingData, int len);
void enviar();
void defineServer();


#endif // ENVIAR_H