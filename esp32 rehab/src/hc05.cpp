#include <SoftwareSerial.h>
#include "hc05.h"
//------------------------------------------------------------

char numeros[10]={'e','f','g','h','i','j','k','l','m','n'};
char flechas[4]={'a','b','c','d'};
char circulos[1]={'p'}; 
char* patron;

//---------------------beginBT: Inicializar modulo BT de HC---------------------------------------
void beginBT(int rx, int tx) {
    BTSerial.begin(9600);
    SoftwareSerial BTSerial(rx, tx); // RX | TX
}
//-------------------readBT: leer información del HC-----------------------------------------
void readBT() {
    while (BTSerial.available()) {
        char incomingByte = BTSerial.read();
        if(isAlpha(incomingByte)){
            BTmessage.patron = incomingByte;
        } 
        if(isDigit(incomingByte)) {
            BTmessage.color = incomingByte;
        }        
    }
}
//--------------selectPatron: elijo la matriz para enviar----------------------------------------------
void selectPatron(){
    switch (BTmessage.patron) {
        case 'n':
            patron=numeros;
            break;
        case 'f':
            patron=flechas;
            break;
        case 'c':
            patron=circulos;
            break;
    }
}
