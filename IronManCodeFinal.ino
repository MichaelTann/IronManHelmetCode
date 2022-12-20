)
#include <VarSpeedServo.h>

VarSpeedServo myservo;
VarSpeedServo myservo2;

int servostate=0;
int buttonNew;
int buttonOld=1;
int dt = 100;
int LEDvalue;

//Pins Define
const int servo1pin = 9;
const int servo2pin = 10;
int buttonpin=12;
int LEDeyesRpin=3;
int LEDeyesLpin=6;

//Servo Speeds
const int fast = 255;
const int medium = 170;
const int slow = 140;

//Servo Positions
int Servo1pos1 = 155; // Open
int Servo1pos2 = 15;  // Closed
int Servo2pos1 = 30;  // Open  
int Servo2pos2 = 165; // Closed

void setup() {
  myservo.write(Servo1pos1,slow,false); //default open
  myservo2.write(Servo2pos1,slow,false);
  myservo.attach(servo1pin);  // attaches the servo on pin 9 to the servo object
  myservo2.attach(servo2pin);
  pinMode(buttonpin, INPUT);
  pinMode(LEDeyesRpin, OUTPUT);
  pinMode(LEDeyesLpin, OUTPUT);
}


//Main Code

void loop() {
  buttonNew = digitalRead(buttonpin);
  if (buttonOld == 0 && buttonNew == 1)
  {
    if (servostate == 0){ //close helmet
      closehelmet();
      FadeLEDeyeson();
      servostate = 1;
    }
    else{//open helmet
      dimLEDeyes();
      openhelmet();
      servostate = 0;
    }
  }
  buttonOld = buttonNew;
  delay(dt);
}


//Functions

void dimLEDeyes(){
  for (LEDvalue=255;LEDvalue>=0;LEDvalue--){
    analogWrite(LEDeyesRpin, LEDvalue);
    analogWrite(LEDeyesLpin, LEDvalue);
    delay(3);
  }
}

void FadeLEDeyeson(){
  for (LEDvalue = 0;LEDvalue<=255;LEDvalue++){
    analogWrite(LEDeyesRpin, LEDvalue);
    analogWrite(LEDeyesLpin, LEDvalue);
    delay(3);
  }
}

void LEDeyeson(){
  digitalWrite(LEDeyesRpin, HIGH);
  digitalWrite(LEDeyesLpin, HIGH);
}

void closehelmet(){
  myservo.write(Servo1pos2,slow,false);
  myservo2.write(Servo2pos2,slow,false);
  delay(500);
}

void openhelmet(){
  delay(30);
  myservo.write(Servo1pos1,fast,false);
  myservo2.write(Servo2pos1,fast,false);
}
