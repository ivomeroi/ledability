#include <Adafruit_NeoPixel.h>

void flechas(char direccion, int color, Adafruit_NeoPixel tira){
    int r, g, b; 

    if (color = 0){
        r=255;
        g=0;
        b=0;
    } else if(color=1) {
        r=0;
        g=255;
        b=0;
    }  else if(color=2){
        r=0;
        g=0;
        b=255;
    }
    tira.setBrightness(20);
    tira.begin();
    switch(direccion){
        case 'u':
            //ARRIBA
            tira.clear();
            tira.setPixelColor(3,r,g,b);// posicion (0,R G B)
            tira.setPixelColor(9,r,g,b);// posicion (0,R G B)
            tira.setPixelColor(10,r,g,b);// posicion (0,R G B)
            tira.setPixelColor(11,r,g,b);// posicion (0,R G B)
            tira.setPixelColor(15,r,g,b);// posicion (0,R G B)
            tira.setPixelColor(17,r,g,b);// posicion (0,R G B)
            tira.setPixelColor(19,r,g,b);// posicion (0,R G B)
            tira.setPixelColor(24,r,g,b);// posicion (0,R G B)  
            tira.setPixelColor(31,r,g,b);// posicion (0,R G B)
            tira.setPixelColor(38,r,g,b);// posicion (0,R G B)
            tira.setPixelColor(45,r,g,b);// posicion (0,R G B)
            tira.show();

            break;
        case 'd':
              //ABAJO
            tira.clear();
            tira.setPixelColor(3,r,g,b);// posicion (0,R G B)
            tira.setPixelColor(10,r,g,b);// posicion (0,R G B)
            tira.setPixelColor(17,r,g,b);// posicion (0,R G B)
            tira.setPixelColor(24,r,g,b);// posicion (0,R G B)  
            tira.setPixelColor(31,r,g,b);// posicion (0,R G B)
            tira.setPixelColor(38,r,g,b);// posicion (0,R G B)
            tira.setPixelColor(39,r,g,b);// posicion (0,R G B)
            tira.setPixelColor(37,r,g,b);// posicion (0,R G B)
            tira.setPixelColor(33,r,g,b);// posicion (0,R G B)
            tira.setPixelColor(29,r,g,b);// posicion (0,R G B)
            tira.setPixelColor(45,r,g,b);// posicion (0,R G B)
            break;
        case 'l':
            //IZQUIERDA
            tira.clear();
            tira.setPixelColor(21,r,g,b);// posicion (0,R G B)
            tira.setPixelColor(22,r,g,b);// posicion (0,R G B)
            tira.setPixelColor(23,r,g,b);// posicion (0,R G B)
            tira.setPixelColor(24,r,g,b);// posicion (0,R G B)
            tira.setPixelColor(25,r,g,b);// posicion (0,R G B)
            tira.setPixelColor(26,r,g,b);// posicion (0,R G B)
            tira.setPixelColor(27,r,g,b);// posicion (0,R G B)
            tira.setPixelColor(15,r,g,b);// posicion (0,R G B)  
            tira.setPixelColor(29,r,g,b);// posicion (0,R G B)
            tira.setPixelColor(11,r,g,b);// posicion (0,R G B)
            tira.setPixelColor(39,r,g,b);// posicion (0,R G B)
            tira.show();

            break;
        case 'r':
            //DERECHA
            tira.clear();
            tira.setPixelColor(21,r,g,b);// posicion (0,R G B)
            tira.setPixelColor(22,r,g,b);// posicion (0,R G B)
            tira.setPixelColor(23,r,g,b);// posicion (0,R G B)
            tira.setPixelColor(24,r,g,b);// posicion (0,R G B)
            tira.setPixelColor(25,r,g,b);// posicion (0,R G B)
            tira.setPixelColor(26,r,g,b);// posicion (0,R G B)
            tira.setPixelColor(27,r,g,b);// posicion (0,R G B)
            tira.setPixelColor(33,r,g,b);// posicion (0,R G B)  
            tira.setPixelColor(19,r,g,b);// posicion (0,R G B)
            tira.setPixelColor(9,r,g,b);// posicion (0,R G B)
            tira.setPixelColor(37,r,g,b);// posicion (0,R G B)
            tira.show();
            break;
    }
    
    };
