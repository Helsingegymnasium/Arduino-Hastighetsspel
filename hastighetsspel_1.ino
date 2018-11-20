int light0 = 0; //vi ger var sin lampa i vår 4x4 grid en variabel för dess portar
int light1 = 1;
int light2 = 2;
int light3 = 3;
int light4 = 4;
int light5 = 5;
int light6 = 6;
int light7 = 7;
int light8 = 8;
int light9 = 9;
int light10 = 10;
int light11 = 11;
int light12 = 12;
int light13 = 13;
int light14 = 18;
int light15 = 19;

int twistPin = A0; //porten för rotary switchen

int buttonOne = 15; //portarna för de tre knapparna
int buttonTwo = 16;
int buttonThree = 17;

int rotValue; //variabler för väljaren
int rotStatus;
int lastStatus;

int lastInputOne; //färdiga variabler för speedgame()
int lastInputTwo;
int lastInputStart;
int gameActive = 0;
int scoreOne;
int scoreTwo;


void setup() {
  pinMode(light0, OUTPUT);
  pinMode(light1, OUTPUT);
  pinMode(light2, OUTPUT);
  pinMode(light3, OUTPUT);
  pinMode(light4, OUTPUT);
  pinMode(light5, OUTPUT);
  pinMode(light6, OUTPUT);
  pinMode(light7, OUTPUT);
  pinMode(light8, OUTPUT);
  pinMode(light9, OUTPUT);
  pinMode(light10, OUTPUT);
  pinMode(light11, OUTPUT);
  pinMode(light12, OUTPUT);
  pinMode(light13, OUTPUT);
  pinMode(light14, OUTPUT);
  pinMode(light15, OUTPUT);

  pinMode(buttonOne, INPUT_PULLUP);
  pinMode(buttonTwo, INPUT_PULLUP);
  pinMode(buttonThree, INPUT_PULLUP);

  //Serial.begin(9600); //alla Serial-kommandon är kommenterade pga vi använder portarna 0 och 1 för ljus
}

void loop() {
  rotValue = analogRead(twistPin); //variablen rotValue visar analogvärdet
  rotStatus = map(rotValue, 0, 1023, 0, 3); //och rotStatus mappar den till 4 olika värden från 0 till 3
    
    if(rotStatus == 0) { //vi testar för switchens 4 olika värden
      turnOff(); //programmets "Off-mode"
    }
    
    if(rotStatus == 1) {
      speedGame(); //det första spelet, ett enkelt snabbhetstest med 2 spelare
    }

    if(rotStatus == 2) {
      memoryGame(); //inte ännu gjort minnespel
    }

    if(rotStatus == 2) {
      reactionGame(); //inte ännu gjort reaktionspel
    }
    //Serial.println(rotStatus);
    delay(10); //en liten delay för att sakta ner serialmonitorn vid testing
  }

void turnOff() { //denna funktion släcker alla ljus förutom en, som indikerar att inget spel är aktivt
  digitalWrite(light0, LOW);
  digitalWrite(light1, LOW);
  digitalWrite(light2, LOW);
  digitalWrite(light3, HIGH);
  digitalWrite(light4, LOW);
  digitalWrite(light5, LOW);
  digitalWrite(light6, LOW);
  digitalWrite(light7, LOW);
  digitalWrite(light8, LOW);
  digitalWrite(light9, LOW);
  digitalWrite(light10, LOW);
  digitalWrite(light11, LOW);
  digitalWrite(light12, LOW);
  digitalWrite(light13, LOW);
  digitalWrite(light14, LOW);
  digitalWrite(light15, LOW);

  //Serial.print("Off.");
  delay(100);
}

void speedGame() { //det första spelet i programmet
  
  int inputOne = digitalRead(buttonOne); //vi ger varje knapp var sin variabel
  int inputTwo = digitalRead(buttonThree);
  int startButton = digitalRead(buttonTwo);

  //Serial.println(inputOne);
  //Serial.println(inputTwo);
  //Serial.println(startButton);

  if(lastInputStart != startButton) { //if-satsen inverterar gameActive-variabeln från 0 till 1 och från 1 till 0 när knappen trycks
      if(startButton == 0) {
        gameActive = !gameActive;
        //Serial.println(gameActive);
      }
    lastInputStart = startButton;
  }

  if(gameActive == 1) { //testar för om startknappen har tryckts
    digitalWrite(light0, HIGH); //byter ljus för att visa att spelet är i gång
    digitalWrite(light1, LOW);
    
    if(lastInputOne != inputOne) { //varje klick av knappen adderar +1 till score-variablerna för var sin spelare
      if(inputOne == 0) {
        scoreOne = scoreOne + 1;
        //Serial.println(scoreOne);
      }
      lastInputOne = inputOne;
    }

    if(lastInputTwo != inputTwo) {
      if(inputTwo == 0) {
        scoreTwo = scoreTwo + 1;
        //Serial.println(scoreTwo);
      }
      lastInputTwo = inputTwo;
    }
  }

  if(gameActive == 1) { //vi testar för spelets läge efter 5 sekunder och tänder den vinnande sidans ljus
    
    delay(5000);
    
    if(scoreOne > scoreTwo) {
      digitalWrite(light0, HIGH);
      digitalWrite(light1, HIGH);
      digitalWrite(light2, LOW);
      digitalWrite(light3, LOW);
      digitalWrite(light4, HIGH);
      digitalWrite(light5, HIGH);
      digitalWrite(light6, LOW);
      digitalWrite(light7, LOW);
      digitalWrite(light8, HIGH);
      digitalWrite(light9, HIGH);
      digitalWrite(light10, LOW);
      digitalWrite(light11, LOW);
      digitalWrite(light12, HIGH);
      digitalWrite(light13, HIGH);
      digitalWrite(light14, LOW);
      digitalWrite(light15, LOW);
    }
    
    if(scoreTwo > scoreOne) {
      digitalWrite(light0, LOW);
      digitalWrite(light1, LOW);
      digitalWrite(light2, HIGH);
      digitalWrite(light3, HIGH);
      digitalWrite(light4, LOW);
      digitalWrite(light5, LOW);
      digitalWrite(light6, HIGH);
      digitalWrite(light7, HIGH);
      digitalWrite(light8, LOW);
      digitalWrite(light9, LOW);
      digitalWrite(light10, HIGH);
      digitalWrite(light11, HIGH);
      digitalWrite(light12, LOW);
      digitalWrite(light13, LOW);
      digitalWrite(light14, HIGH);
      digitalWrite(light15, HIGH);
    }
    
    if(scoreOne == scoreTwo) { //om spelet blir jämnt tänds var andra lampa på brädet
      digitalWrite(light0, HIGH);
      digitalWrite(light1, LOW);
      digitalWrite(light2, HIGH);
      digitalWrite(light3, LOW);
      digitalWrite(light4, LOW);
      digitalWrite(light5, HIGH);
      digitalWrite(light6, LOW);
      digitalWrite(light7, HIGH);
      digitalWrite(light8, HIGH);
      digitalWrite(light9, LOW);
      digitalWrite(light10, HIGH);
      digitalWrite(light11, LOW);
      digitalWrite(light12, LOW);
      digitalWrite(light13, HIGH);
      digitalWrite(light14, LOW);
      digitalWrite(light15, HIGH);
    }
    
    delay(3000); //efter att ljusen har visats för 3 sekunder sätts spelet i det oaktiva läget och ställs om
    gameActive = 0;
  }

  if(gameActive == 0) { //när spelet är i oaktivt läge släcks alla ljus förutom statusljuset och poängen ställs om
    scoreOne = 0;
    scoreTwo = 0;
    digitalWrite(light0, LOW);
    digitalWrite(light1, HIGH);
    digitalWrite(light2, LOW);
    digitalWrite(light3, LOW);
    digitalWrite(light4, LOW);
    digitalWrite(light5, LOW);
    digitalWrite(light6, LOW);
    digitalWrite(light7, LOW);
    digitalWrite(light8, LOW);
    digitalWrite(light9, LOW);
    digitalWrite(light10, LOW);
    digitalWrite(light11, LOW);
    digitalWrite(light12, LOW);
    digitalWrite(light13, LOW);
    digitalWrite(light14, LOW);
    digitalWrite(light15, LOW);
  }

}

void memoryGame() { //färdiga definitioner för andra spel man kunde programmera
  
}

void reactionGame() {
  
}
