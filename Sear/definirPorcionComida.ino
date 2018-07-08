/**
 * Se setea el keyboard de fechas
 */
//const byte ROWS_POCIONES = 4; //four rows
//const byte COLS_PORCIONES = 3; //three columns
//char keys[ROWS_POCIONES][COLS_PORCIONES] = {
//    {'1','2','3'},
//    {'4','5','6'},
//    {'7','8','9'},
//    {'*','0','#'}
//};
//
//byte rowPins[ROWS_POCIONES] = {31, 33, 35, 37}; //connect to the row pinouts of the keypad
//byte colPins[COLS_PORCIONES] = {39, 41, 43}; //connect to the column pinouts of the keypad

bool isPorcionValida=false;
int porcionSeteadaBuffer=-1;

Keypad keypadPorciones = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void inicializarDefinirPorcionComida(){
  keypadPorciones.addEventListener(setearPorcion);
}


void definirPorcionComida(String itemSeleccionado){
  if(itemSeleccionado=="2.0"){
    printLcd("Porcion de","comida");
  }  
  
   if(itemSeleccionado=="2.1"){    
    printLcd("Cant. porciones",PORCIONES);      
    comportamietnoDefinirPorcionComidaAceptarCancelar();
     char key = keypadPorciones.getKey(); 
//    if(isPorcionValida){
//      //int number = atoi( input );
//      (*porciones)=atoi(key);
//      Serial.print("PORCIONES: ");
//      Serial.println((*porciones));
//     }else{
//      Serial.println("no valida");
//     }
   }

}


void comportamietnoDefinirPorcionComidaAceptarCancelar(){
  if(isAceptar()){
      resetarNiveles();
      isPorcionValida=false;
  }
  if(isCancelar()){
    errorSound();
  }
}

void setearPorcion(KeypadEvent key){  
    switch (keypadPorciones.getState()){      
      case PRESSED:{
         if(itemSeleccionado=="2.1" && valdiarPorcion(key)){
          PORCIONES[0]=key;
            //porcionSeteadaBuffer=atoi(key);
          }        
         break;
        }        
    }
    isPorcionValida=false;
}

boolean valdiarPorcion(KeypadEvent key){
  boolean valido=false;
  if(key=='*' || key=='#' || key=='0'){
    errorSound();
    return false;
  }
  return true;
}

