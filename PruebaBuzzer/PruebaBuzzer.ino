#include "pitches.h"

const int PIN_BUZZER=49;
int noteDuration=200;
// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

void setup() {
  Serial.begin(9600);
// for (int thisNote = 0; thisNote < 8; thisNote++) {
//
//    // to calculate the note duration, take one second divided by the note type.
//    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
//    int noteDuration = 1000 / noteDurations[thisNote];
//    tone(PIN_BUZZER, melody[thisNote], noteDuration);
//
//    // to distinguish the notes, set a minimum time between them.
//    // the note's duration + 30% seems to work well:
//    int pauseBetweenNotes = noteDuration * 1.30;
//    delay(pauseBetweenNotes);
//    // stop the tone playing:
//    noTone(PIN_BUZZER);
//  }
 
}

void loop() {
  tone(PIN_BUZZER,2200, noteDuration);Serial.println("NOTE_C1");  
  delay(4000);
  
//delay(1000);tone(PIN_BUZZER,NOTE_C1, noteDuration);Serial.println("NOTE_C1");
//delay(1000);tone(PIN_BUZZER,NOTE_B0, noteDuration);Serial.println("NOTE_B0");
//delay(1000);tone(PIN_BUZZER,NOTE_CS1, noteDuration);Serial.println("NOTE_CS1");
//delay(1000);tone(PIN_BUZZER,NOTE_D1, noteDuration);Serial.println("NOTE_D1");
//delay(1000);tone(PIN_BUZZER,NOTE_DS1, noteDuration);Serial.println("NOTE_DS1");
//delay(1000);tone(PIN_BUZZER,NOTE_E1, noteDuration);Serial.println("NOTE_E1");
//delay(1000);tone(PIN_BUZZER,NOTE_F1, noteDuration);Serial.println("NOTE_F1");
//delay(1000);tone(PIN_BUZZER,NOTE_FS1, noteDuration);Serial.println("NOTE_FS1");
//delay(1000);tone(PIN_BUZZER,NOTE_G1, noteDuration);Serial.println("NOTE_G1");
//delay(1000);tone(PIN_BUZZER,NOTE_GS1, noteDuration);Serial.println("NOTE_GS1");
//delay(1000);tone(PIN_BUZZER,NOTE_A1, noteDuration);Serial.println("NOTE_A1");
//delay(1000);tone(PIN_BUZZER,NOTE_AS1, noteDuration);Serial.println("NOTE_AS1");
//delay(1000);tone(PIN_BUZZER,NOTE_B1, noteDuration);Serial.println("NOTE_B1");
//delay(1000);tone(PIN_BUZZER,NOTE_C2, noteDuration);Serial.println("NOTE_C2");
//delay(1000);tone(PIN_BUZZER,NOTE_CS2, noteDuration);Serial.println("NOTE_CS2");
//delay(1000);tone(PIN_BUZZER,NOTE_D2, noteDuration);Serial.println("NOTE_D2");
//delay(1000);tone(PIN_BUZZER,NOTE_DS2, noteDuration);Serial.println("NOTE_DS2");
//delay(1000);tone(PIN_BUZZER,NOTE_E2, noteDuration);Serial.println("NOTE_E2");
//delay(1000);tone(PIN_BUZZER,NOTE_F2, noteDuration);Serial.println("NOTE_F2");
//delay(1000);tone(PIN_BUZZER,NOTE_FS2, noteDuration);Serial.println("NOTE_FS2");
//delay(1000);tone(PIN_BUZZER,NOTE_G2, noteDuration);Serial.println("NOTE_G2");
//delay(1000);tone(PIN_BUZZER,NOTE_GS2, noteDuration);Serial.println("NOTE_GS2");
//delay(1000);tone(PIN_BUZZER,NOTE_A2, noteDuration);Serial.println("NOTE_A2");
//delay(1000);tone(PIN_BUZZER,NOTE_AS2, noteDuration);Serial.println("NOTE_AS2");
//delay(1000);tone(PIN_BUZZER,NOTE_B2, noteDuration);Serial.println("NOTE_B2");
//delay(1000);tone(PIN_BUZZER,NOTE_C3, noteDuration);Serial.println("NOTE_C3");
//delay(1000);tone(PIN_BUZZER,NOTE_CS3, noteDuration);Serial.println("NOTE_CS3");
//delay(1000);tone(PIN_BUZZER,NOTE_D3, noteDuration);Serial.println("NOTE_D3");
//delay(1000);tone(PIN_BUZZER,NOTE_DS3, noteDuration);Serial.println("NOTE_DS3");
//delay(1000);tone(PIN_BUZZER,NOTE_E3, noteDuration);Serial.println("NOTE_E3");
//delay(1000);tone(PIN_BUZZER,NOTE_F3, noteDuration);Serial.println("NOTE_F3");
//delay(1000);tone(PIN_BUZZER,NOTE_FS3, noteDuration);Serial.println("NOTE_FS3");
//delay(1000);tone(PIN_BUZZER,NOTE_G3, noteDuration);Serial.println("NOTE_G3");
//delay(1000);tone(PIN_BUZZER,NOTE_GS3, noteDuration);Serial.println("NOTE_GS3");
//delay(1000);tone(PIN_BUZZER,NOTE_A3, noteDuration);Serial.println("NOTE_A3");
//delay(1000);tone(PIN_BUZZER,NOTE_AS3, noteDuration);Serial.println("NOTE_AS3");
//delay(1000);tone(PIN_BUZZER,NOTE_B3, noteDuration);Serial.println("NOTE_B3");
//delay(1000);tone(PIN_BUZZER,NOTE_C4, noteDuration);Serial.println("NOTE_C4");
//delay(1000);tone(PIN_BUZZER,NOTE_CS4, noteDuration);Serial.println("NOTE_CS4");
//delay(1000);tone(PIN_BUZZER,NOTE_D4, noteDuration);Serial.println("NOTE_D4");
//delay(1000);tone(PIN_BUZZER,NOTE_DS4, noteDuration);Serial.println("NOTE_DS4");
//delay(1000);tone(PIN_BUZZER,NOTE_E4, noteDuration);Serial.println("NOTE_E4");
//delay(1000);tone(PIN_BUZZER,NOTE_F4, noteDuration);Serial.println("NOTE_F4");
//delay(1000);tone(PIN_BUZZER,NOTE_FS4, noteDuration);Serial.println("NOTE_FS4");
//delay(1000);tone(PIN_BUZZER,NOTE_G4, noteDuration);Serial.println("NOTE_G4");
//delay(1000);tone(PIN_BUZZER,NOTE_GS4, noteDuration);Serial.println("NOTE_GS4");
//delay(1000);tone(PIN_BUZZER,NOTE_A4, noteDuration);Serial.println("NOTE_A4");
//delay(1000);tone(PIN_BUZZER,NOTE_AS4, noteDuration);Serial.println("NOTE_AS4");
//delay(1000);tone(PIN_BUZZER,NOTE_B4, noteDuration);Serial.println("NOTE_B4");
//delay(1000);tone(PIN_BUZZER,NOTE_C5, noteDuration);Serial.println("NOTE_C5");
//delay(1000);tone(PIN_BUZZER,NOTE_CS5, noteDuration);Serial.println("NOTE_CS5");
//delay(1000);tone(PIN_BUZZER,NOTE_D5, noteDuration);Serial.println("NOTE_D5");
//delay(1000);tone(PIN_BUZZER,NOTE_DS5, noteDuration);Serial.println("NOTE_DS5");
//delay(1000);tone(PIN_BUZZER,NOTE_E5, noteDuration);Serial.println("NOTE_E5");
//delay(1000);tone(PIN_BUZZER,NOTE_F5, noteDuration);Serial.println("NOTE_F5");
//delay(1000);tone(PIN_BUZZER,NOTE_FS5, noteDuration);Serial.println("NOTE_FS5");
//delay(1000);tone(PIN_BUZZER,NOTE_G5, noteDuration);Serial.println("NOTE_G5");
//delay(1000);tone(PIN_BUZZER,NOTE_GS5, noteDuration);Serial.println("NOTE_GS5");
//delay(1000);tone(PIN_BUZZER,NOTE_A5, noteDuration);Serial.println("NOTE_A5");
//delay(1000);tone(PIN_BUZZER,NOTE_AS5, noteDuration);Serial.println("NOTE_AS5");
//delay(1000);tone(PIN_BUZZER,NOTE_B5, noteDuration);Serial.println("NOTE_B5");
//delay(1000);tone(PIN_BUZZER,NOTE_C6, noteDuration);Serial.println("NOTE_C6");
//delay(1000);tone(PIN_BUZZER,NOTE_CS6, noteDuration);Serial.println("NOTE_CS6");
//delay(1000);tone(PIN_BUZZER,NOTE_D6, noteDuration);Serial.println("NOTE_D6");
//delay(1000);tone(PIN_BUZZER,NOTE_DS6, noteDuration);Serial.println("NOTE_DS6");
//delay(1000);tone(PIN_BUZZER,NOTE_E6, noteDuration);Serial.println("NOTE_E6");
//delay(1000);tone(PIN_BUZZER,NOTE_F6, noteDuration);Serial.println("NOTE_F6");
//delay(1000);tone(PIN_BUZZER,NOTE_FS6, noteDuration);Serial.println("NOTE_FS6");
//delay(1000);tone(PIN_BUZZER,NOTE_G6, noteDuration);Serial.println("NOTE_G6");
//delay(1000);tone(PIN_BUZZER,NOTE_GS6, noteDuration);Serial.println("NOTE_GS6");
//delay(1000);tone(PIN_BUZZER,NOTE_A6, noteDuration);Serial.println("NOTE_A6");
//delay(1000);tone(PIN_BUZZER,NOTE_AS6, noteDuration);Serial.println("NOTE_AS6");
//delay(1000);tone(PIN_BUZZER,NOTE_B6, noteDuration);Serial.println("NOTE_B6");
//delay(1000);tone(PIN_BUZZER,NOTE_C7, noteDuration);Serial.println("NOTE_C7");
//delay(1000);tone(PIN_BUZZER,NOTE_CS7, noteDuration);Serial.println("NOTE_CS7");
//delay(1000);tone(PIN_BUZZER,NOTE_D7, noteDuration);Serial.println("NOTE_D7");
//delay(1000);tone(PIN_BUZZER,NOTE_DS7, noteDuration);Serial.println("NOTE_DS7");
//delay(1000);tone(PIN_BUZZER,NOTE_E7, noteDuration);Serial.println("NOTE_E7");
//delay(1000);tone(PIN_BUZZER,NOTE_F7, noteDuration);Serial.println("NOTE_F7");
//delay(1000);tone(PIN_BUZZER,NOTE_FS7, noteDuration);Serial.println("NOTE_FS7");
//delay(1000);tone(PIN_BUZZER,NOTE_G7, noteDuration);Serial.println("NOTE_G7");
//delay(1000);tone(PIN_BUZZER,NOTE_GS7, noteDuration);Serial.println("NOTE_GS7");
//delay(1000);tone(PIN_BUZZER,NOTE_A7, noteDuration);Serial.println("NOTE_A7");
//delay(1000);tone(PIN_BUZZER,NOTE_AS7, noteDuration);Serial.println("NOTE_AS7");
//delay(1000);tone(PIN_BUZZER,NOTE_B7, noteDuration);Serial.println("NOTE_B7");
//delay(1000);tone(PIN_BUZZER,NOTE_C8, noteDuration);Serial.println("NOTE_C8");
//delay(1000);tone(PIN_BUZZER,NOTE_CS8, noteDuration);Serial.println("NOTE_CS8");
//delay(1000);tone(PIN_BUZZER,NOTE_D8, noteDuration);Serial.println("NOTE_D8");
//delay(1000);tone(PIN_BUZZER,NOTE_DS8, noteDuration);Serial.println("NOTE_DS8");
}
