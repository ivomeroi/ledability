#include <SoftwareSerial.h>
#include "hc05.h"
#include <string>
#include "enviar.h"
//-----------------Patrones------------------------------------
char numeros[10]={'e','f','g','h','i','j','k','l','m','n'}; //Números ascendentes 0 a 9
char flechas[4]={'a','b','c','d'}; // Flechas
char circulos[1]={'o'}; //Circulo
char* patron; //Patron a enviar

//--------------selectPatron: elijo la matriz para enviar------

void listening_bt() {
  if (BTSerial.available()) {
    delay(10);

    int messageInt = BTSerial.read(); // Read the character as an integer
    std::string message(2, static_cast<char>(messageInt)); // Convert integer to string    
    int simbolo = message[0];
    int color = message[1];

    if (simbolo == 102) {
      patron = flechas;
    }
    else if (simbolo == 110) {
      patron = numeros;
    }
    else if (simbolo == 99) {
      patron = circulos;
    }
    else {
      patron = flechas;
    }
    if (color == 48) { // ASCII 48 = 0
      BTmessage.color = 0;
    }
    else if (color == 49) { // ASCII 49 = 1
      BTmessage.color = 1;
    }
    else if (color == 50) { // ASCII 50 = 2
      BTmessage.color = 2;
    }
    else if (color == 51) {
      BTmessage.color = 3;
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
