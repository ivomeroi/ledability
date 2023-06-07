// Sirve para configurar los leds de la tira de neopixel, en otro archivo configuro cómo sería en patrones.

#include <Adafruit_NeoPixel.h>
#include "sensor.h"

Adafruit_NeoPixel tira = Adafruit_NeoPixel(49, 16, NEO_GRB + NEO_KHZ800);

#include <Adafruit_NeoPixel.h>
//Patrones contiene los patrones de la tira. Con el char selecciono qué patron mostrar y con el int el color en RGB.
void patrones(char direccion, int color){
    int r, g, b; 

    if (color == 0){
        r=255;
        g=0;
        b=0;
    } else if(color==1) {
        r=0;
        g=255;
        b=0;
    }  else if(color==2){
        r=0;
        g=0;
        b=255;
    }
    tira.begin();
    switch(direccion){
        case 0:
            //ARRIBA
            tira.clear();
            tira.setPixelColor(3, r, g, b);
            tira.setPixelColor(9, r, g, b);
            tira.setPixelColor(10, r, g, b);
            tira.setPixelColor(11, r, g, b);
            tira.setPixelColor(15, r, g, b);
            tira.setPixelColor(17, r, g, b);
            tira.setPixelColor(19, r, g, b);
            tira.setPixelColor(21, r, g, b);
            tira.setPixelColor(24, r, g, b);
            tira.setPixelColor(27, r, g, b);
            tira.setPixelColor(31, r, g, b);
            tira.setPixelColor(38, r, g, b);
            tira.setPixelColor(45, r, g, b);
            tira.show();
            break;

        case 1:
            //ABAJO
            tira.clear();
            tira.setPixelColor(3, r, g, b);
            tira.setPixelColor(10, r, g, b);
            tira.setPixelColor(17, r, g, b);
            tira.setPixelColor(21, r, g, b);
            tira.setPixelColor(24, r, g, b);
            tira.setPixelColor(27, r, g, b);
            tira.setPixelColor(29, r, g, b);
            tira.setPixelColor(31, r, g, b);
            tira.setPixelColor(33, r, g, b);
            tira.setPixelColor(37, r, g, b);
            tira.setPixelColor(38, r, g, b);
            tira.setPixelColor(39, r, g, b);
            tira.setPixelColor(45, r, g, b);
            tira.show();
            break;

        case 2:
            //DERECHA
            tira.clear();
            tira.setPixelColor(3, r, g, b);
            tira.setPixelColor(9, r, g, b);
            tira.setPixelColor(19, r, g, b);
            tira.setPixelColor(21, r, g, b);
            tira.setPixelColor(22, r, g, b);
            tira.setPixelColor(23, r, g, b);
            tira.setPixelColor(24, r, g, b);
            tira.setPixelColor(25, r, g, b);
            tira.setPixelColor(26, r, g, b);
            tira.setPixelColor(27, r, g, b);
            tira.setPixelColor(33, r, g, b);
            tira.setPixelColor(37, r, g, b);
            tira.setPixelColor(45, r, g, b);            
            tira.show();
            break;
        case 3:
            //IZQUIERDA
            tira.clear();
            tira.setPixelColor(3, r, g, b);
            tira.setPixelColor(11, r, g, b);
            tira.setPixelColor(15, r, g, b);
            tira.setPixelColor(21, r, g, b);
            tira.setPixelColor(22, r, g, b);
            tira.setPixelColor(23, r, g, b);
            tira.setPixelColor(24, r, g, b);
            tira.setPixelColor(25, r, g, b);
            tira.setPixelColor(26, r, g, b);
            tira.setPixelColor(27, r, g, b);
            tira.setPixelColor(29, r, g, b);
            tira.setPixelColor(39, r, g, b);
            tira.setPixelColor(45, r, g, b);            
            tira.show();
            break;
        case 4:
            //UNO
            tira.clear();
            tira.setPixelColor(3, r, g, b);
            tira.setPixelColor(4, r, g, b);
            tira.setPixelColor(9, r, g, b);
            tira.setPixelColor(10, r, g, b);
            tira.setPixelColor(11, r, g, b);
            tira.setPixelColor(15, r, g, b);
            tira.setPixelColor(17, r, g, b);
            tira.setPixelColor(18, r, g, b);
            tira.setPixelColor(23, r, g, b);
            tira.setPixelColor(24, r, g, b);
            tira.setPixelColor(31, r, g, b);
            tira.setPixelColor(37, r, g, b);
            tira.setPixelColor(38, r, g, b);
            tira.setPixelColor(44, r, g, b);
            tira.setPixelColor(45, r, g, b);
            tira.setPixelColor(46, r, g, b);  
            tira.setPixelColor(47, r, g, b);         
            tira.show();
            break;
        case 5:
            //DOS
            tira.clear();
            tira.setPixelColor(2, r, g, b);
            tira.setPixelColor(3, r, g, b);
            tira.setPixelColor(4, r, g, b);
            tira.setPixelColor(8, r, g, b);
            tira.setPixelColor(9, r, g, b);
            tira.setPixelColor(11, r, g, b);
            tira.setPixelColor(12, r, g, b);
            tira.setPixelColor(18, r, g, b);
            tira.setPixelColor(19, r, g, b);
            tira.setPixelColor(23, r, g, b);
            tira.setPixelColor(24, r, g, b);
            tira.setPixelColor(30, r, g, b);
            tira.setPixelColor(31, r, g, b);
            tira.setPixelColor(37, r, g, b);
            tira.setPixelColor(40, r, g, b);
            tira.setPixelColor(43, r, g, b);
            tira.setPixelColor(44, r, g, b);
            tira.setPixelColor(45, r, g, b);
            tira.setPixelColor(46, r, g, b); 
            tira.setPixelColor(47, r, g, b);       
            tira.show();
            break;
        case 6:
            //TRES
            tira.clear();
            tira.setPixelColor(1, r, g, b);
            tira.setPixelColor(2, r, g, b);
            tira.setPixelColor(3, r, g, b);
            tira.setPixelColor(4, r, g, b);
            tira.setPixelColor(8, r, g, b);
            tira.setPixelColor(9, r, g, b);
            tira.setPixelColor(18, r, g, b);
            tira.setPixelColor(19, r, g, b);
            tira.setPixelColor(23, r, g, b);
            tira.setPixelColor(24, r, g, b);
            tira.setPixelColor(25, r, g, b);
            tira.setPixelColor(32, r, g, b);
            tira.setPixelColor(33, r, g, b);
            tira.setPixelColor(36, r, g, b);
            tira.setPixelColor(37, r, g, b);
            tira.setPixelColor(43, r, g, b);
            tira.setPixelColor(44, r, g, b);
            tira.setPixelColor(45, r, g, b);
            tira.setPixelColor(46, r, g, b);       
            tira.show();
            break;  
        case 7:
            //CUATRO
            tira.clear();
            tira.setPixelColor(4, r, g, b);
            tira.setPixelColor(5, r, g, b);
            tira.setPixelColor(8, r, g, b);
            tira.setPixelColor(9, r, g, b);
            tira.setPixelColor(10, r, g, b);
            tira.setPixelColor(16, r, g, b);
            tira.setPixelColor(18, r, g, b);
            tira.setPixelColor(19, r, g, b);
            tira.setPixelColor(22, r, g, b);
            tira.setPixelColor(23, r, g, b);
            tira.setPixelColor(26, r, g, b);
            tira.setPixelColor(29, r, g, b);
            tira.setPixelColor(30, r, g, b);
            tira.setPixelColor(31, r, g, b);
            tira.setPixelColor(32, r, g, b);
            tira.setPixelColor(33, r, g, b);
            tira.setPixelColor(36, r, g, b);
            tira.setPixelColor(37, r, g, b);
            tira.setPixelColor(45, r, g, b);
            tira.setPixelColor(46, r, g, b);
            tira.setPixelColor(47, r, g, b);
            tira.show();
            break; 
        case 8:
            //CINCO
            tira.clear();
            tira.setPixelColor(1, r, g, b);
            tira.setPixelColor(2, r, g, b);
            tira.setPixelColor(3, r, g, b);
            tira.setPixelColor(4, r, g, b);
            tira.setPixelColor(5, r, g, b);
            tira.setPixelColor(11, r, g, b);
            tira.setPixelColor(12, r, g, b);
            tira.setPixelColor(15, r, g, b);
            tira.setPixelColor(16, r, g, b);
            tira.setPixelColor(17, r, g, b);
            tira.setPixelColor(18, r, g, b);
            tira.setPixelColor(22, r, g, b);
            tira.setPixelColor(23, r, g, b);
            tira.setPixelColor(32, r, g, b);  
            tira.setPixelColor(33, r, g, b);
            tira.setPixelColor(36, r, g, b);
            tira.setPixelColor(37, r, g, b);
            tira.setPixelColor(39, r, g, b);
            tira.setPixelColor(40, r, g, b);
            tira.setPixelColor(44, r, g, b);
            tira.setPixelColor(45, r, g, b);
            tira.setPixelColor(46, r, g, b);
            tira.show();
            break;
        case 9:
            //SEIS
            tira.clear();
            tira.setPixelColor(2, r, g, b);
            tira.setPixelColor(3, r, g, b);
            tira.setPixelColor(4, r, g, b);
            tira.setPixelColor(5, r, g, b);
            tira.setPixelColor(11, r, g, b);
            tira.setPixelColor(12, r, g, b);
            tira.setPixelColor(15, r, g, b);
            tira.setPixelColor(16, r, g, b);
            tira.setPixelColor(22, r, g, b);
            tira.setPixelColor(23, r, g, b);
            tira.setPixelColor(24, r, g, b);
            tira.setPixelColor(25, r, g, b);
            tira.setPixelColor(26, r, g, b);
            tira.setPixelColor(29, r, g, b);
            tira.setPixelColor(30, r, g, b);
            tira.setPixelColor(32, r, g, b);
            tira.setPixelColor(33, r, g, b);
            tira.setPixelColor(36, r, g, b);
            tira.setPixelColor(37, r, g, b);
            tira.setPixelColor(39, r, g, b);
            tira.setPixelColor(40, r, g, b); 
            tira.setPixelColor(44, r, g, b);
            tira.setPixelColor(45, r, g, b); 
            tira.setPixelColor(46, r, g, b);   
            tira.show();
            break;
        case 10:
            //Siete
            tira.clear();
            tira.setPixelColor(1, r, g, b);
            tira.setPixelColor(2, r, g, b);
            tira.setPixelColor(3, r, g, b);
            tira.setPixelColor(4, r, g, b);
            tira.setPixelColor(5, r, g, b);
            tira.setPixelColor(8, r, g, b);
            tira.setPixelColor(9, r, g, b);
            tira.setPixelColor(12, r, g, b);
            tira.setPixelColor(16, r, g, b);
            tira.setPixelColor(23, r, g, b);
            tira.setPixelColor(24, r, g, b);
            tira.setPixelColor(25, r, g, b);
            tira.setPixelColor(30, r, g, b);
            tira.setPixelColor(32, r, g, b);
            tira.setPixelColor(37, r, g, b);
            tira.setPixelColor(39, r, g, b); 
            tira.setPixelColor(44, r, g, b);
            tira.setPixelColor(45, r, g, b); 
            tira.setPixelColor(46, r, g, b);   
            tira.show();
            break;
        case 11:
            //OCHO
            tira.clear();
            tira.setPixelColor(2, r, g, b);
            tira.setPixelColor(3, r, g, b);
            tira.setPixelColor(4, r, g, b);
            tira.setPixelColor(8, r, g, b);
            tira.setPixelColor(9, r, g, b);
            tira.setPixelColor(11, r, g, b);
            tira.setPixelColor(12, r, g, b);
            tira.setPixelColor(15, r, g, b);
            tira.setPixelColor(16, r, g, b);
            tira.setPixelColor(18, r, g, b);
            tira.setPixelColor(19, r, g, b);
            tira.setPixelColor(23, r, g, b);
            tira.setPixelColor(24, r, g, b);
            tira.setPixelColor(25, r, g, b);
            tira.setPixelColor(29, r, g, b);
            tira.setPixelColor(30, r, g, b);
            tira.setPixelColor(32, r, g, b);
            tira.setPixelColor(33, r, g, b);
            tira.setPixelColor(36, r, g, b);
            tira.setPixelColor(37, r, g, b);
            tira.setPixelColor(39, r, g, b);
            tira.setPixelColor(40, r, g, b);
            tira.setPixelColor(44, r, g, b);
            tira.setPixelColor(45, r, g, b);
            tira.setPixelColor(46, r, g, b);
            tira.show();
            break;  
        case 12:
            //NUEVE
            tira.clear();
            tira.setPixelColor(2, r, g, b);
            tira.setPixelColor(3, r, g, b);
            tira.setPixelColor(4, r, g, b);
            tira.setPixelColor(8, r, g, b);
            tira.setPixelColor(9, r, g, b);
            tira.setPixelColor(11, r, g, b);
            tira.setPixelColor(12, r, g, b);
            tira.setPixelColor(15, r, g, b);
            tira.setPixelColor(16, r, g, b);
            tira.setPixelColor(18, r, g, b);
            tira.setPixelColor(19, r, g, b);
            tira.setPixelColor(22, r, g, b);    
            tira.setPixelColor(23, r, g, b);
            tira.setPixelColor(24, r, g, b);
            tira.setPixelColor(25, r, g, b);
            tira.setPixelColor(26, r, g, b);
            tira.setPixelColor(32, r, g, b); 
            tira.setPixelColor(33, r, g, b);
            tira.setPixelColor(36, r, g, b);
            tira.setPixelColor(37, r, g, b);
            tira.setPixelColor(44, r, g, b);
            tira.setPixelColor(45, r, g, b); 
            tira.setPixelColor(46, r, g, b);
            tira.show();
            break;     
        case 13:
            //CERO
            tira.clear();
            tira.setPixelColor(2, r, g, b);
            tira.setPixelColor(3, r, g, b);
            tira.setPixelColor(4, r, g, b);
            tira.setPixelColor(8, r, g, b);
            tira.setPixelColor(9, r, g, b);
            tira.setPixelColor(11, r, g, b);
            tira.setPixelColor(12, r, g, b);
            tira.setPixelColor(15, r, g, b);
            tira.setPixelColor(19, r, g, b);
            tira.setPixelColor(22, r, g, b);
            tira.setPixelColor(26, r, g, b);
            tira.setPixelColor(29, r, g, b);
            tira.setPixelColor(33, r, g, b);
            tira.setPixelColor(36, r, g, b);
            tira.setPixelColor(37, r, g, b);
            tira.setPixelColor(39, r, g, b);
            tira.setPixelColor(40, r, g, b);
            tira.setPixelColor(44, r, g, b);
            tira.setPixelColor(45, r, g, b);
            tira.setPixelColor(46, r, g, b);
            tira.show();

            break; 
        case 14:
            //CIRCULOS
            tira.clear();
            tira.setPixelColor(2, r, g, b);
            tira.setPixelColor(3, r, g, b);
            tira.setPixelColor(4, r, g, b);
            tira.setPixelColor(8, r, g, b);
            tira.setPixelColor(9, r, g, b);
            tira.setPixelColor(10, r, g, b);
            tira.setPixelColor(11, r, g, b);
            tira.setPixelColor(12, r, g, b);
            tira.setPixelColor(14, r, g, b);
            tira.setPixelColor(15, r, g, b);
            tira.setPixelColor(16, r, g, b);
            tira.setPixelColor(17, r, g, b);
            tira.setPixelColor(18, r, g, b);
            tira.setPixelColor(19, r, g, b);
            tira.setPixelColor(20, r, g, b);
            tira.setPixelColor(21, r, g, b);
            tira.setPixelColor(22, r, g, b);
            tira.setPixelColor(23, r, g, b);
            tira.setPixelColor(24, r, g, b);
            tira.setPixelColor(25, r, g, b);
            tira.setPixelColor(26, r, g, b);
            tira.setPixelColor(27, r, g, b);
            tira.setPixelColor(28, r, g, b);
            tira.setPixelColor(29, r, g, b);
            tira.setPixelColor(30, r, g, b);
            tira.setPixelColor(31, r, g, b);
            tira.setPixelColor(32, r, g, b);
            tira.setPixelColor(33, r, g, b);
            tira.setPixelColor(34, r, g, b);
            tira.setPixelColor(36, r, g, b); 
            tira.setPixelColor(37, r, g, b);
            tira.setPixelColor(38, r, g, b);
            tira.setPixelColor(39, r, g, b); 
            tira.setPixelColor(40, r, g, b);
            tira.setPixelColor(44, r, g, b); 
            tira.setPixelColor(45, r, g, b); 
            tira.setPixelColor(46, r, g, b);   
            tira.show();
            break; 
    }
}