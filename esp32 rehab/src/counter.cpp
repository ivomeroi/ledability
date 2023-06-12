#include "counter.h"
#include <SoftwareSerial.h>

int counter;
int color_counter;
char* patron;
bool isSensorDetectionPaused = false;

SoftwareSerial BTSerial(3);

struct_send enviar; // estructura de datos que contiene el patron y el color

struct_BTmessage BTmessage;

struct_message message;

struct_message esp2;
struct_message esp3;
struct_message esp4;

struct_message boardsStruct[3]={esp2,esp3,esp4}; //Creo una subestructura de la estructura boardsStruct para cada ESP slave

//------------writeBT: escribir información en el HC-----------
void writeBT(int ID, char pat, int col) {
    std::string data = std::to_string(ID) + pat + std::to_string(col); // Concatenate the values into a string
    BTSerial.println(data.c_str()); // Send the string with a newline character
    Serial.println(data.c_str());
}
