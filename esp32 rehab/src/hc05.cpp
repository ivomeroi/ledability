#include <SoftwareSerial.h>
#include "hc05.h"
#include <string>
//-----------------Patrones------------------------------------
char numeros[10]={'e','f','g','h','i','j','k','l','m','n'}; //Números ascendentes 0 a 9
char flechas[4]={'a','b','c','d'}; // Flechas
char circulos[1]={'o'}; //Circulo
char* patron; //Patron a enviar

//--------------selectPatron: elijo la matriz para enviar------
void listening_bt(){
  if (BTSerial.available()) {
    delay(10);

    int messageInt = BTSerial.read(); // Read the character as an integer
    Serial.println(messageInt);
    std::string message(1, static_cast<char>(messageInt)); // Convert integer to string    
    char simbolo=message[0];
    if (simbolo=='102'){
      patron=flechas;
      Serial.println("flechas");
    }
    else if (simbolo=='n'){
      patron=numeros;
      Serial.println("numeros");
    }
    else if (simbolo=='c'){
      patron=circulos;
      Serial.println("circulos");
    }
    else{
      patron=flechas;
    }
    if(message[1]=='48'){ // ASCII 48 = 0
      BTmessage.color=1;
      Serial.println("color 1");
    }
    else if(message[1]=='49'){ // ASCII 49 = 1
      BTmessage.color=2;
      Serial.println("color 2");
    }
    else if(message[1]=='50'){ // ASCII 50 = 2
      BTmessage.color=3;
      Serial.println("color 3");
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
