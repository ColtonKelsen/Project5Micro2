//**** add 2 buttons and 2 lights
#define westButton 3
#define eastButton 13
#define westRed 2
#define westYellow 1
#define westGreen 0
#define eastRed 12
#define eastYellow 11
#define eastGreen 10
#define pedButton 9
#define yellowBlinkTime 500
#define pedLight 8

//boolean trafficWest = true; // west = true, east = false
int flowTime = 10000;
int changeDelay = 2000;
char direction;


void setup() {
  pinMode(westButton, INPUT);
  pinMode(eastButton, INPUT);
  pinMode(westRed, OUTPUT);
  pinMode(westYellow, OUTPUT);
  pinMode(westGreen, OUTPUT);
  pinMode(eastRed, OUTPUT);
  pinMode(eastYellow, OUTPUT);
  pinMode(eastGreen, OUTPUT);
  pinMode(pedButton, INPUT);
  pinMode(pedLight, OUTPUT);



  digitalWrite(westRed, LOW);
  digitalWrite(westYellow, LOW);
  digitalWrite(westGreen, HIGH);
  digitalWrite(eastRed, HIGH);
  digitalWrite(eastYellow, LOW);
  digitalWrite(eastGreen, LOW);
}
void startTraffic(char direction) {
  if (direction == 'E') {
    for (int a = 0; a < 5; a++) {
      digitalWrite(eastYellow, LOW);
      delay(yellowBlinkTime);
      digitalWrite(eastYellow, HIGH);
      delay(yellowBlinkTime);
    }
    digitalWrite(eastYellow, LOW);
    digitalWrite(eastRed, LOW);
    digitalWrite(eastGreen, HIGH);
  }

  if (direction == 'W') {
    for (int a = 0; a < 5; a++) {
      digitalWrite(westYellow, LOW);
      delay(yellowBlinkTime);
      digitalWrite(westYellow, HIGH);
      delay(yellowBlinkTime);
    }
    digitalWrite(westYellow, LOW);
    digitalWrite(westRed, LOW);
    digitalWrite(westGreen, HIGH);
  }
}
void stopTraffic(char direction) {
  if (direction == 'W') {
    delay(flowTime);
    digitalWrite(westGreen, LOW);
    digitalWrite(westYellow, HIGH);
    delay(changeDelay);
    digitalWrite(westYellow, LOW);
    digitalWrite(westRed, HIGH);
    delay(changeDelay);
  }
  if (direction == 'E') {
    delay(flowTime);
    digitalWrite(eastGreen, LOW);
    digitalWrite(eastYellow, HIGH);
    delay(changeDelay);
    digitalWrite(eastYellow, LOW);
    digitalWrite(eastRed, HIGH);
    delay(changeDelay);
  }
}
void pedestrian() {
    delay(750);
    stopTraffic('E');
    stopTraffic('W');
    delay(changeDelay);
    digitalWrite(pedLight, HIGH);
    delay(flowTime * 1.5);
    digitalWrite(pedLight, LOW);
  
}
void loop() {
  if (digitalRead(westButton) == HIGH) {
    stopTraffic('E');
    delay(changeDelay);
    startTraffic('W'); 
  }
  if (digitalRead(pedButton) == HIGH) {
    delay(changeDelay);
    pedestrian();
    delay(changeDelay);
  }    
  if (digitalRead(eastButton) == HIGH) {
    stopTraffic('W');
    delay(changeDelay);
    startTraffic('E');
  }
}
