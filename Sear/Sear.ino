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

const int MODO_TESTING=0;
const int MODO_MANTENIMIENTO=1;
const int MODO_NORMAL=2;

int MODO=MODO_TESTING;



void setup(){
  Serial.begin(9600);
  setupChequearHoraComida();
  setupLCD();
  //setupKeyPad();
  setupServo();
  setupMenuBotonera();
}

void loop() {
  switch(MODO){
    case MODO_TESTING:{
      startModoTesting();
      break;
    }
    case MODO_NORMAL:{
      startMenuBotonera();   
      break;
    }
    case MODO_MANTENIMIENTO:{
      //Pendiente
      break;
    }
    default:{
      MODO=MODO_NORMAL;
    }
  }
}





