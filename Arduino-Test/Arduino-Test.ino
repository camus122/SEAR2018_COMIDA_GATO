#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Servo.h>
bool keyEventPressed=false;

void setup(){
  Serial.begin(9600);
  setupLCD();
  setupKeyPad();
  setupServo();
}

void loop() {
  //startMenu();
  startKeyPad();

  //Print milisegundos
  if(keyEventPressed==false){
    String mil=String(millis()/1000);
    Serial.println(mil);
    printLcdLine2(mil);  
  }

  
  
}

