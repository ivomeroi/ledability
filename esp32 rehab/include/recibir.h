#ifndef RECIBIR_H
#define RECIBIR_H

#include <stdint.h>
typedef struct struct_message {
  int id;
  bool recibir;
} struct_message;

extern struct_message message;

extern struct_message esp2;
extern struct_message esp3;

extern struct_message boardsStruct[2];

void OnDataRecv(const uint8_t *macAddr, const uint8_t *incomingData, int len);

#endif // RECIBIR_H
