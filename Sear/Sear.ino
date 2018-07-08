#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>
#include <pitches.h>

/**
 * INFO sobre como utilizar TIME
 * https://github.com/PaulStoffregen/Time
 */
#include <Time.h>
#include <TimeLib.h>



bool keyEventPressed=false;

void setup(){
  Serial.begin(9600);
  setupChequearHoraComida();
  setupLCD();
  //setupKeyPad();
  setupServo();
  setupMenuBotonera();
}

void loop() {
//  startMenu();
 // startKeyPad();
 startMenuBotonera();
// printLcd("Bienvenido","hora actual");
  
}

