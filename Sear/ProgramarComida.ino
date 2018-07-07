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
String horaComida2="__:__";
String horaComida3="__:__";
String horaComida4="__:__";
int index=0;
int HORA_COMPLETADA=5;

void inicializarProgramarComida(){
  keypad.addEventListener(setearHorariosComida);
}

void programarComida(String itemSeleccionado){
     verificarHorario(horaComida1,horaComida2,horaComida3,horaComida4);

  
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
}

void resetarIndex(){
  index=0;
}

void comportamietnoProgramacionComidaAceptarCancelar(){
  if(isAceptar()){
    if(index==HORA_COMPLETADA){
      sumarContadorSegundoNivel();
      resetarIndex();  
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
  }
}

void setearHorariosComida(KeypadEvent key){  
  

    switch (keypad.getState()){      
      case PRESSED:{
              if(validarHora(key,index)){
               if(itemSeleccionado=="1.1"){
                  setarHoraComida(&horaComida1,key);
                }
               if(itemSeleccionado=="1.2"){                
                  setarHoraComida(&horaComida2,key);
                }                
               }
               Serial.println("entorSiempre");
               Serial.println(horaComida1);
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

boolean validarHora(KeypadEvent key, int index){
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

