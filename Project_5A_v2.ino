//**** add 1 button and 1 light
// Note: Deleted the flash portion because traffic lights dont flash before they change in most applications
//       Additonally, the code was causing a ton of unintended behavior so it got scrapped
//       Updated to use more complex logic because apparently functional isn't good enough
//       Check github https://github.com/ColtonKelsen/Project5Micro2
//       Warning: do not swap lights too quickly; due to hardware limitations it can cause temporary erratic behavior
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

boolean trafficWest = true;  // west = true, east = false. in v3 This is removed and replaced with a character input to determine function call behaviors
int flowTime = 10000; // Edited Values for testing purposes
int changeDelay = 2000; // Edited Values for testing purposes
int pedFlowTime = 10000; // Edited Values for testing purposes



void setup() { //Setup 
  pinMode(westButton, INPUT);
  pinMode(eastButton, INPUT);
  pinMode(westRed, OUTPUT);
  pinMode(westYellow, OUTPUT);
  pinMode(westGreen, OUTPUT);
  pinMode(eastRed, OUTPUT);
  pinMode(eastYellow, OUTPUT);
  pinMode(eastGreen, OUTPUT);
  pinMode(pedButton, INPUT); //new component
  pinMode(pedLight, OUTPUT); //new component
// dictating inputs/outputs ^
// dictating initial states v

  digitalWrite(westRed, LOW);
  digitalWrite(westYellow, LOW);
  digitalWrite(westGreen, HIGH);
  digitalWrite(eastRed, HIGH);
  digitalWrite(eastYellow, LOW);
  digitalWrite(eastGreen, LOW);
}

void loop() { 
  //start west
  if (digitalRead(westButton) == HIGH) { // only run when traffic west
    if (trafficWest != true) { 
      trafficWest = true;
      delay(flowTime); //flow
      digitalWrite(eastGreen, LOW);
      digitalWrite(eastYellow, HIGH); //bring east to yellow
      delay(changeDelay);
      digitalWrite(eastYellow, LOW);
      digitalWrite(eastRed, HIGH); //bring east to red
      delay(changeDelay);
      digitalWrite(westYellow, LOW);
      digitalWrite(westRed, LOW);
      digitalWrite(westGreen, HIGH); //activate west
    }
  }
  //start pedestrian
  if (digitalRead(pedButton) == HIGH) { 
    if (trafficWest != true) { //Only run when traffic is east
      delay(changeDelay);
      digitalWrite(eastGreen, LOW);
      digitalWrite(eastYellow, HIGH);
      delay(changeDelay);
      digitalWrite(eastYellow, LOW);
      digitalWrite(eastRed, HIGH);
      delay(changeDelay);  // East goes red
    } 
    else if (trafficWest == true) { //Only run when traffic is west
      delay(changeDelay);
      digitalWrite(westGreen, LOW);
      digitalWrite(westYellow, HIGH);
      delay(changeDelay);
      digitalWrite(westYellow, LOW);
      digitalWrite(westRed, HIGH);
      delay(changeDelay);  //West goes red
    }
      // This code runs regardless of direction    
    digitalWrite(pedLight, HIGH);
    delay(pedFlowTime);
    digitalWrite(pedLight, LOW);
    trafficWest = true; //west goes firt
    digitalWrite(eastYellow, LOW);
    digitalWrite(eastRed, LOW);
    digitalWrite(eastGreen, HIGH);  // turn traffic back on
  } 
  // end pedestrian
  // start east
  if (digitalRead(eastButton) == HIGH) { //Only run when traffic is east
    if (trafficWest == true) {  //
      trafficWest = false;
      delay(flowTime);
      digitalWrite(westGreen, LOW);
      digitalWrite(westYellow, HIGH);
      delay(changeDelay);
      digitalWrite(westYellow, LOW);
      digitalWrite(westRed, HIGH);
      delay(changeDelay);
      digitalWrite(eastYellow, LOW);
      digitalWrite(eastRed, LOW);
      digitalWrite(eastGreen, HIGH);
    }
  }
}
// *Note: trafficWest variable check is implemented to dictate the pedestrian button behavior since double-checking is apparently not good enough.