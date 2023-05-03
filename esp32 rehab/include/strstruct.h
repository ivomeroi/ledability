// strstruct.h
#ifndef _STRSTRUCT_H_
#define _STRSTRUCT_H_

#include <stdint.h>

typedef struct struct_message {
    char patron;
    int color;
} struct_message;

extern struct_message dupla;
extern struct_message myData;

typedef struct struct_bool {
    int id;
    bool state;
} struct_bool;

extern struct_bool estadoPad;
extern struct_bool pad1;
extern struct_bool pad2;
extern struct_bool pad3;
extern struct_bool boardpads[3];

extern uint8_t allBroadcastAddresses[3][6];
extern bool isServer;

#endif // _STRSTRUCT_H_
