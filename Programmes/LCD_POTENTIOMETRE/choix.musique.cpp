#include choix.musique.h

void musiqueRock(){
  tension = analogRead(0);
  
  if ((0<=tension)&&(tension<=170)){
    lcd.setCursor(0,0);
    lcd.print("Knockin On Heaven s Door");
    lcd.scrollDisplayLeft();
    delay(200);
    lcd.setCursor(0,1);
    lcd.print("Guns N Roses");
    numeroMusique = 1;
  }
  
  else if ((tension>170)&&(tension<=341)){
    lcd.setCursor(0,0);
    lcd.print("Sunday Bloody Sunday");
    lcd.scrollDisplayLeft();
    delay(200);
    lcd.setCursor(0,1);
    lcd.print("U2");
    numeroMusique = 2;
  }

  else if ((341<tension)&&(tension<=511)){
    lcd.setCursor(0,0);
    lcd.print("Another One Bites The Dust");
    lcd.scrollDisplayLeft();
    delay(200);
    lcd.setCursor(0,1);
    lcd.print("Queen");
    numeroMusique = 3;
  }

  else if ((511<tension)&&(tension<=682)){
    lcd.setCursor(0,0);
    lcd.print("Rock You Like A Hurricane");
    lcd.scrollDisplayLeft();
    delay(200);
    lcd.setCursor(0,1);
    lcd.print("Scorpions");
    numeroMusique = 4;
  }

  else if ((682<tension)&&(tension<=852)){
    lcd.setCursor(0,0);
    lcd.print("Back In Black");
    lcd.setCursor(0,1);
    lcd.print("AC/DC");
    numeroMusique = 5;
  }

  else if ((852<tension)&&(tension<=1023)){
    lcd.setCursor(0,0);
    lcd.print("Should I Stay Or Should I Go");
    lcd.scrollDisplayLeft();
    delay(200);
    lcd.setCursor(0,1);
    lcd.print("The Clash");
    numeroMusique = 6;
  }
}

void musiquePop(){
  tension = analogRead(0);
  
  if ((0<=tension)&&(tension<=170)){
    lcd.setCursor(0,0);
    lcd.print("Kiss");
    lcd.setCursor(0,1);
    lcd.print("Prince");
    numeroMusique = 1;
  }
  
  else if ((tension>170)&&(tension<=341)){
    lcd.setCursor(0,0);
    lcd.print("Billie Jean");
    lcd.setCursor(0,1);
    lcd.print("Michael Jackson");
    numeroMusique = 2;
  }

  else if ((341<tension)&&(tension<=511)){
    lcd.setCursor(0,0);
    lcd.print("Nevre Gonna Give You Up");
    lcd.scrollDisplayLeft();
    delay(200);
    lcd.setCursor(0,1);
    lcd.print("Rick Astley");
    numeroMusique = 3;
  }

  else if ((511<tension)&&(tension<=682)){
    lcd.setCursor(0,0);
    lcd.print("The Logical Song");
    lcd.setCursor(0,1);
    lcd.print("Superstramp");
    numeroMusique = 4;
  }

  else if ((682<tension)&&(tension<=852)){
    lcd.setCursor(0,0);
    lcd.print("Everybody Wants to Rule the World");
    lcd.scrollDisplayLeft();
    delay(200);
    lcd.setCursor(0,1);
    lcd.print("Tears For Fears");
    numeroMusique = 5;
  }

  else if ((852<tension)&&(tension<=1023)){
    lcd.setCursor(0,0);
    lcd.print("Total Eclipse of the Heart");
    lcd.scrollDisplayLeft();
    delay(200);
    lcd.setCursor(0,1);
    lcd.print("Bonnie Tyler");
    numeroMusique = 6;
  }
}

void musiqueDisco(){
  tension = analogRead(0);
  
  if ((0<=tension)&&(tension<=170)){
    lcd.setCursor(0,0);
    lcd.print("Girls Just Wanna Have Fun");
    lcd.scrollDisplayLeft();
    delay(200);
    lcd.setCursor(0,1);
    lcd.print("Cyndi Lauper");
    numeroMusique = 1;
  }
  
  else if ((tension>170)&&(tension<=341)){
    lcd.setCursor(0,0);
    lcd.print("Take On Me");
    lcd.setCursor(0,1);
    lcd.print("Aha");
    numeroMusique = 2;
  }

  else if ((341<tension)&&(tension<=511)){
    lcd.setCursor(0,0);
    lcd.print("I Wanna Dance With Somebody");
    lcd.scrollDisplayLeft();
    delay(200);
    lcd.setCursor(0,1);
    lcd.print("Whitney Houston");
    numeroMusique = 3;
  }

  else if ((511<tension)&&(tension<=682)){
    lcd.setCursor(0,0);
    lcd.print("Heart Of Glass");
    lcd.setCursor(0,1);
    lcd.print("Blondie");
    numeroMusique = 4;
  }

  else if ((682<tension)&&(tension<=852)){
    lcd.setCursor(0,0);
    lcd.print("Night Fever");
    lcd.setCursor(0,1);
    lcd.print("Bee Gees");
    numeroMusique = 5;
  }

  else if ((852<tension)&&(tension<=1023)){
    lcd.setCursor(0,0);
    lcd.print("It s Raining Men");
    lcd.setCursor(0,1);
    lcd.print("The Weather Girls");
    numeroMusique = 6;
  }
}

void musiqueMovie(){
  tension = analogRead(0);
  
  if ((0<=tension)&&(tension<=170)){
    lcd.setCursor(0,0);
    lcd.print("The Time Of My Life");
    lcd.scrollDisplayLeft();
    delay(200);
    lcd.setCursor(0,1);
    lcd.print("Dirty Dancing");
    numeroMusique = 1;
  }
  
  else if ((tension>170)&&(tension<=341)){
    lcd.setCursor(0,0);
    lcd.print("Eye Of The Tiger");
    lcd.setCursor(0,1);
    lcd.print("Rocky");
    numeroMusique = 2;
  }

  else if ((341<tension)&&(tension<=511)){
    lcd.setCursor(0,0);
    lcd.print("Johnny Bee Goode");
    lcd.scrollDisplayLeft();
    delay(200);
    lcd.setCursor(0,1);
    lcd.print("Back To The Future");
    numeroMusique = 3;
  }

  else if ((511<tension)&&(tension<=682)){
    lcd.setCursor(0,0);
    lcd.print("Reality");
    lcd.setCursor(0,1);
    lcd.print("La Boum");
    numeroMusique = 4;
  }

  else if ((682<tension)&&(tension<=852)){
    lcd.setCursor(0,0);
    lcd.print("What A Feeling");
    lcd.setCursor(0,1);
    lcd.print("Flashdance");
    numeroMusique = 5;
  }

  else if ((852<tension)&&(tension<=1023)){
    lcd.setCursor(0,0);
    lcd.print("Ghostbusters");
    numeroMusique = 6;
  }
}

void musiqueArcade(){
  tension = analogRead(0);
  
  if ((0<=tension)&&(tension<=170)){
    lcd.setCursor(0,0);
    lcd.print("Pacman");
    numeroMusique = 1;
  }
  
  else if ((tension>170)&&(tension<=341)){
    lcd.setCursor(0,0);
    lcd.print("Super Mario Bros");
    numeroMusique = 2;
  }

  else if ((341<tension)&&(tension<=511)){
    lcd.setCursor(0,0);
    lcd.print("The Legend Of");
    lcd.setCursor(0,1);
    lcd.print("Zelda");
    numeroMusique = 3;
  }

  else if ((511<tension)&&(tension<=682)){
    lcd.setCursor(0,0);
    lcd.print("Tetris");
    numeroMusique = 4;
  }

  else if ((682<tension)&&(tension<=852)){
    lcd.setCursor(0,0);
    lcd.print("Metroid");
    numeroMusique = 5;
  }

  else if ((852<tension)&&(tension<=1023)){
    lcd.setCursor(0,0);
    lcd.print("ExciteBike");
    numeroMusique = 6;
  }
}

void musiqueBestOf(){
  tension = analogRead(0);
  
  if ((0<=tension)&&(tension<=170)){
    lcd.setCursor(0,0);
    lcd.print("Purple Rain");
    lcd.setCursor(0,1);
    lcd.print("Prince");
    numeroMusique = 1;
  }
  
  else if ((tension>170)&&(tension<=341)){
    lcd.setCursor(0,0);
    lcd.print("Beat It");
    lcd.setCursor(0,1);
    lcd.print("Michael Jackson");
    numeroMusique = 2;
  }

  else if ((341<tension)&&(tension<=511)){
    lcd.setCursor(0,0);
    lcd.print("Radio Gaga");
    lcd.setCursor(0,1);
    lcd.print("Queen");
    numeroMusique = 3;
  }

  else if ((511<tension)&&(tension<=682)){
    lcd.setCursor(0,0);
    lcd.print("Careless Whisper");
    lcd.setCursor(0,1);
    lcd.print("George Michael");
    numeroMusique = 4;
  }

  else if ((682<tension)&&(tension<=852)){
    lcd.setCursor(0,0);
    lcd.print("The Final Countdown");
    lcd.scrollDisplayLeft();
    delay(200);
    lcd.setCursor(0,1);
    lcd.print("Europe");
    numeroMusique = 5;
  }

  else if ((852<tension)&&(tension<=1023)){
    lcd.setCursor(0,0);
    lcd.print("Sweet Dreams");
    lcd.setCursor(0,1);
    lcd.print("Annie Lenox");
    numeroMusique = 6;
  }
}

void lireMusiqueRock{

  if (numeroMusique==1){
    
  }

  if (numeroMusique==2){
    
  }

  if (numeroMusique==3){
    
  }

  if (numeroMusique==4){
    
  }

  if (numeroMusique==5){
    
  }

  if (numeroMusique==6){
    
  }
}

void lireMusiquePop{

  if (numeroMusique==1){
    
  }

  if (numeroMusique==2){
    
  }

  if (numeroMusique==3){
    
  }

  if (numeroMusique==4){
    
  }

  if (numeroMusique==5){
    
  }

  if (numeroMusique==6){
    
  }
}

void lireMusiqueDisco{

  if (numeroMusique==1){
    
  }

  if (numeroMusique==2){
    
  }

  if (numeroMusique==3){
    
  }

  if (numeroMusique==4){
    
  }

  if (numeroMusique==5){
    
  }

  if (numeroMusique==6){
    
  }
}

void lireMusiqueMovie{

  if (numeroMusique==1){
    
  }

  if (numeroMusique==2){
    
  }

  if (numeroMusique==3){
    
  }

  if (numeroMusique==4){
    
  }

  if (numeroMusique==5){
    
  }

  if (numeroMusique==6){
    
  }
}

void lireMusiqueArcade{

  if (numeroMusique==1){
    
  }

  if (numeroMusique==2){
    
  }

  if (numeroMusique==3){
    
  }

  if (numeroMusique==4){
    
  }

  if (numeroMusique==5){
    
  }

  if (numeroMusique==6){
    
  }
}

void lireMusiqueBestOf{

  if (numeroMusique==1){
    
  }

  if (numeroMusique==2){
    
  }

  if (numeroMusique==3){
    
  }

  if (numeroMusique==4){
    
  }

  if (numeroMusique==5){
    
  }

  if (numeroMusique==6){
    
  }
}
