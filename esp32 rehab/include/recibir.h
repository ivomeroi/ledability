#ifndef RECIBIR_H
#define RECIBIR_H

#include <stdint.h>




void OnDataRecv(const uint8_t *macAddr, const uint8_t *incomingData, int len);

#endif // RECIBIR_H
