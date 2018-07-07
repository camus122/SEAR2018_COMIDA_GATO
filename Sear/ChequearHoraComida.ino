const int INDEX_HORA_COMIDA=0;
const int INDEX_MINUTOS_COMIDA=3;


void setupChequearHoraComida(){
  //setTime(hr,min,sec,day,mnth,yr)
  setTime(9,59,40,16,57,2018);
}

String obtenerHorarioActual(){
  time_t horaActual = now();
  char buffer[5];
  sprintf(buffer, "%0.2d:%0.2d", hour(horaActual),minute(horaActual));
  return buffer;  
}
String horaUltimaComida="__:__";
boolean liberoComida=false;

void verificarHorario(String hActual,String horaComida1,String horaComida2,String horaComida3,String horaComida4){
  //Realizara la accion de liberar comida si y solo si aun no libero la comida en algun horario.
  if(!liberoComida && (hActual==horaComida1 || hActual==horaComida2 || hActual==horaComida3 || hActual==horaComida4)){
    horaUltimaComida=hActual;
   liberarComida();   
  }  
  if(horaUltimaComida==hActual){
    liberoComida=true;
  }else{
    liberoComida=false;
  }
}



