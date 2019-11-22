#include <Servo.h>
int Musicread = 13;
int Music;
Servo Eyes;
Servo Nose;
Servo Mouth;
int pos = 10;
int pos2 = 20;
int pos3 = 10;

long previousMillis = 0;
long interval = 15000; // timer is set to 15 second intervals
#define Servo1Pin 12
#define Servo2Pin 11
#define Servo3Pin 10  

void setup()
{
  pinMode(13, INPUT);
  digitalWrite(13, LOW);
  Eyes.attach(Servo1Pin);
  Nose.attach(Servo2Pin);
  Mouth.attach(Servo3Pin);
  Eyes.write(0);
  Nose.write(40);
  Mouth.write(40);
  Eyes.detach();
  Nose.detach();
  Mouth.detach();
}

void loop()
{
  //Set timer for eyeblinks (every 15 seconds)
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > interval){
    previousMillis = currentMillis;
    Eyes.attach(Servo1Pin);
    eyeBlink();
    Eyes.detach();
  } 
  //Read audio value from analog pin.
  //If the value equals 1, run the small movement talk script
  //If the value is greater than 1, rin the large movement talk script
  //Otherwise, set everything back to its original value.
  Music = digitalRead(Musicread);
  delay(10);
  if (Music == 1){
    Nose.attach(Servo2Pin);
    Mouth.attach(Servo3Pin);
    talk();
    delay(10);
  } else {
    Nose.write(40);
    Mouth.write(40);
    delay(10);
    Nose.detach();
    Mouth.detach();
  }
}

//Large movement talk script (opens mouth a lot)
void talk()
{
   for(pos = 40; pos > 5; pos -= 5)  // goes from 90 degrees to 50 degrees 
  {                                  // in steps of 1 degree 
    Nose.write(pos);              // tell servo to go to position in variable 'pos' 
    Mouth.write(pos);
    delay(10);                       // waits 15ms for the servo to reach the position 
  }
  for(pos = 5; pos < 40; pos += 5)     // goes from 180 degrees to 0 degrees 
  {                                
    Nose.write(pos);              // tell servo to go to position in variable 'pos' 
    Mouth.write(pos);
    delay(10);                       // waits 15ms for the servo to reach the position 
  } 
}
//Eye blink script
void eyeBlink()
{
  for(pos3 = 0; pos3 < 70; pos3 += 10)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    Eyes.write(pos3);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos3 = 70; pos3 >= 0 ; pos3 -= 10)     // goes from 180 degrees to 0 degrees 
  {                                
    Eyes.write(pos3);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
}
