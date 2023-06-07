#ifndef COUNTER_H
#define COUNTER_H


extern int counter;
extern char* patron;

typedef struct struct_send {
  char patron;  
  int color;
} struct_send;

extern struct_send enviar;

typedef struct struct_message {
  int id;
  bool recibir; //es el valor de interact del ESP slave
} struct_message;

extern struct_message message;

extern struct_message esp2;
extern struct_message esp3;
extern struct_message esp4;

extern struct_message boardsStruct[3];

typedef struct struct_BTmessage {
  char patron;
  int color;
} struct_BTmessage;

extern struct_BTmessage BTmessage;

void writeBT(int ID, char pat, int col);

#endif