#include <Adafruit_NeoPixel.h>
 
int X=74;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(X, 6, NEO_GRB + NEO_KHZ800);
uint32_t Red=strip.Color(255,   0,   0);
uint32_t Blue=strip.Color(0,   0,   255);
uint32_t Green=strip.Color(0, 255,   0);
uint32_t Yellow=strip.Color(255, 255,   0);
uint32_t White=strip.Color(255, 255, 255);
void colorWipe(uint32_t color, int speed=50,bool single=false) {
  for(int i=0; i<X; i++) {
    if (single) strip.clear();
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
  strip.clear();
  colorWipe(Blue);
  colorWipe(Red);
  colorWipe(Green);
  colorWipe(Yellow);
}
