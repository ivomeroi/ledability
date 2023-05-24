#include <SoftwareSerial.h>
#include "hc05.h"
//-----------------Patrones-------------------------------------------

char numeros[10]={'e','f','g','h','i','j','k','l','m','n'}; //Números ascendentes 0 a 9
char flechas[4]={'a','b','c','d'}; // Flechas 
char circulos[1]={'p'}; //Circulo
char* patron; //Aca se guarda alguna de las siguientes secuencias de letras. Luego esto va a ser enviado a los ESPs slaves

//---------------------beginBT: Inicializar modulo BT de HC----------------------------------
void beginBT(int rx, int tx) {
    BTSerial.begin(9600); //tener en cuenta el BDrate
    SoftwareSerial BTSerial(rx, tx); // RX | TX
}
//-------------------readBT: leer información del HC-----------------------------------------
void readBT() { //leer el mensaje del HC
    while (BTSerial.available()) {
        char incomingByte = BTSerial.read(); //Guardar el incoming data
        if(isAlpha(incomingByte)){
            BTmessage.patron = incomingByte; //Guardar el patron
        } 
        if(isDigit(incomingByte)) {
            BTmessage.color = incomingByte; //Guardar el color
        } //isAlpha y isDigit leen el tipo de valor que entra. Si es un caracter es un patron, si es un numero es un color.       
    }
}
//-------------------writeBT: escribir información en el HC----------------------------------
void writeBT(int ID, char pat, int col) { //escribir el mensaje en el HC en función de la ID, patron y color
    BTSerial.write(ID); //enviar el ID
    BTSerial.write(pat); //enviar el patron
    BTSerial.write(col); //enviar el color
}
//--------------selectPatron: elijo la matriz para enviar----------------------------------------------
void selectPatron(){ //con la información del patrón, guardo la secuencia a mostrar en el programa
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
