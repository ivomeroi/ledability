#include <Arduino.h>
#include "secuencias.h"
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel strip(49, 2, NEO_GRB + NEO_KHZ800);


void setup() {
  // Initialize LED strip
  Serial.begin(115200);  
  strip.setBrightness(20);
  strip.begin();
  strip.show();
}

void loop() {
  // Call flechas function with "arriba" direction and red color
  flechas('d', 1, strip);
  Serial.println("Arriba");
}
