#ifndef HC05_H
#define HC05_H

#include <stdint.h>
#include <SoftwareSerial.h>

typedef struct struct_BTmessage {
  char patron;
  int color;
} struct_BTmessage;

extern SoftwareSerial BTSerial; 
extern struct_BTmessage BTmessage;
extern char* patron;

extern char numeros[10];
extern char flechas[4];
extern char circulos[1];

void beginBT(int rx, int tx);
void readBT();
void writeBT(int ID, char pat, int col);
void selectPatron(struct_BTmessage mess);

#endif // HC05_H