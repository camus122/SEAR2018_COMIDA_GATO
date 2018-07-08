char PIN_SERVO=A0;
Servo myservo;
int degrees=0;

int SERVO_CERRADO=180;
int SERVO_ABIERTO=0;


void setupServo(){
   myservo.attach(PIN_SERVO);
}

void abrirServo(){
  myservo.write(SERVO_ABIERTO); 
}

void cerrarServo(){
  myservo.write(SERVO_CERRADO); 
}



