#ifndef ENVIAR_H
#define ENVIAR_H

#include <esp_now.h>
#include <stdint.h>



extern uint8_t broadcastAddress[3][6];

extern esp_now_peer_info_t peerInfo[3];



void peering();

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);

int checkID(const uint8_t *MACAddr);

void enviarMensaje(const uint8_t *MACAddr);



#endif // ENVIAR_H