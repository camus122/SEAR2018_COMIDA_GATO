const int INDEX_HORA_COMIDA=0;
const int INDEX_MINUTOS_COMIDA=3;


void setupChequearHoraComida(){
  //setTime(hr,min,sec,day,mnth,yr)
  setTime(9,59,00,16,57,2018);
}

String obtenerHorarioActual(){
  time_t horaActual = now();
  char buffer[5];
  sprintf(buffer, "%0.2d:%0.2d", hour(horaActual),minute(horaActual));
  return buffer;  
}

void verificarHorario(String horaComida1,String horaComida2,String horaComida3,String horaComida4){
  time_t t = now();
//  Serial.print(hour(t)); 
//  Serial.print(":");  
//  Serial.print(minute(t));  
//  Serial.print(":");  
//  Serial.println(second(t));  
  
  
}



