// globals.cpp
#include "strstruct.h"
#include <stdint.h>
struct_message dupla;
struct_message myData;
struct_bool estadoPad;
struct_bool pad1;
struct_bool pad2;
struct_bool pad3;
struct_bool boardpads[3] = {pad1, pad2, pad3};

uint8_t allBroadcastAddresses[3][6] = {
    {0x0C, 0xB8, 0x15, 0xCB, 0xEE, 0x00},
    {0x0C, 0xB8, 0x15, 0xCB, 0xFF, 0x84},
    {0x0C, 0xB8, 0x15, 0xCB, 0xFA, 0x1C}
};

bool isServer;
