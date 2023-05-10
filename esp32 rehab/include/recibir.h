#ifndef RECIBIR_H
#define RECIBIR_H

#include <stdint.h>
//---------------------------------------------------------------------------
typedef struct struct_message {
  char patron;
  int color;
} struct_message;

extern struct_message myData;
//---------------------------------------------------------------------------
void OnDataRecv(const uint8_t *macAddr, const uint8_t *incomingData, int len);

#endif // RECIBIR_H
