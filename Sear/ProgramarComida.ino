/**
 * Se setea el keyboard de fechas
 */
const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'},
    {'*','0','#'}
};

byte rowPins[ROWS] = {31, 33, 35, 37}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {39, 41, 43}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
/**************************************************************/

//Constantes de horarios
String HORA_RECHAZADA="##:##";
String HORA_VACIA="__:__";
//Buffers de horas de comidas
String horaComida1="__:__";
//String horaComida1="09:59";
String horaComida2="__:__";
String horaComida3="__:__";
String horaComida4="__:__";
int index=0;
int HORA_COMPLETADA=5;
int INDICE_VACIA=0;


int MAXIMO_CANTIDAD_COMIDA=5;

void inicializarProgramarComida(){
  keypad.addEventListener(setearHorariosComida);
}

void programarComida(String itemSeleccionado,String horaMinutoActual,String porciones){
     verificarHorario(horaMinutoActual,horaComida1,horaComida2,horaComida3,horaComida4,porciones);

  
    if(itemSeleccionado=="1.0"){
      printLcd("Programar","comidas");
      resetarIndex();
   }  
   if(itemSeleccionado=="1.1"){    
    printLcd("Hora comida 1",horaComida1);      
    comportamietnoProgramacionComidaAceptarCancelar();
    char key = keypad.getKey(); 
   }
   if(itemSeleccionado=="1.2"){    
    printLcd("Hora comida 2",horaComida2);      
    comportamietnoProgramacionComidaAceptarCancelar();
    char key = keypad.getKey(); 
   }
   if(itemSeleccionado=="1.3"){    
    printLcd("Hora comida 3",horaComida3);      
    comportamietnoProgramacionComidaAceptarCancelar();
    char key = keypad.getKey(); 
   }   
   if(itemSeleccionado=="1.4"){    
    printLcd("Hora comida 4",horaComida4);      
    comportamietnoProgramacionComidaAceptarCancelar();
    char key = keypad.getKey(); 
   }      
}

void resetarIndex(){
  index=0;
}

void comportamietnoProgramacionComidaAceptarCancelar(){
  if(isAceptar()){
    if(index==HORA_COMPLETADA || index==INDICE_VACIA){
      int contador=sumarContadorSegundoNivel();
      resetarIndex();  
      if(contador==MAXIMO_CANTIDAD_COMIDA){
        resetarNiveles();
      }
    }else{
      errorSound();
    }
  }
  if(isCancelar()){
    Serial.println("cancelar");
     resetarIndex();
     if(itemSeleccionado=="1.1"){     
      horaComida1=HORA_VACIA;
     }
     if(itemSeleccionado=="1.2"){     
      horaComida2=HORA_VACIA;
     }
     if(itemSeleccionado=="1.3"){     
      horaComida3=HORA_VACIA;
     }     
     if(itemSeleccionado=="1.4"){     
      horaComida4=HORA_VACIA;
     }            
  }

  if(isSeleccion() || isFlechaAbajo() || isFlechaArriba()){
    errorSound(); 
  }
  
}

void setearHorariosComida(KeypadEvent key){  
    switch (keypad.getState()){      
      case PRESSED:{
         if(itemSeleccionado=="1.1" && validarHora(key,horaComida1,index)){
            setarHoraComida(&horaComida1,key);
          }
         if(itemSeleccionado=="1.2" && validarHora(key,horaComida2,index)){                
            setarHoraComida(&horaComida2,key);
          }                
         if(itemSeleccionado=="1.3" && validarHora(key,horaComida3,index)){                
            setarHoraComida(&horaComida3,key);
          }                  
         if(itemSeleccionado=="1.4" && validarHora(key,horaComida4,index)){                
            setarHoraComida(&horaComida4,key);
          }                            
         break;
        }        
    }
}


void setarHoraComida(String *hhmmComida,KeypadEvent key){
    if(index==2){index++;} //Esto es para que se saltee el ":"
    (*hhmmComida)[index]=key;   
    printLcdLine2(*hhmmComida);               
    index++;
}

/**
 * Liberar comida
 */
 void liberarComida(String porciones){  
  for(int i=0;i<porciones.toInt();i++){
    Serial.print("LIBERAR_COMIDA: ");
    Serial.println(i);
    //Serial.print("LIBERAR_COMIDA"):
    if(i!=0){delay(1000);} //Esto es para que en las iteraciones posteriores espere a que cierre el servo;
    abrirServo();
    delay(1000);
    cerrarServo();
  }
 //marchaImperialSound();  
 }

/**
 * Validacion de horario al momento de cargar por keypad
 */
boolean validarHora(KeypadEvent key, String hhmmComida,int index){
  boolean valido=false;
  if(key=='*' || key=='#'){
    errorSound();
    return false;
  }
  switch(index){
    case 0:{
       valido=key=='0' ||key=='1' || key=='2' ;
       break;
    }
    case 1:{
        /**
         * Que no se puede colocar una hora superior a 20/21/22/23
         */
        if(hhmmComida[0]=='2'){
          valido=key=='0' ||key=='1' || key=='2' || key=='3' ;   
        }else{
          valido=true;
        }       
       break;
    }    
    case 2:{
       valido=key=='0' ||key=='1' || key=='2' || key=='3' ||key=='4' || key=='5' ;
       break;
    }    
    default: {
      return true;
    }
  }
  if(!valido){
    errorSound();
  }
  return valido;
}

