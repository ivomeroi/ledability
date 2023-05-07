#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel tira = Adafruit_NeoPixel(49, 16, NEO_GRB + NEO_KHZ800);

void flechas(char direccion, int color){
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
        case 'u':
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

        case 'd':
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

        case 'r':
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
        case 'l':
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
    }
    
    };
