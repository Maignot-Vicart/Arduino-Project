
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int bouton1=2;
const int bouton2=8;
const int bouton3=9;
int val=1;
int val2=1;
int val3=1;
int etat=1;
int etat2=1;
int etat3=1;
int ancien_val=1;
int ancien_val2=1;
int ancien_val3=1;

void setup() {
  lcd.init();
  lcd.backlight();
  pinMode(bouton2, INPUT);
  pinMode(bouton1, INPUT);
}

void loop() {
  
  lcd.setCursor(0,0);
  lcd.print("Choisir le genre");
  
  val=digitalRead(bouton1);
  val2=digitalRead(bouton2);
  val3=digitalRead(bouton3);
 
  if ((val==LOW)&&(ancien_val==HIGH)){ 
    etat=1-etat; 
    ancien_val=val;
    if(etat==LOW){
      lcd.clear();
      lcd.print("ROCK"); 
      delay(1000);
      digitalWrite(bouton1,HIGH);
    }
  }
  
  else if ((val2==LOW)&&(ancien_val2==HIGH)&&(digitalRead(bouton1)==HIGH)){
    etat2=1-etat2;
    ancien_val2=val2;
    if(etat2==LOW){
      lcd.clear();
      lcd.print("POP"); 
      delay(1000);
      digitalWrite(bouton2,HIGH);
    }
  }

  else if ((val3==LOW)&&(ancien_val3==HIGH)&&(digitalRead(bouton1)==HIGH)&&(digitalRead(bouton2)==HIGH)){
    etat3=1-etat3;
    ancien_val3=val3;
    if(etat3==LOW){
      lcd.clear();
      lcd.print("DISCO"); 
      delay(1000);
      digitalWrite(bouton3,HIGH);
    }
  }
}
  
