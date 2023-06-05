#ifndef ENVIAR_H
#define ENVIAR_H

#include <stdint.h>


typedef struct struct_send {
  char patron;  
  int color;
} struct_send;

extern struct_send enviar;

extern uint8_t broadcastAddress[3][6];

extern esp_now_peer_info_t peerInfo[3];

void peering();

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);

void checkID(const uint8_t *MACAddr);

void enviarMensaje(const uint8_t *MACAddr);



#endif // ENVIAR_H