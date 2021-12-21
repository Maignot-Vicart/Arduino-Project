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
    lcd.print("Girls Just Wanna Have Fun – Cindy Lauper");
    numero = 1;
  }
  
  else if ((tension>170)&&(tension<=341)){
    lcd.setCursor(6,0);
    lcd.print("Take On Me – Aha");
    numero = 2;
  }

  else if ((341<tension)&&(tension<=511)){
    lcd.setCursor(5,0);
    lcd.print("I Wanna Dance with Somebody – Whitney Houston");
    numero = 3;
  }

  else if ((511<tension)&&(tension<=682)){
    lcd.setCursor(2,0);
    lcd.print("Heart Of Glass – Blondie");
    numero = 4;
  }

  else if ((682<tension)&&(tension<=852)){
    lcd.setCursor(5,0);
    lcd.print("Night Fever – Bee Gees");
    numero = 5;
  }

  else if ((852<tension)&&(tension<=1023)){
    lcd.setCursor(2,0);
    lcd.print("It’s Raining Man – Weather Girls");
    numero = 6;
  }
}
