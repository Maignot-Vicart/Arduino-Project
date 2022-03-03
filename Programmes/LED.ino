
#include <Adafruit_NeoPixel.h>

int X=40;
int temps=0;


Adafruit_NeoPixel strip = Adafruit_NeoPixel(X, 6, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show();
}

void loop() {
  temps=millis();
  while((millis()-temps)<10000){
    Fire(55,120,15);
  }

  temps=millis();
  while((millis()-temps)<10000){
    meteorRain(0xff,0xff,0xff,10, 64, true, 30);
  }

  temps=millis();
  while((millis()-temps)<10000){
    theaterChaseRainbow(50);
  }

  temps=millis();
  while((millis()-temps)<10000){
    byte colors[3][3] = { {0xff,0,0},
                        {0,0xff,0},
                        {0,0,0xff} };

    BouncingColoredBalls(3, colors);
  }

  temps=millis();
  while((millis()-temps)<10000){
    rainbowCycle(20);
  }

}

void setPixelHeatColor (int Pixel, byte temperature) {
  // Scale 'heat' down from 0-255 to 0-191
  byte t192 = round((temperature/255.0)*191);
 
  // calculate ramp up from
  byte heatramp = t192 & 0x3F; // 0..63
  heatramp <<= 2; // scale up to 0..252
 
  // figure out which third of the spectrum we're in:
  if( t192 > 0x80) {                     // hottest
    strip.setPixelColor(Pixel, 255, 255, heatramp);
  } else if( t192 > 0x40 ) {             // middle
    strip.setPixelColor(Pixel, 255, heatramp, 0);
  } else {                               // coolest
    strip.setPixelColor(Pixel, heatramp, 0, 0);
  }
}

void Fire(int Cooling, int Sparking, int SpeedDelay) {
  byte heat[X];
  int cooldown;
 
  // Step 1.  Cool down every cell a little
  for( int i = 0; i < X; i++) {
    cooldown = random(0, ((Cooling * 10) / X) + 2);
   
    if(cooldown>heat[i]) {
      heat[i]=0;
    } else {
      heat[i]=heat[i]-cooldown;
    }
  }
 
  // Step 2.  Heat from each cell drifts 'up' and diffuses a little
  for( int k= X - 1; k >= 2; k--) {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
  }
   
  // Step 3.  Randomly ignite new 'sparks' near the bottom
  if( random(255) < Sparking ) {
    int y = random(7);
    heat[y] = heat[y] + random(160,255);
    //heat[y] = random(160,255);
  }

  // Step 4.  Convert heat to LED colors
  for( int j = 0; j < X; j++) {
    setPixelHeatColor(j, heat[j] );
  }

  strip.show();
  delay(SpeedDelay);
}


void meteorRain(byte red, byte green, byte blue, byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay, int SpeedDelay) {  
 
  for(int i = 0; i < X+X; i++) {
   
   
    // fade brightness all LEDs one step
    for(int j=0; j<X; j++) {
      if( (!meteorRandomDecay) || (random(10)>5) ) {
        fadeToBlack(j, meteorTrailDecay );        
      }
    }
   
    // draw meteor
    for(int j = 0; j < meteorSize; j++) {
      if( ( i-j <X) && (i-j>=0) ) {
        strip.setPixelColor(i-j, red, green, blue);
      }
    }
   
    strip.show();
    delay(SpeedDelay);
  }
}


void fadeToBlack(int ledNo, byte fadeValue) {
 #ifdef ADAFRUIT_NEOPIXEL_H
    // NeoPixel
    uint32_t oldColor;
    uint8_t r, g, b;
    int value;
   
    oldColor = strip.getPixelColor(ledNo);
    r = (oldColor & 0x00ff0000UL) >> 16;
    g = (oldColor & 0x0000ff00UL) >> 8;
    b = (oldColor & 0x000000ffUL);

    r=(r<=10)? 0 : (int) r-(r*fadeValue/256);
    g=(g<=10)? 0 : (int) g-(g*fadeValue/256);
    b=(b<=10)? 0 : (int) b-(b*fadeValue/256);
   
    strip.setPixelColor(ledNo, r,g,b);
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   leds[ledNo].fadeToBlackBy( fadeValue );
 #endif  
}




void theaterChaseRainbow(int SpeedDelay) {
  byte *c;
 
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < X; i=i+3) {
          c = Wheel( (i+j) % 255);
          strip.setPixelColor(i+q, *c, *(c+1), *(c+2));    //turn every third pixel on
        }
        strip.show();
       
        delay(SpeedDelay);
       
        for (int i=0; i < X; i=i+3) {
          strip.setPixelColor(i+q, 0,0,0);        //turn every third pixel off
        }
    }
  }
}

byte * Wheel(byte WheelPos) {
  static byte c[3];
 
  if(WheelPos < 85) {
   c[0]=WheelPos * 3;
   c[1]=255 - WheelPos * 3;
   c[2]=0;
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   c[0]=255 - WheelPos * 3;
   c[1]=0;
   c[2]=WheelPos * 3;
  } else {
   WheelPos -= 170;
   c[0]=0;
   c[1]=WheelPos * 3;
   c[2]=255 - WheelPos * 3;
  }

  return c;
}

void BouncingColoredBalls(int BallCount, byte colors[][3]) {
  float Gravity = -9.81;
  int StartHeight = 1;
 
  float Height[BallCount];
  float ImpactVelocityStart = sqrt( -2 * Gravity * StartHeight );
  float ImpactVelocity[BallCount];
  float TimeSinceLastBounce[BallCount];
  int   Position[BallCount];
  long  ClockTimeSinceLastBounce[BallCount];
  float Dampening[BallCount];
 
  for (int i = 0 ; i < BallCount ; i++) {  
    ClockTimeSinceLastBounce[i] = millis();
    Height[i] = StartHeight;
    Position[i] = 0;
    ImpactVelocity[i] = ImpactVelocityStart;
    TimeSinceLastBounce[i] = 0;
    Dampening[i] = 0.90 - float(i)/pow(BallCount,2);
  }

  while (true) {
    for (int i = 0 ; i < BallCount ; i++) {
      TimeSinceLastBounce[i] =  millis() - ClockTimeSinceLastBounce[i];
      Height[i] = 0.5 * Gravity * pow( TimeSinceLastBounce[i]/1000 , 2.0 ) + ImpactVelocity[i] * TimeSinceLastBounce[i]/1000;
 
      if ( Height[i] < 0 ) {                      
        Height[i] = 0;
        ImpactVelocity[i] = Dampening[i] * ImpactVelocity[i];
        ClockTimeSinceLastBounce[i] = millis();
 
        if ( ImpactVelocity[i] < 0.01 ) {
          ImpactVelocity[i] = ImpactVelocityStart;
        }
      }
      Position[i] = round( Height[i] * (X - 1) / StartHeight);
    }
 
    for (int i = 0 ; i < BallCount ; i++) {
      strip.setPixelColor(Position[i],colors[i][0],colors[i][1],colors[i][2]);
    }
   
    strip.show();
  }
}

void rainbowCycle(int SpeedDelay) {
  byte *c;
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< X; i++) {
      c=Wheel(((i * 256 / X) + j) & 255);
      strip.setPixelColor(i, *c, *(c+1), *(c+2));
    }
    strip.show();
    delay(SpeedDelay);
  }
}
