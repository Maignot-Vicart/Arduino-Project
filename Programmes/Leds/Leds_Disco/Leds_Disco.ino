#include <Adafruit_NeoPixel.h>

int X=75;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(X, 6, NEO_GRB + NEO_KHZ800);

void Strobe(byte red, byte green, byte blue, int StrobeCount, int FlashDelay, int EndPause){
  for(int j = 0; j < StrobeCount; j++) {
    strip.setPixelColor(X,red,green,blue);
    strip.show();
    delay(FlashDelay);
    strip.setPixelColor(X,0,0,0);
    strip.show();
    delay(FlashDelay);
  }
 
 delay(EndPause);
}

void setup() {
strip.begin();
strip.show();
}

void loop() {
  // Slower:
  // Strobe(0xff, 0x77, 0x00, 10, 100, 1000);
  // Fast:
  Strobe(0xff, 0xff, 0xff, 10, 50, 1000);
}
