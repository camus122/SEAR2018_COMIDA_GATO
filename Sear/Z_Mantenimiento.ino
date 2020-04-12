/**
 * SE GUARDAN LAS VARIABLES PARA EL MANTENIMIENTOS
 */
String horaComida1_GUARDAR="__:__";
String horaComida2_GUARDAR="__:__";
String horaComida3_GUARDAR="__:__";
String horaComida4_GUARDAR="__:__";

String PORCIONES_GUARDAR="1";
bool configuracionGuardada=false;

void guardandoConfiguracion(){
    if(!configuracionGuardada){
      printLcd("GUARDANDO","CONFIGURACION");        
      horaComida1_GUARDAR=horaComida1;
      horaComida2_GUARDAR=horaComida2;
      horaComida3_GUARDAR=horaComida3;
      horaComida4_GUARDAR=horaComida4;
      PORCIONES_GUARDAR=PORCIONES;
      configuracionGuardada=true;
      delay(1000);      
    }

}

void restaurarConfiguracion(){
    printLcd("RESTAURANDO","CONFIGURACION");        
    horaComida1=horaComida1_GUARDAR;
    horaComida2=horaComida2_GUARDAR;
    horaComida3=horaComida3_GUARDAR;
    horaComida4=horaComida4_GUARDAR;
    PORCIONES=PORCIONES_GUARDAR;
    configuracionGuardada=false;
    delay(1000);
}


