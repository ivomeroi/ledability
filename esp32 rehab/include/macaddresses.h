#ifndef MAC_ADDRESSES_H
#define MAC_ADDRESSES_H

#include <cstdint>

extern uint8_t UNIV[6];
extern uint8_t MAC1[6];
extern uint8_t MAC2[6];
extern uint8_t MAC3[6];

typedef struct struct_message3 {
    uint8_t mac[6];
} struct_message3;

extern struct_message3 MatrixMac[3];




#endif