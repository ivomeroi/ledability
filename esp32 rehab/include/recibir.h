#ifndef RECIBIR_H
#define RECIBIR_H

#include <stdint.h>
//void readMac(bool isServer);
typedef struct struct_message {
  int id;
  char patron;
  int color;
} struct_message;

extern struct_message myData;

extern struct_message dataSlave;

extern bool recibido;
void OnDataRecv(const uint8_t *macAddr, const uint8_t *incomingData, int len);

#endif // RECIBIR_H
