// Project 5 part C: Implementing functions to divide and conquer



// constant definitions (somehow different from global variables?)
#define westButton 3
#define eastButton 13
#define westRed 2
#define westYellow 1
#define westGreen 0
#define eastRed 12
#define eastYellow 11
#define eastGreen 10
#define pedButton 9
#define pedLight 8

// ****** VARIABLE INITIALIZATION ****** /

bool trafficWest = true;  // Only really needed for Pedestrians, can likely be removed. Same logic as v1; west = true, east = false
int flowTime = 10000;     // for both pedestrians and cars
int changeDelay = 2000;   // same value we always used
char direction;           // variable used to occupy the function inputs
// edit: Removed pedFlowTime in this version so we dont have to have too many variables
// note; likely need a direction variable apart from our input variable so we don't cross too many wires, unknown for sure though


// Pin function setups
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
  // intial state
  digitalWrite(westRed, LOW);
  digitalWrite(westYellow, LOW);
  digitalWrite(westGreen, HIGH);
  digitalWrite(eastRed, HIGH);
  digitalWrite(eastYellow, LOW);
  digitalWrite(eastGreen, LOW);
}

// Starting traffic
void startTraffic(char direction) {  // accepts a character input for the direction. West is W and East is E

  if (direction == 'E') {
    delay (changeDelay);
    digitalWrite(eastYellow, LOW);
    digitalWrite(eastRed, LOW);
    digitalWrite(eastGreen, HIGH);
    trafficWest = false; // cleanup variable garbage
  }

  if (direction == 'W') {
    delay (changeDelay);
    digitalWrite(westYellow, LOW);
    digitalWrite(westRed, LOW);
    digitalWrite(westGreen, HIGH);
    trafficWest = true; //cleanup variable garbage
  }
}

// Stopping traffic
void stopTraffic(char direction) {  // accepts a character input for the direction. West is W and East is E
  if (direction == 'W') {
    delay(flowTime); //keeping flowTime on stop makes sure it only initiates a cycle when it detects traffic on the otherside. Elsewise it remains static
    digitalWrite(westGreen, LOW);     // beyond this line until end of function is just the ending part of the traffic cycle; yellow, then red
    digitalWrite(westYellow, HIGH);
    delay(changeDelay);
    digitalWrite(westYellow, LOW);
    digitalWrite(westRed, HIGH);
    delay(changeDelay);
  }
  if (direction == 'E') {
    delay(flowTime); //keeping flowTime on stop makes sure it only initiates a cycle when it detects traffic on the otherside. Elsewise it remains static
    digitalWrite(eastGreen, LOW);     // beyond this line until end of function is just the ending part of the traffic cycle; yellow, then red
    digitalWrite(eastYellow, HIGH);
    delay(changeDelay);
    digitalWrite(eastYellow, LOW);
    digitalWrite(eastRed, HIGH);
    delay(changeDelay);
  }
}

// What if... pedestrian
void pedestrian() {
  if (trafficWest) { // check direction
    stopTraffic('W'); //stop directional traffic
  } 
  if (trafficWest != true) { // check direction
    stopTraffic('E'); //stop directional traffic
  }
  delay(changeDelay);
  digitalWrite(pedLight, HIGH);
  delay(flowTime * 1.5); //chosen to be a function of regulr flowTime so if traffic moves slower then pedesrins can also have more time
  delay(changeDelay);
  digitalWrite(pedLight, LOW);
  if (trafficWest) { // resume traffic flow from the last flow state
    startTraffic('W');
  } 
  if (trafficWest != true) { //resume traffic flow from the last flow state
    startTraffic('E');
  }
}

//Actual calling of functions down below
void loop() {
  if (digitalRead(westButton) == HIGH) { // When West traffic arrives
    stopTraffic('E'); //trigger to stop east
    delay(changeDelay);
    startTraffic('W'); // begin west
  }
  if (digitalRead(pedButton) == HIGH) { // When Pedestrian arrives
    delay(changeDelay);
    pedestrian(); //if pedestrian detected
  }
  if (digitalRead(eastButton) == HIGH) { // When East traffic arrives
    stopTraffic('W'); // trigger to stop west
    delay(changeDelay);
    startTraffic('E'); // begin east
  }
}


// Signed off as Rowan (The artist formerly known as Colton)