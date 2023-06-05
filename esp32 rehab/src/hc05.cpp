#include <SoftwareSerial.h>
#include "hc05.h"
//-----------------Patrones------------------------------------
char numeros[10]={'e','f','g','h','i','j','k','l','m','n'}; //Números ascendentes 0 a 9
char flechas[4]={'a','b','c','d'}; // Flechas
char circulos[1]={'o'}; //Circulo
char* patron; //Patron a enviar

//--------------selectPatron: elijo la matriz para enviar------
void listening_bt() {
  if (BTSerial.available()) {
    delay(10);
    char message = BTSerial.read();
    if (message == 'n') {
      patron = numeros;
    } else if (message == 'f') {
      patron = flechas;
    } else if (message == 'c') {
      patron = circulos;
    } else if (message == '0'){
      BTmessage.color=0;
    } else if (message == '1'){
      BTmessage.color=1;
    } else if (message == '2'){
      BTmessage.color=2;
    } else if (message == '3'){
      BTmessage.color=random(0,3);
    }
  }
}

//------------writeBT: escribir información en el HC-----------
void writeBT(int ID, char pat, int col) { //escribir el mensaje en el HC en función de la ID, patron y color
    Serial.write(ID); //enviar el ID
    Serial.write(pat); //enviar el patron
    Serial.write(col); //enviar el color
    Serial.print('\n');
}
