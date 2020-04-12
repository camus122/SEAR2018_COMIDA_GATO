#include <Time.h>
#include <TimeLib.h>

void setup() {
   Serial.begin(9600);
  setupChequearHoraComida();

}
String horaComida1="10:00";

String DATO="5";
char charBuf[1];
void loop() {
//  String hActual=obtenerHorarioActual();
//   Serial.println(hActual);
//  if(hActual==horaComida1){
//    Serial.println("YES!!");
//    delay(5000);
//  }
  

  Serial.println(DATO.toInt());
  delay(10000);
}

void setupChequearHoraComida(){
  //setTime(hr,min,sec,day,mnth,yr)
  setTime(9,59,55,16,57,2018);
}

String obtenerHorarioActual(){
  time_t horaActual = now();
  char buffer[5];
  sprintf(buffer, "%0.2d:%0.2d", hour(horaActual),minute(horaActual));
  return buffer;  
}

