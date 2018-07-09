char PIN_SERVO=A0;
Servo myservo;
int degrees=0;

int SERVO_CERRADO=180;
int SERVO_ABIERTO=0;
int SERVO_ABIERTO_TESTING=140;


void setupServo(){
   myservo.attach(PIN_SERVO);
   cerrarServo();
   ///abrirServo();
}

void abrirServo(){
  myservo.write(SERVO_ABIERTO); 
}

void cerrarServo(){
  myservo.write(SERVO_CERRADO); 
}


void abrirServoTesting(){
  myservo.write(SERVO_ABIERTO_TESTING); 
}




