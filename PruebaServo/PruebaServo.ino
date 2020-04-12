#include <Servo.h>
int CERRADO=180;
int ABIERTO=0;

char pin=A0;
Servo myservo;
int degrees=0;

void setupServo(){
   myservo.attach(pin);
}

void sweepServo() {
    myservo.write(ABIERTO); 
    delay(1000);
    myservo.write(CERRADO); 
    delay(5000);
//    if(degrees==0)degrees=180;
//    else degrees=0;
//    myservo.write(degrees); 
    delay(2000);
    /*degrees=180;*/
}

void setup() {
 setupServo();

}

void loop() {
  sweepServo();
}
