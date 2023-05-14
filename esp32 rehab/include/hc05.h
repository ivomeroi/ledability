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
extern int counter;

void beginBT(int rx, int tx);
void readBT();

#endif // HC05_H