const int bouton1 = 2;
const int bouton2 = 3;
const int bouton3 = 4;
const int bouton4 = 5;
const int bouton5 = 6;
const int bouton6 = 7;
const int boutonOK = 8;
const int boutonRETOUR = 9;


void setup() {
  // put your setup code here, to run once:
  pinMode(bouton1, INPUT);
  pinMode(bouton2, INPUT);
  pinMode(bouton3, INPUT);
  pinMode(bouton4, INPUT);
  pinMode(bouton5, INPUT);
  pinMode(bouton6, INPUT);
  pinMode(boutonOK, INPUT);
  pinMode(boutonRETOUR, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int val1 = digitalRead(bouton1);
  int val2 = digitalRead(bouton2);
  int val3 = digitalRead(bouton3);
  int val4 = digitalRead(bouton4);
  int val5 = digitalRead(bouton5);
  int val6 = digitalRead(bouton6);
  int valOK = digitalRead(boutonOK);
  int valRETOUR = digitalRead(boutonRETOUR);

  // code captage pièce insérée ... si captage pièce :
  // l'écran LCD affiche le message correspondant, puis :
  if(val1 == LOW) {
    // l'écran LCD affiche le genre, puis :
    if (valOK == LOW) {
      // l'écran LCD affiche le message correspondant, puis :
      val1 = HIGH;
      valOK = HIGH;
      val1 = digitalRead(bouton1);
      digitalRead(boutonOK);
      
    }
  }
  else if(val2 == LOW) {
    
  }
  else if(val3 == LOW) {
    
  }
  else if(val4 == LOW) {
    
  }
  else if(val5 == LOW) {
    
  }
  else if(val6 == LOW) {
    
  }
  else if(valOK == LOW) {
    
  }
  else if(valRETOUR == LOW) {
    
  }
}
