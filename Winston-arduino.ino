
/*
   Motorcontrol code for Winston animatronic.

*/

#include <Servo.h>
#include <Adafruit_DotStar.h>
#define NUMPIXELS 1
#define DATAPIN 7
#define CLOCKPIN 8

Adafruit_DotStar strip = Adafruit_DotStar(
  NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BGR);

String inputString = "";

Servo Eyes;
Servo Nose;
Servo Mouth;
int openeyes = 0;
int closedeyes = 70;
int openmouth = 0;
int closedmouth = 45;
int eyeposition = openeyes;
int mouthposition = closedmouth;
int oldmouthposition = mouthposition;
int number_of_blinks = 0;
int sd = 10; //delay in millisec to give a servo time to complete movement
#define Servo1Pin 0
#define Servo2Pin 1
#define Servo3Pin 2
long int previousMillis = 0;
long int interval = 15000; // set eye blink timer in milliseconds

void setup() {
  inputString.reserve(200);
  strip.begin();
  strip.show();
  // Servo setup
  Eyes.attach(Servo1Pin);
  Nose.attach(Servo2Pin);
  Mouth.attach(Servo3Pin);
  Eyes.write(closedeyes);
  Eyes.write(openeyes);
  Nose.write(openmouth);
  Mouth.write(openmouth);
  Nose.write(closedmouth);
  Mouth.write(closedmouth);

  Serial1.begin(9600);
  while (!Serial1) {
    ; // wait
  }
}

void loop() {
  action0();
  action1();
  action2();
  action3();
}

void action0() {
  if (Serial1.available()) {
    inputString = Serial1.readStringUntil('\n');
    Serial.println(inputString);
  }
}

void action1() {
  if (inputString.equals("system.version")) {
    Serial1.println("Command: system.version");
    inputString = "";
  }
}

void action2() {
  if (inputString.equals("mouth.viseme=0")) {
    oldmouthposition = mouthposition;
    talk(0);
    inputString = "";
  }
  else if ((inputString.equals("mouth.viseme=1")) || (inputString.equals("mouth.viseme=4"))) {
    oldmouthposition = mouthposition;
    talk(45);
    inputString = "";
  }
  else if ((inputString.equals("mouth.viseme=2")) || (inputString.equals("mouth.viseme=5"))) {
    oldmouthposition = mouthposition;
    talk(15);
    inputString = "";
  }
  else if ((inputString.equals("mouth.viseme=3")) || (inputString.equals("mouth.viseme=6"))) {
    oldmouthposition = mouthposition;
    talk(30);
    inputString = "";
  }
  else if (inputString.equals("mouth.reset")) {
    oldmouthposition = mouthposition;
    talk(closedmouth);
    inputString = "";
  }
}

void action3() {
  if (inputString.startsWith("eyes.blink")) {
    eyeBlink(closedeyes);
    eyeBlink(openeyes);
    inputString = "";
  }
}

void talk(int mouthposition) {
  Nose.write(mouthposition);
  Mouth.write(mouthposition);
  delay(abs(mouthposition - oldmouthposition) * (sd / 5));
}

void eyeBlink(int eyeposition) {
  Eyes.write(eyeposition);
  delay(100);
}
