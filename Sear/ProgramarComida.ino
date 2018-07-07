
String hhmmBuffer="__:__";
int index=0;

void programarComida(String itemSeleccionado){
    if(itemSeleccionado=="1.0"){
      printLcd("Programar","comidas");
   }  
   if(itemSeleccionado=="1.1"){    
    printLcd("Hora comida 1",horaComida1);      
    comportamietnoProgramacionComidaAceptarCancelar();
    char key = keypad.getKey(); 
   }
}


void comportamietnoProgramacionComidaAceptarCancelar(){
  if(isAceptar()){
      //limpiar pantalla guardar y sumar indice segundo.
         index=0;
      }
  if(isCancelar()){
    Serial.println("cancelar");
     index=0;
     if(itemSeleccionado=="1.1"){     
      horaComida1=HORA_VACIA;
     }
  }
}

void keypadEvent(KeypadEvent key){  
  

    switch (keypad.getState()){      
      case PRESSED:{
               if(itemSeleccionado=="1.1"){                  
                if(validarHora(key,horaComida1,index)){
                  if(index==2){index++;} //Esto es para que se saltee el ":"
                  horaComida1[index]=key;   
                  printLcdLine2(horaComida1);               
                  index++;
                }
               }
               Serial.println("entorSiempre");
               Serial.println(horaComida1);
               break;
        }        
    }
}


boolean validarHora(KeypadEvent key, String hora,int index){
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

