#include <Adafruit_NeoPixel.h>
 
int X=75;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(X, 6, NEO_GRB + NEO_KHZ800);
uint32_t White=strip.Color(255, 255, 255);
uint32_t Yellow=strip.Color(255, 211, 0);
uint32_t Orange=strip.Color(255, 165, 0);
uint32_t Red=strip.Color(255, 0, 0);
uint32_t Pink=strip.Color(255, 192, 203);
uint32_t Purple=strip.Color(128, 0, 128);
uint32_t Blue=strip.Color(0, 0, 255);
uint32_t Green=strip.Color(0, 255, 0);
uint32_t Black=strip.Color(0, 0, 0);

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
  colorWipe(White);
  colorWipe(Yellow);
  colorWipe(Orange);
  colorWipe(Red);
  colorWipe(Pink);
  colorWipe(Purple);
  colorWipe(Blue);
  colorWipe(Green);
  colorWipe(Black);
}
