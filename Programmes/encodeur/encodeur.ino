#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int sw = 7; //pour le bouton
const int dt = 3;
const int clk = 2;
int valBoutonGenre = 0;
int ancien_valBoutonGenre = 0;
int etat_bouton_genre = 0;
int valBoutonMusique = 0;
int ancien_valBoutonMusique = 0;
int etat_bouton_musique = 0;
int compteur = 0;
int ancien_compteur = 0;
int compteur2 = 0;
int ancien_compteur2 = 0;
int tempsA = 0;
int tempsB = 0;
int numeroGenre = 0;
int numeroMusique = 0;


void setup() {
  pinMode(dt, INPUT);
  pinMode(clk, INPUT);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  tempsA = millis();
  attachInterrupt(digitalPinToInterrupt(clk),genre,FALLING);
  attachInterrupt(digitalPinToInterrupt(dt),musique,FALLING);
}

void loop() {
  
  while (etat_bouton_genre==LOW){
    
    if (compteur==ancien_compteur){
      Serial.println("même genre");
    }
    else{
      lcd.clear();
    }
    
    ancien_compteur=compteur;
    
    Serial.println(compteur);
    delay(100);
    
    if ((compteur==0)){
      lcd.setCursor(6,0);
      lcd.print("ROCK");
      numeroGenre = 0;
    }
    else if ((compteur==1)){
      lcd.setCursor(6,0);
      lcd.print("POP");
      numeroGenre = 1;
    }
    else if ((compteur==2)){
      lcd.setCursor(5,0);
      lcd.print("DISCO");
      numeroGenre = 2;
    }
    else if (compteur==3){
      lcd.setCursor(2,0);
      lcd.print("80'S MOVIES");
      numeroGenre = 3;
    }
    else if (compteur==4){
      lcd.setCursor(5,0);
      lcd.print("ARCADE");
      numeroGenre = 4;
    }
    else if (compteur==5){
      lcd.setCursor(2,0);
      lcd.print("80'S BEST OF");
      numeroGenre = 5;
    }
    
    valBoutonGenre = digitalRead(sw);

    if ((valBoutonGenre==LOW)&&(ancien_valBoutonGenre==HIGH)){
      etat_bouton_genre=1-etat_bouton_genre;
      delay(20);
    }

    ancien_valBoutonGenre = valBoutonGenre;
 }
 
  
 Serial.println("bouton OK GENRE");
  
 while (etat_bouton_musique==LOW){
    
   if (compteur2==ancien_compteur2){
     Serial.println("même musique");
   }
   else{
     lcd.clear();
   }
    
   ancien_compteur2=compteur2;
    
   Serial.println(compteur2);
   delay(100);
    
   if (numeroGenre==0){
     musiqueRock();
   }
   else if (numeroGenre==1){
     musiquePop();
   }
   else if ((numeroGenre==2)){
     musiqueDisco();
   }
   else if (numeroGenre==3){
     musiqueMovies();
   }
   else if (numeroGenre==4){
     musiqueArcade();
   }
   else if (numeroGenre==5){
     musiqueBestOf();
   }
    
   valBoutonMusique = digitalRead(sw);

   if ((valBoutonMusique==LOW)&&(ancien_valBoutonMusique==HIGH)){
     etat_bouton_musique=1-etat_bouton_musique;
     delay(20);
   }

   ancien_valBoutonMusique = valBoutonMusique;
  }
  Serial.println("bouton OK MUSIQUE");
  
}


int genre(){
  if (abs(millis()-tempsA) > 100){
    if (dt) {
      compteur++;
      if (compteur>5){
        compteur=0;
      }
    }
    else {
      compteur--;
      if (compteur<0){
        compteur=5;
      }
    }
    tempsA=millis();
  }
}

int musique(){
  if (abs(millis()-tempsB) > 100){
    if (dt) {
      compteur2++;
      if (compteur2>5){
        compteur2=0;
      }
    }
    else {
      compteur2--;
      if (compteur2<0){
        compteur2=5;
      }
    }
    tempsB=millis();
  }
}

void musiqueRock(){
  if (compteur2==0){
    lcd.setCursor(0,0);
    lcd.print("Knockin On Heaven s Door");
    lcd.scrollDisplayLeft();
    delay(200);
    lcd.setCursor(0,1);
    lcd.print("Guns N Roses");
    numeroMusique=0;
  }
  else if (compteur2==1){
    lcd.setCursor(0,0);
    lcd.print("Sunday Bloody Sunday");
    lcd.scrollDisplayLeft();
    delay(200);
    lcd.setCursor(0,1);
    lcd.print("U2");
    numeroMusique=1;
  }
  else if (compteur2==2){
    lcd.setCursor(0,0);
    lcd.print("Another One Bites The Dust");
    lcd.scrollDisplayLeft();
    delay(200);
    lcd.setCursor(0,1);
    lcd.print("Queen");
    numeroMusique = 2;
  }
  else if (compteur2==3){
    lcd.setCursor(0,0);
    lcd.print("Rock You Like A Hurricane");
    lcd.scrollDisplayLeft();
    delay(200);
    lcd.setCursor(0,1);
    lcd.print("Scorpions");
    numeroMusique = 3;
  }
  else if (compteur2==4){
    lcd.setCursor(0,0);
    lcd.print("Back In Black");
    lcd.setCursor(0,1);
    lcd.print("AC/DC");   
    numeroMusique=4; 
  }
  else if (compteur2==5){
    lcd.setCursor(0,0);
    lcd.print("Should I Stay Or Should I Go");
    lcd.scrollDisplayLeft();
    delay(200);
    lcd.setCursor(0,1);
    lcd.print("The Clash");
    numeroMusique=5;
  }
}

void musiquePop(){
  if (compteur2==0){
    lcd.setCursor(0,0);
    lcd.print("Kiss");
    lcd.setCursor(0,1);
    lcd.print("Prince");
    numeroMusique=0;
  }
  else if (compteur2==1){
    lcd.setCursor(0,0);
    lcd.print("Billie Jean");
    lcd.setCursor(0,1);
    lcd.print("Michael Jackson");
    numeroMusique=1;
  }
  else if (compteur2==2){
    lcd.setCursor(0,0);
    lcd.print("Never Gonna Give You Up");
    lcd.scrollDisplayLeft();
    delay(200);
    lcd.setCursor(0,1);
    lcd.print("Rick Astley");
    numeroMusique = 2;
  }
  else if (compteur2==3){
    lcd.setCursor(0,0);
    lcd.print("The Logical Song");
    lcd.setCursor(0,1);
    lcd.print("Superstramp");
    numeroMusique = 3;
  }
  else if (compteur2==4){
    lcd.setCursor(0,0);
    lcd.print("Everybody Wants to Rule the World");
    lcd.scrollDisplayLeft();
    delay(200);
    lcd.setCursor(0,1);
    lcd.print("Tears For Fears");
    numeroMusique=4;
  }
  else if (compteur2==5){
    lcd.setCursor(0,0);
    lcd.print("Total Eclipse of the Heart");
    lcd.scrollDisplayLeft();
    delay(200);
    lcd.setCursor(0,1);
    lcd.print("Bonnie Tyler");
    numeroMusique=5;
  }
}

void musiqueDisco(){
  if (compteur2==0){
    lcd.setCursor(0,0);
    lcd.print("Girls Just Wanna Have Fun");
    lcd.scrollDisplayLeft();
    delay(200);
    lcd.setCursor(0,1);
    lcd.print("Cyndi Lauper");
    numeroMusique=0;
  }
  else if (compteur2==1){
    lcd.setCursor(0,0);
    lcd.print("Take On Me");
    lcd.setCursor(0,1);
    lcd.print("Aha");
    numeroMusique=1;
  }
  else if (compteur2==2){
    lcd.setCursor(0,0);
    lcd.print("I Wanna Dance With Somebody");
    lcd.scrollDisplayLeft();
    delay(200);
    lcd.setCursor(0,1);
    lcd.print("Whitney Houston");
    numeroMusique = 2;
  }
  else if (compteur2==3){
    lcd.setCursor(0,0);
    lcd.print("Heart Of Glass");
    lcd.setCursor(0,1);
    lcd.print("Blondie");
    numeroMusique = 3;
  }
  else if (compteur2==4){
    lcd.setCursor(0,0);
    lcd.print("Night Fever");
    lcd.setCursor(0,1);
    lcd.print("Bee Gees");
    numeroMusique=4;
  }
  else if (compteur2==5){
    lcd.setCursor(0,0);
    lcd.print("It s Raining Men");
    lcd.setCursor(0,1);
    lcd.print("The Weather Girls");
    numeroMusique=5;
  }
}

void musiqueMovies(){
  if (compteur2==0){
    lcd.setCursor(0,0);
    lcd.print("The Time Of My Life");
    lcd.scrollDisplayLeft();
    delay(200);
    lcd.setCursor(0,1);
    lcd.print("Dirty Dancing");
    numeroMusique=0;
  }
  else if (compteur2==1){
    lcd.setCursor(0,0);
    lcd.print("Eye Of The Tiger");
    lcd.setCursor(0,1);
    lcd.print("Rocky");
    numeroMusique=1;
  }
  else if (compteur2==2){
    lcd.setCursor(0,0);
    lcd.print("Johnny Bee Goode");
    lcd.scrollDisplayLeft();
    delay(200);
    lcd.setCursor(0,1);
    lcd.print("Back To The Future");
    numeroMusique = 2;
  }
  else if (compteur2==3){
    lcd.setCursor(0,0);
    lcd.print("Reality");
    lcd.setCursor(0,1);
    lcd.print("La Boum");
    numeroMusique = 3;
  }
  else if (compteur2==4){
    lcd.setCursor(0,0);
    lcd.print("What A Feeling");
    lcd.setCursor(0,1);
    lcd.print("Flashdance");
    numeroMusique=4;
  }
  else if (compteur2==5){
    lcd.setCursor(0,0);
    lcd.print("Ghostbusters");
    numeroMusique=5;
  }
}

void musiqueArcade(){
  if (compteur2==0){
    lcd.setCursor(0,0);
    lcd.print("Pacman");
    numeroMusique=0;
  }
  else if (compteur2==1){
    lcd.setCursor(0,0);
    lcd.print("Super Mario Bros");
    numeroMusique=1;
  }
  else if (compteur2==2){
    lcd.setCursor(0,0);
    lcd.print("The Legend Of");
    lcd.setCursor(0,1);
    lcd.print("Zelda");
    numeroMusique = 2;
  }
  else if (compteur2==3){
    lcd.setCursor(0,0);
    lcd.print("Tetris");
    numeroMusique = 3;
  }
  else if (compteur2==4){
    lcd.setCursor(0,0);
    lcd.print("Metroid");
    numeroMusique=4;
  }
  else if (compteur2==5){
    lcd.setCursor(0,0);
    lcd.print("ExciteBike");
    numeroMusique=5;
  }
}

void musiqueBestOf(){
  if (compteur2==0){
    lcd.setCursor(0,0);
    lcd.print("Purple Rain");
    lcd.setCursor(0,1);
    lcd.print("Prince");
    numeroMusique=0;
  }
  else if (compteur2==1){
    lcd.setCursor(0,0);
    lcd.print("Beat It");
    lcd.setCursor(0,1);
    lcd.print("Michael Jackson");
    numeroMusique=1;
  }
  else if (compteur2==2){
    lcd.setCursor(0,0);
    lcd.print("Radio Gaga");
    lcd.setCursor(0,1);
    lcd.print("Queen");
    numeroMusique = 2;
  }
  else if (compteur2==3){
    lcd.setCursor(0,0);
    lcd.print("Careless Whisper");
    lcd.setCursor(0,1);
    lcd.print("George Michael");
    numeroMusique = 3;
  }
  else if (compteur2==4){
    lcd.setCursor(0,0);
    lcd.print("The Final Countdown");
    lcd.scrollDisplayLeft();
    delay(200);
    lcd.setCursor(0,1);
    lcd.print("Europe");
    numeroMusique=4;
  }
  else if (compteur2==5){
    lcd.setCursor(0,0);
    lcd.print("Sweet Dreams");
    lcd.setCursor(0,1);
    lcd.print("Annie Lenox");
    numeroMusique=5;
  }
}
