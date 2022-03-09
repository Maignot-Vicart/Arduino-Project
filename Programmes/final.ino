#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

#define RX 12
#define VOL 13
#define XR 5
#define XT 6
const int sw = 7; //pour le bouton de l'encodeur
const int dt = 3;
const int clk = 2;
const int An = A0; // pour le capteur
const int Dig = 8; // pour le capteur
int PWM = 0;
char Data;


LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial Bluetooth(XR,XT);
SoftwareSerial mySerial(RX,VOL);


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
int ancien_numeroGenre = 6;
int numeroMusique = 0;
int tempsDebut = 0;
int tempsMusique = 0;
static int8_t Send_buf[8] = {0} ;

#define CMD_SEL_DEV 0X09
#define DEV_TF 0X02
#define CMD_PLAY_WITHFOLDER 0X0F
#define CMD_SET_VOLUME 0X06

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
  Bluetooth.begin(9600);
  pinMode(dt, INPUT);
  pinMode(clk, INPUT);
  pinMode(An, INPUT);
  pinMode(Dig, INPUT);
  pinMode(VOL, OUTPUT);
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
      controleVolumeBluetooth();
      ancien_numeroGenre = numeroGenre;
      lireMusiqueRock();
    }
    else if (numeroGenre==1){
      ancien_numeroGenre = numeroGenre;
      lireMusiquePop();
    }
    else if ((numeroGenre==2)){
      ancien_numeroGenre = numeroGenre;
      lireMusiqueDisco();
    }
    else if (numeroGenre==3){
      ancien_numeroGenre = numeroGenre;
      lireMusiqueMovie();
    }
    else if (numeroGenre==4){
      ancien_numeroGenre = numeroGenre;
      lireMusiqueArcade();
    }
    else if (numeroGenre==5){
      ancien_numeroGenre = numeroGenre;
      lireMusiqueBestOf();
    } 

    tempsDebut = millis();
    while((millis()-tempsDebut)<tempsMusique){
      controleVolumeBluetooth();
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
  if (abs(millis()-tempsA) > 140){
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
  if (abs(millis()-tempsB) > 140){
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
    tempsMusique == 336000;
  }

  if (numeroMusique==1){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0102);
    tempsMusique == 279000;
  }

  if (numeroMusique==2){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0103);
    tempsMusique == 214000;
  }

  if (numeroMusique==3){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0104);
    tempsMusique == 254000;
  }

  if (numeroMusique==4){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0105);
    tempsMusique == 253000;
  }

  if (numeroMusique==5){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0106);
    tempsMusique == 189000;
  }
}

void lireMusiquePop(){

  if (numeroMusique==0){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0201);
    tempsMusique == 235000;
  }

  if (numeroMusique==1){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0202);
    tempsMusique == 294000;
  }

  if (numeroMusique==2){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0203);
    tempsMusique == 212000;
  }

  if (numeroMusique==3){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0204);
    tempsMusique == 249000;
  }

  if (numeroMusique==4){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0205);
    tempsMusique == 252000;
  }

  if (numeroMusique==5){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0206);
    tempsMusique == 267000;
  }
}

void lireMusiqueDisco(){

  if (numeroMusique==0){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0301);
    tempsMusique == 234000;
  }

  if (numeroMusique==1){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0302);
    tempsMusique == 228000;
  }

  if (numeroMusique==2){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0303);
    tempsMusique == 290000;
  }

  if (numeroMusique==3){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0304);
    tempsMusique == 252000;
  }

  if (numeroMusique==4){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0305);
    tempsMusique == 208000;
  }

  if (numeroMusique==5){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0306);
    tempsMusique == 325000;
  }
}

void lireMusiqueMovie(){

  if (numeroMusique==0){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0401);
    tempsMusique == 290000;
  }

  if (numeroMusique==1){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0402);
    tempsMusique == 244000;
  }

  if (numeroMusique==2){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0403);
    tempsMusique == 160000;
  }

  if (numeroMusique==3){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0404);
    tempsMusique == 286000;
  }

  if (numeroMusique==4){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0405);
    tempsMusique == 199000;
  }

  if (numeroMusique==5){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0406);
    tempsMusique == 243000;
  }
}

void lireMusiqueArcade(){

  if (numeroMusique==0){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0501);
    tempsMusique == 60000;
  }

  if (numeroMusique==1){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0502);
    tempsMusique == 82000;
  }

  if (numeroMusique==2){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0503);
    tempsMusique == 168000;
  }

  if (numeroMusique==3){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0504);
    tempsMusique == 104000;
  }

  if (numeroMusique==4){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0505);
    tempsMusique == 149000;
  }

  if (numeroMusique==5){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0506);
    tempsMusique == 210000;
  }
}

void lireMusiqueBestOf(){

  if (numeroMusique==0){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0601);
    tempsMusique == 275000;
  }

  if (numeroMusique==1){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0602);
    tempsMusique == 259000;
  }

  if (numeroMusique==2){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0603); 
    tempsMusique == 343000;
  }

  if (numeroMusique==3){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0604);
    tempsMusique == 300000;
  }

  if (numeroMusique==4){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0605);
    tempsMusique == 310000;
  }

  if (numeroMusique==5){
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0606); 
    tempsMusique == 336000;
  }
}

void controleVolumeBluetooth() {
  if(Bluetooth.available()) {
    Data = Bluetooth.read();
    if(Data == 'A') {
      PWM = Bluetooth.parseInt();
      if(0<=PWM && PWM<=50) {
        sendCommand(CMD_SET_VOLUME, 0);
      }
      if(51<=PWM && PWM<=100) {
        sendCommand(CMD_SET_VOLUME, 24);
      }
      if(101<=PWM && PWM<=150) {
        sendCommand(CMD_SET_VOLUME, 26);
      }
      if(151<=PWM && PWM<=200) {
        sendCommand(CMD_SET_VOLUME, 28);
      }
      if(201<=PWM && PWM<=255) {
        sendCommand(CMD_SET_VOLUME, 30);
      }
    }
  }
}
