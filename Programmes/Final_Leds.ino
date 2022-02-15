#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>

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
int X=75;


LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial Bluetooth(XR,XT);
SoftwareSerial mySerial(RX,VOL);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(X, 9, NEO_GRB + NEO_KHZ800);


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
  strip.begin();
  strip.show();
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

    led_color();
    
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

//fonction de LEDs

void led_color(){
  if (numeroGenre==0){
    Fire(55,120,15);
  }
  else if (numeroGenre==1){
    meteorRain(0xff,0xff,0xff,10, 64, true, 30);
  }
  else if (numeroGenre==2){
    Strobe(0xff, 0xff, 0xff, 10, 50, 1000);
  }
  else if (numeroGenre==3){
    theaterChaseRainbow(50);
  }
  else if (numeroGenre==4){
    byte colors[3][3] = { {0xff,0,0},
                        {0,0xff,0},
                        {0,0,0xff} };

    BouncingColoredBalls(3, colors);
  }
  else if (numeroGenre==5){
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
