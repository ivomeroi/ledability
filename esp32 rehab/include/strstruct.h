
//--------------------ESTRUCTURAS--------------------
typedef struct struct_message{
  char patron;
  int color;
} struct_message;

struct_message dupla;
struct_message myData;
//--------------------ESTRUCTURAS--------------------
typedef struct struct_bool{
  int id;
  bool state;
} struct_bool;

struct_bool estadoPad;

struct_bool pad1;
struct_bool pad2;
struct_bool pad3;

struct_bool boardpads[3]={pad1,pad2,pad3};

//--------------------ESTRUCTURAS--------------------
uint8_t allBroadcastAddresses[3][6] = {
        {0x0C, 0xB8, 0x15, 0xCB, 0xEE, 0x00},
        {0x0C, 0xB8, 0x15, 0xCB, 0xFF, 0x84},
        {0x0C, 0xB8, 0x15, 0xCB, 0xFA, 0x1C}
        //falta el 4to
    };
//-----Variable para determinar si es Master o Slave--------------------
bool isServer;