#include <Adafruit_NeoPixel.h>
 
int X=75;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(X, 6, NEO_GRB + NEO_KHZ800);
uint32_t Yellow=strip.Color(255, 211, 0);
uint32_t Orange=strip.Color(255, 165, 0);
uint32_t Blue=strip.Color(0,   0,   255);

void colorWipe(uint32_t color, int speed=20) {
  for(int i=0; i<X; i++) {
    strip.setPixelColor(i, color);
    strip.show();
    delay(speed);
  }
}
void setup() {
strip.begin();
strip.show();
}
void loop() {
  colorWipe(Yellow);
  colorWipe(Orange);
  colorWipe(Blue);
}
