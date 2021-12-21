#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int potentiometre = 0;
const int boutonOK = 9;
const int boutonRETOUR = 8;
float tension = 0;
int numeroMusique = 0;


void setup() {
  lcd.init();
  lcd.backlight();
  pinMode(potentiometre,INPUT);
  lcd.setCursor(0,0);
  lcd.print("Choisir la musique");

}

void loop() {
  tension = analogRead(0);
  
  if ((0<=tension)&&(tension<=170)){
    lcd.setCursor(6,0);
    lcd.print("Knockin’ On Heaven’s Door – Guns N’ Roses");
    numero = 1;
  }
  
  else if ((tension>170)&&(tension<=341)){
    lcd.setCursor(6,0);
    lcd.print("Sunday Bloody Sunday – U2");
    numero = 2;
  }

  else if ((341<tension)&&(tension<=511)){
    lcd.setCursor(5,0);
    lcd.print(" Another One Bites the Dust – Queen");
    numero = 3;
  }

  else if ((511<tension)&&(tension<=682)){
    lcd.setCursor(2,0);
    lcd.print("Rock You Like a Hurricane – Scorpions");
    numero = 4;
  }

  else if ((682<tension)&&(tension<=852)){
    lcd.setCursor(5,0);
    lcd.print("Back in Black – ACDC");
    numero = 5;
  }

  else if ((852<tension)&&(tension<=1023)){
    lcd.setCursor(2,0);
    lcd.print("Should I Stay or Should I Go – The Clash");
    numero = 6;
  }
}
