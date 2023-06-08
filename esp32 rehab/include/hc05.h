#ifndef HC05_H
#define HC05_H

#include <stdint.h>
#include <SoftwareSerial.h>



extern SoftwareSerial BTSerial; 

extern char numeros[];
extern char flechas[];
extern char circulos[];
extern char stop[];

void listening_bt();
void readBT();
void selectPatron(char message);


#endif // HC05_H