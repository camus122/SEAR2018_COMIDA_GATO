char pin=A0;
Servo myservo;
int degrees=0;

void setupServo(){
   myservo.attach(pin);
}

void sweepServo() {
    myservo.write(degrees); 
    delay(3000);
    if(degrees==0)degrees=180;
    else degrees=0;
}
