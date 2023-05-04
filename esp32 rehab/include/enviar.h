#ifndef _ENVIAR_H_
#define _ENVIAR_H_

#include "globales.h"

void peering(uint8_t direcciones[4][6]);
void sendpads(uint8_t direcciones[4][6],struct_message);

#endif