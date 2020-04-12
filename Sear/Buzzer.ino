const int PIN_BUZZER=49;
int noteDuration=200;

void errorSound(){
   tone(PIN_BUZZER,2200, noteDuration);
}

void marchaImperialSound(){
  marchaImperial(PIN_BUZZER);
}

