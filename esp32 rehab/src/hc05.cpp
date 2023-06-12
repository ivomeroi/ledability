#include <SoftwareSerial.h>
#include "hc05.h"
#include <string>
#include <esp_now.h>
#include "enviar.h"
#include "counter.h"
#include "recibir.h"
//-----------------Patrones------------------------------------
char numeros1[]="efghijklmn"; //Números ascendentes 0 a 9
char numeros2[]="nmlkjihgfe"; //Números descendentes 9 a 0
char flechas[]="abcd"; // Flechas
char circulos[] ="o"; //Circulo
char stop[]="p"; //Stop
char inicio[]="x"; //Inicio
char pausa[]="z"; //Patron
bool randomValue;
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

    // -------------Secuencias---------------
    if (simbolo == 112){
      patron = stop;
      isSensorDetectionPaused = false;
    }  
    else if (simbolo == 102) {
      patron = flechas;
    }
    else if (simbolo == 110) {
      patron = numeros1;
    }
    else if (simbolo == 111) {
      patron = numeros2;
    }
    else if (simbolo == 99) {
      patron = circulos;
    }
    else if (simbolo == 113){
      patron = numeros1;
      randomValue = true;
    }
    //   -------------Colores----------------
    if (color == 48) { // ASCII 48 = 0 Rojo
      BTmessage.color = 0;
    }
    else if (color == 49) { // ASCII 49 = 1 Verde
      BTmessage.color = 1;
    }
    else if (color == 50) { // ASCII 50 = 2 Azul
      BTmessage.color = 2;
    }
    else if (color == 51) {
      BTmessage.color = 3;  // ASCII 51 = 3 Amarillo
    }
    else if (color == 52){
      BTmessage.color = 4; // ASCII 52 = 4  Random
    }
    else if (color == 53){
      BTmessage.color = 5; // ASCII 52 = 4  Random
    }
    else if (color == 54){
      BTmessage.color = 6; // ASCII 52 = 4  Random
    }
    if (simbolo == 89) { // ASCII 89 = 'Y'
      isSensorDetectionPaused = !isSensorDetectionPaused; // Toggle the pause state
      char pause = 'Y';
      for (int i = 0; i < 3; i++) {
        esp_now_send(broadcastAddress[i], (uint8_t *)&pause, sizeof(pause));
      }
    } else{
      counter=0;
    }
  }
}



