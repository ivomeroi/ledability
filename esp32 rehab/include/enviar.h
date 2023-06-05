#ifndef ENVIAR_H
#define ENVIAR_H

#include <stdint.h>

//---------------------------------------------------------------------------
typedef struct struct_message_to_master {
    int  id;
    bool interact; //el bool interact reemplaza al recibido. 
} struct_message_to_master;

extern struct_message_to_master toMaster;
//---------------------------------------------------------------------------
extern uint8_t broadcastAddressMaster[6];

extern uint8_t slaveMACS[3][6];

extern esp_now_peer_info_t peerInfo;
//---------------------------------------------------------------------------
void peering();
void OnDataRecv(const uint8_t *macAddr, const uint8_t *incomingData, int len);
void enviar();
void defID();


#endif // ENVIAR_H