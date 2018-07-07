#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>
#include <pitches.h>

bool keyEventPressed=false;

void setup(){
  Serial.begin(9600);
  setupLCD();
  //setupKeyPad();
  //setupServo();
  setupMenuBotonera();
}

void loop() {
//  startMenu();
 // startKeyPad();
 startMenuBotonera();
// printLcd("Bienvenido","hora actual");
  
}

