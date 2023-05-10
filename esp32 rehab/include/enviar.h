#ifndef ENVIAR_H
#define ENVIAR_H

#include <stdint.h>


typedef struct struct_send {
  char patron;  
  int color;
} struct_send;

extern struct_send enviar;

extern uint8_t broadcastAddress[2][6];

extern esp_now_peer_info_t peerInfo[2];

void peering();

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);

void enviarMensaje();

#endif // ENVIAR_H