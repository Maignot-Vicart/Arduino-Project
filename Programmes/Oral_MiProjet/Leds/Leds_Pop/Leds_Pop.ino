#include <Adafruit_NeoPixel.h>
 
int X=75;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(X, 6, NEO_GRB + NEO_KHZ800);
uint32_t Red=strip.Color(255,   0,   0);
uint32_t Blue=strip.Color(0,   0,   255);
uint32_t Green=strip.Color(0, 255,   0);
void colorWipe(uint32_t color, int speed=30) {
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
  colorWipe(Red, 50);
  colorWipe(Green, 50);
  colorWipe(Blue, 50);
}
