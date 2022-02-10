#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

#define RX_SON 12
#define TX_SON 13
const int sw = 7; //pour le bouton de l'encodeur
const int dt = 3;
const int clk = 2;
const int An = A0; // pour le capteur
const int Dig = 8; // pour le capteur


LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial mySerial(RX_SON,TX_SON);

int value_A0 = 0;
int value_D0 = 0;
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

static int8_t Send_buf[8] = {0} ;

#define CMD_SEL_DEV 0X09
#define DEV_TF 0X02
#define CMD_PLAY_WITHFOLDER 0X0F

void sendCommand(int8_t command, int16_t dat) { 
  delay(20); 
  Send_buf[0] = 0x7e; //starting byte 
  Send_buf[1] = 0xff; //version 
  Send_buf[2] = 0x06; //the number of bytes of the command without starting byte and ending byte 
  Send_buf[3] = command; // 
  Send_buf[4] = 0x00;//0x00 = no feedback, 0x01 = feedback 
  Send_buf[5] = (int8_t)(dat >> 8);//datah 
  Send_buf[6] = (int8_t)(dat); //datal 
  Send_buf[7] = 0xef; //ending byte 
  for(uint8_t i=0; i<8; i++){ 
    mySerial.write(Send_buf[i]) ; 
  } 
} 

void setup() {
  mySerial.begin(9600);
  pinMode(dt, INPUT);
  pinMode(clk, INPUT);
  pinMode(An, INPUT);
  pinMode(Dig, INPUT);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  tempsA = millis();
  tempsB = millis();
  sendCommand(CMD_SEL_DEV, DEV_TF);
  attachInterrupt(digitalPinToInterrupt(clk),genre,FALLING);
  attachInterrupt(digitalPinToInterrupt(dt),musique,FALLING);
}

void loop() {
  lcd.clear();

  value_A0 = analogRead(An);
  
  while (value_A0 > 600){
    lcd.setCursor(1,0);
    lcd.print("INSERER PIECE");
    lcd.setCursor(0,1);
    lcd.print("ET CHOISIR GENRE");
    delay(1000);
    value_A0 = analogRead(An);
  }

  while (value_A0 < 100){
    lcd.clear();
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
       musiqueMovie();
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
  
    if (numeroGenre==0){
       lireMusiqueRock();
     }
     else if (numeroGenre==1){
       lireMusiquePop();
     }
     else if ((numeroGenre==2)){
       lireMusiqueDisco();
     }
     else if (numeroGenre==3){
       lireMusiqueMovie();
     }
     else if (numeroGenre==4){
       lireMusiqueArcade();
     }
     else if (numeroGenre==5){
       lireMusiqueBestOf();
     } 
     

    value_A0 = analogRead(An);
    
    lcd.clear(); 
    while (value_A0 < 100){
      lcd.setCursor(0,0);
      lcd.print("RETIRER PIECE");
      value_A0 = analogRead(An);
    }
  }

  
  
  etat_bouton_musique = 0;
  etat_bouton_genre = 0;
  ancien_valBoutonGenre = 0;
  ancien_valBoutonMusique = 0;
  
}


void genre(){
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

void musique(){
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

void musiqueMovie(){
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

void lireMusiqueRock(){

  if (numeroMusique==0){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0101);
    delay(336000);
  }

  if (numeroMusique==1){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0102);
    delay(279000);
  }

  if (numeroMusique==2){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0103);
    delay(214000);
  }

  if (numeroMusique==3){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0104);
    delay(254000);
  }

  if (numeroMusique==4){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0105);
    delay(253000);
  }

  if (numeroMusique==5){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0106);
    delay(189000);
  }
}

void lireMusiquePop(){

  if (numeroMusique==0){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0201);
    delay(235000);
  }

  if (numeroMusique==1){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0202);
    delay(294000);
  }

  if (numeroMusique==2){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0203);
    delay(212000);
  }

  if (numeroMusique==3){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0204);
    delay(249000);
  }

  if (numeroMusique==4){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0205);
    delay(252000);
  }

  if (numeroMusique==5){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0206);
    delay(267000);
  }
}

void lireMusiqueDisco(){

  if (numeroMusique==0){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0301);
    delay(234000);
  }

  if (numeroMusique==1){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0302);
    delay(228000);
  }

  if (numeroMusique==2){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0303);
    delay(290000);
  }

  if (numeroMusique==3){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0304);
    delay(252000);
  }

  if (numeroMusique==4){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0305);
    delay(208000);
  }

  if (numeroMusique==5){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0306);
    delay(325000);
  }
}

void lireMusiqueMovie(){

  if (numeroMusique==0){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0401);
    delay(290000);
  }

  if (numeroMusique==1){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0402);
    delay(244000);
  }

  if (numeroMusique==2){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0403);
    delay(160000);
  }

  if (numeroMusique==3){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0404);
    delay(286000);
  }

  if (numeroMusique==4){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0405);
    delay(199000);
  }

  if (numeroMusique==5){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0406);
    delay(243000);
  }
}

void lireMusiqueArcade(){

  if (numeroMusique==0){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0501);
    delay(60000);
  }

  if (numeroMusique==1){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0502);
    delay(82000);
  }

  if (numeroMusique==2){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0503);
    delay(168000);
  }

  if (numeroMusique==3){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0504);
    delay(104000);
  }

  if (numeroMusique==4){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0505);
    delay(149000);
  }

  if (numeroMusique==5){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0506);
    delay(210000);
  }
}

void lireMusiqueBestOf(){

  if (numeroMusique==0){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0601);
    delay(275000);
  }

  if (numeroMusique==1){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0602);
    delay(259000);
  }

  if (numeroMusique==2){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0603);
    delay(343000);
  }

  if (numeroMusique==3){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0604);
    delay(300000);
  }

  if (numeroMusique==4){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0605);
    delay(310000);
  }

  if (numeroMusique==5){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0606);
    delay(336000);
  }
}
