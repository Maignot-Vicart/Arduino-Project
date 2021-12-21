#include choix.musique.h

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int potentiometre = 0;
const int boutonOK = 9;
const int boutonRETOUR = 8;
float tension = 0;
int numeroGenre = 0;
int numeroMusique = 0;
int valOK = 1;
int valOK2 = 1;
int etatOK = 1;
int etatOK2 = 1;
int ancien_valOK = 1;
int ancien_valOK2 = 1;


void setup() {
  pinMode(boutonOK, INPUT);
  lcd.init();
  lcd.backlight();
  pinMode(potentiometre,INPUT);
  lcd.setCursor(0,0);
  lcd.print("Choisir le genre");

}

void loop() {
  tension = analogRead(0);
  
  if ((0<=tension)&&(tension<=170)){
    lcd.setCursor(6,0);
    lcd.print("ROCK");
    numeroGenre = 1;
  }
  
  else if ((tension>170)&&(tension<=341)){
    lcd.setCursor(6,0);
    lcd.print("POP");
    numeroGenre = 2;
  }

  else if ((341<tension)&&(tension<=511)){
    lcd.setCursor(5,0);
    lcd.print("DISCO");
    numeroGenre = 3;
  }

  else if ((511<tension)&&(tension<=682)){
    lcd.setCursor(2,0);
    lcd.print("80'S MOVIES");
    numeroGenre = 4;
  }

  else if ((682<tension)&&(tension<=852)){
    lcd.setCursor(5,0);
    lcd.print("ARCADE");
    numeroGenre = 5;
  }

  else if ((852<tension)&&(tension<=1023)){
    lcd.setCursor(2,0);
    lcd.print("80'S BEST OF");
    numeroGenre = 6;
  }

  valOK = digitalRead(boutonOK);

  if ((valOK==LOW)&&(ancien_valOK==HIGH)){
    etat=1-etat;
    delay(20);
    lcd.setCursor(3,0);
    lcd.print("Choisir la");
    lcd.setCursor(5,1);
    lcd.print("musique");
  }
  ancien_valOK = valOK;
  
  if ((etat==HIGH)&&(numeroGenre==1)){
    musiqueRock();
  }

  else if ((etat==HIGH)&&(numeroGenre==2)){
    musiquePop();
  }

  else if ((etat==HIGH)&&(numeroGenre==3)){
    musiqueDisco();
  }

  else if ((etat==HIGH)&&(numeroGenre==4)){
    musiqueMovie();
  }

  else if ((etat==HIGH)&&(numeroGenre==5)){
    musiqueArcade();
  }

  else if ((etat==HIGH)&&(numeroGenre==6)){
    musiqueBestOf();
  }

  valOK2 = digitalRead(boutonOK);

  if ((valOK2==LOW)&&(ancien_valOK2==HIGH)){
    etat2=1-etat2;
    delay(20);
  }
  ancien_valOK2 = valOK2;

  if ((etat==HIGH)&&(numeroGenre==1)){
    lireMusiqueRock();
  }

  else if ((etat==HIGH)&&(numeroGenre==2)){
    lireMusiquePop();
  }

  else if ((etat==HIGH)&&(numeroGenre==3)){
    lireMusiqueDisco();
  }

  else if ((etat==HIGH)&&(numeroGenre==4)){
    lireMusiqueMovie();
  }

  else if ((etat==HIGH)&&(numeroGenre==5)){
    lireMusiqueArcade();
  }

  else if ((etat==HIGH)&&(numeroGenre==6)){
    lireMusiqueBestOf();
  }
}
