
/*
 * Motorcontrol code for Winston animatronic.
 * 
*/

#include <Servo.h>

int Musicread = 13;
int Music;

Servo Eyes;
Servo Upper;
Servo Lower;
int ol1 = 0;
int cl1 = 70;
int ol2 = 45;
int cl2 = 0;
int pos1 = ol1;
int pos2 = ol2;
int sd = 100; //delay in millisec to give a servo time to complete movement
long int previousMillis = 0;
long int interval = 15000; // set eye blink timer in milliseconds
#define Servo1Pin 0
#define Servo2Pin 1
#define Servo3Pin 2  

void setup(){
  // Servo setup
  Eyes.attach(Servo1Pin);
  Upper.attach(Servo2Pin);
  Lower.attach(Servo3Pin);
  Eyes.write(pos1);
  Upper.write(pos2);
  Lower.write(pos2);
  }

void loop(){
  //Set timer for eyeblinks (every 15 seconds)
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > interval){
    previousMillis = currentMillis;
    eyeBlink();
  } 
  
  //Read audio value from analog pin.
  //If the value is greater than 1, run the large movement talk script
}

// Large movement talk script (opens mouth a lot)
void talk()
{
   for(pos2 = ol2; pos2 >= cl2; pos2 -= 5) // goes from ol2 to cl2
  {                                     // in steps of 1 degree 
    Upper.write(pos2);                  // tell upper mouth servo to go to position 'pos2' 
    Lower.write(pos2);                  // tell lower mouth servo to go to position 'pos2'
    delay(10);
  }
  delay(sd);
  for(pos2 = cl2; pos2 <= ol2; pos2 += 5)  // goes from cl2 degrees to ol2
  {                                     // in steps of 1 degree
    Upper.write(pos2);                  // tell upper mouth servo to go to position 'pos2' 
    Lower.write(pos2);                  // tell lower mouth servo to go to position 'pos2'
    delay(10);
  }
  delay(sd);                          // wait for the servo to reach the final position 
}
//Eye blink script
void eyeBlink()
{
  for(pos1 = ol1; pos1 <= cl1; pos1 += 5)
  {
    Eyes.write(pos1);
    delay(10);
  }
  delay(sd);
  for(pos1 = cl1; pos1 >= ol1 ; pos1 -= 5)
  {                                
    Eyes.write(pos1);
    delay(10);
  }
  delay(sd);
}
