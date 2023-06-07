#include "counter.h"
#include <SoftwareSerial.h>

int counter;
char* patron;

struct_send enviar; // estructura de datos que contiene el patron y el color

struct_BTmessage BTmessage;

struct_message message;

struct_message esp2;
struct_message esp3;
struct_message esp4;

struct_message boardsStruct[3]={esp2,esp3,esp4}; //Creo una subestructura de la estructura boardsStruct para cada ESP slave

//------------writeBT: escribir información en el HC-----------
void writeBT(int ID, char pat, int col) { //escribir el mensaje en el HC en función de la ID, patron y color
    Serial.write(ID); //enviar el ID
    Serial.write(pat); //enviar el patron
    Serial.write(col); //enviar el color
    Serial.print('\n');
}