//**** add 1 button and 1 light
// Note: Deleted the flash portion because traffic lights dont flash before they change
//       Additonally, the code was causing a ton of unintended behavior so it got scrapped 
//       Updated to use more complex logic because apparently functional isn't good enough
//       Check github https://github.com/ColtonKelsen/Project5Micro2
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

boolean trafficWest = true; // west = true, east = false
int flowTime = 4000;
int changeDelay = 1000;
int pedFlowTime = 4000;



void setup()
{
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

void loop()
{
  if ( digitalRead(westButton) == HIGH)
  {
    if ( trafficWest != true)
    {
      trafficWest = true;
      delay(flowTime);
      digitalWrite(eastGreen, LOW);

      digitalWrite(eastYellow, HIGH);
      delay(changeDelay);
      digitalWrite(eastYellow, LOW);
      digitalWrite(eastRed, HIGH);
      delay(changeDelay);
      digitalWrite(westYellow, LOW);
      digitalWrite(westRed, LOW);
      digitalWrite(westGreen, HIGH);

    }
  }
  if (digitalRead(pedButton) == HIGH)
  {
     if ( trafficWest != true)
    { 
      delay(changeDelay);
      digitalWrite(eastGreen, LOW);
      digitalWrite(eastYellow, HIGH);
      delay(changeDelay);
      digitalWrite(eastYellow, LOW);
      digitalWrite(eastRed, HIGH);
      delay(changeDelay);// East goes red







    }
    else if ( trafficWest == true)
    {
      delay(changeDelay);
      digitalWrite(westGreen, LOW);
      digitalWrite(westYellow, HIGH);
      delay(changeDelay);
      digitalWrite(westYellow, LOW);
      digitalWrite(westRed, HIGH);
      delay(changeDelay); //West goes red



     
            

    }
      digitalWrite(pedLight, HIGH);
      delay(pedFlowTime);
      digitalWrite (pedLight, LOW);
      trafficWest = true;
      
      digitalWrite(eastYellow, LOW);
      digitalWrite(eastRed, LOW);
      digitalWrite(eastGreen, HIGH); // turn traffic back
  }
  if ( digitalRead(eastButton) == HIGH)
  {
    if ( trafficWest == true)
    {
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
