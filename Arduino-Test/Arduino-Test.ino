#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Servo.h>
bool keyEventPressed=false;

void setup(){
  Serial.begin(9600);
  setupLCD();
  //setupKeyPad();
  //setupServo();
  setupMenuBotonera();
}

void loop() {
  //startMenu();
 // startKeyPad();
 startMenuBotonera();
  
}

