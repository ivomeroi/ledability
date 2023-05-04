#ifndef _GLOBALES_H_
#define _GLOBALES_H_

#include <stdint.h>

typedef struct struct_message {
    int id;
    char patron;
    int color;
} struct_message;

typedef struct struct_bool {
    int id;
    bool state;
} struct_bool;



extern struct_message dupla;
extern struct_message board1;
extern struct_message boardsStruct[1];
extern struct_bool estadoPad;
extern struct_bool pad1;
extern struct_bool pad2;
extern struct_bool pad3;
extern struct_bool boardpads[3];
extern uint8_t allBroadcastAddresses[4][6];
extern uint8_t MACaddressServer[][6];
extern bool isServer;

#endif // _GLOBALES_H_
