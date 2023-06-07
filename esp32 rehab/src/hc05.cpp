#include <SoftwareSerial.h>
#include "hc05.h"
#include <string>
#include <esp_now.h>
#include "enviar.h"
#include "counter.h"
#include "recibir.h"
//-----------------Patrones------------------------------------
char numeros[10]={'e','f','g','h','i','j','k','l','m','n'}; //Números ascendentes 0 a 9
char flechas[4]={'a','b','c','d'}; // Flechas
char circulos[1]={'o'}; //Circulo

//--------------selectPatron: elijo la matriz para enviar------

void listening_bt() {
  int simbolo;
  int color;
  if (BTSerial.available()) {
    delay(10);

    int messageInt = BTSerial.read(); // Read the character as an integer
    if(messageInt != -1) {
      
    }
    std::string message(2, static_cast<char>(messageInt)); // Convert integer to string    
    simbolo = message[0];
    color = message[1];

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



