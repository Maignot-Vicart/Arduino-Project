#include <Adafruit_NeoPixel.h>
 
// Parameter 32 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
int X=20;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(X, 6, NEO_GRB + NEO_KHZ800);
void setup() {
  strip.begin();
  strip.show(); // Initialise toute les led à 'off'
   
}
 
void loop() {
    strip.setPixelColor(1, 223, 0, 0);       
    strip.show();
    delay(1000);
    strip.setPixelColor(2, 200, 20, 0);       
    strip.show();
    delay(1000);
    strip.setPixelColor(3, 180, 20, 20);       
    strip.show();
    delay(1000);
    strip.setPixelColor(4, 140, 40, 40);       
    strip.show();
    delay(1000);
    strip.setPixelColor(5, 100, 60, 60);       
    strip.show();
    delay(1000);
    strip.setPixelColor(6, 60, 80, 80);       
    strip.show();
    delay(1000);
    strip.setPixelColor(7, 20, 100, 100);       
    strip.show();
    delay(1000);
    strip.setPixelColor(8, 0, 120, 100);       
    strip.show();
    delay(1000);
    strip.setPixelColor(9, 0, 150, 130);       
    strip.show();
    delay(1000);
}
