#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "secuencias.h"

void setup() {
  // Initialize LED strip
  tira.begin();
  tira.show();
}

void loop() {
  // Call flechas function with "arriba" direction and red color
  //flechas('u', 0);
}
