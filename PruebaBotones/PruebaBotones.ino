#include <Bounce2.h>


const byte PIN_FLECHA_ABAJO = 26; 
const byte PIN_FLECHA_ARRIBA = 24; 
const byte PIN_LINEA_DOWN = 22; 

Bounce bounce;
void setup() {
  //bounce=Bounce();
  Serial.begin(9600);
//  bounce.attach(PIN_FLECHA_ARRIBA);
  pinMode(PIN_FLECHA_ARRIBA, INPUT_PULLUP); 
  pinMode(PIN_FLECHA_ABAJO, INPUT_PULLUP); 
  pinMode(PIN_LINEA_DOWN, OUTPUT); 
  digitalWrite(PIN_LINEA_DOWN,LOW);

}

void loop() {
  // put your main code here, to run repeatedly:
  int pressArriba=digitalRead(PIN_FLECHA_ARRIBA);
  int pressAbajo=digitalRead(PIN_FLECHA_ABAJO);
  //int dato=bounce.read();
  //Serial.println(dato);
  if(pressAbajo==LOW){
    Serial.println("abajo");
    delay(500);
  }  
  if(pressArriba==LOW){
    Serial.println("arriba");
    delay(500);
  }
  //delay(2000);
}
