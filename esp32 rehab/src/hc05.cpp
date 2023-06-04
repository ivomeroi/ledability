#include <SoftwareSerial.h>
#include "hc05.h"
//-----------------Patrones-------------------------------------------

char numeros[10]={'e','f','g','h','i','j','k','l','m','n'}; //Números ascendentes 0 a 9
char flechas[4]={'a','b','c','d'}; // Flechas
char circulos[1]={'p'}; //Circulo
char* patron; //Aca se guarda alguna de las siguientes secuencias de letras. Luego esto va a ser enviado a los ESPs slaves

//---------------------beginBT: Inicializar modulo BT de HC----------------------------------
void beginBT(int rx, int tx) {
  SoftwareSerial BTSerial(rx, tx); // RX | TX
  delay(500);
    Serial.println("BT connected");

    BTSerial.write(random(0, 100));
    delay(100);
    Serial.println(random(0, 100));
    delay(1000);
    Serial.println(random(0, 100));
    delay(1000);
    Serial.println(random(0, 100));
    delay(1000);
    Serial.println(random(0, 100));
  }
//--------------selectPatron: elijo la matriz para enviar----------------------------------------------
void selectPatron(char message){ //con la información del patrón, guardo la secuencia a mostrar en el programa
    //Con la información del patron, guardo la secuencia a enviar
    switch (message) {
        case 'n':
        Serial.println("n");
            //patron=numeros;
            break;
        case 'f':
        Serial.println("f");
            //patron=flechas;
            break;
        case 'c':
        Serial.println("c");
            //patron=circulos;
            break;
    }   
    //Con la información del color, guardo el valor a enviar
    // //* switch (message.color) {
    //     case 'r':
    //         message.color=0;
    //         break;
    //     case 'g':
    //         message.color=1;
    //         break;
    //     case 'b':
    //         message.color=2;
    //         break;
    // } 
    // * //
}
//-------------------readBT: leer información del HC-----------------------------------------
// void readBT() { //leer el mensaje del HC
//     while (BTSerial.available()) {
//         char incomingByte = BTSerial.read(); //Guardar el incoming data
//         if(isAlpha(incomingByte)){
//             BTmessage.patron = incomingByte; //Guardar el patron
//         } 
//         if(isDigit(incomingByte)) {
//             BTmessage.color = incomingByte; //Guardar el color
//             break;
//         } //isAlpha y isDigit leen el tipo de valor que entra. Si es un caracter es un patron, si es un numero es un color.   
//     }
//     selectPatron(BTmessage); //Seleccionar el patron a enviar
// }
//-------------------writeBT: escribir información en el HC----------------------------------
// void writeBT(int ID, char pat, int col) { //escribir el mensaje en el HC en función de la ID, patron y color
//     BTSerial.write(ID); //enviar el ID
//     BTSerial.write(pat); //enviar el patron
//     BTSerial.write(col); //enviar el color
// }
