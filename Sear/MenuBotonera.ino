/* MenuPrimarino
 * 0: Bienvenido {horaActual}
 * 1: Programar comida
 *      1.1: Comida 1 {hora:min}
 *      1.2: Comida 2 {hora:min}
 *      1.2: Comida 3 {hora:min}
 *      1.2: Comida 4 {hora:min}
 * 2: porcion de comida
 *      2.1: Cantidad {X}
 * 3: Informe/Actualizacion
 *      3.1: {Mostrar info} + {Consultar json}
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

//Constantes de pins de botones
const byte PIN_FLECHA_ABAJO = 1; 
const byte PIN_FLECHA_ARRIBA = 2; 
const byte PIN_SELECCION = 3; 
const byte PIN_CANCELAR = 4; 
const byte PIN_ACEPTAR = 5; 

//Estados iniciales del menu
const byte cantidadMaximaMenuPrimario=3; 
const int INDICE_PRIMER_NIVEL=0;
const int INDICE_SEGUNDO_NIVEL=2;
boolean isSegundoNivel=false;
String itemSeleccionado="0.0"; //Variable  global de estado seleccionado
int contadorPrimerNivel=0;
int contadorSegundoNivel=0;

//Constantes de horarios
String HORA_RECHAZADA="##:##";
String HORA_VACIA="__:__";
//Buffers de horas de comidas
String horaComida1="__:__";
String horaComida2="__:__";
String horaComida3="__:__";
String horaComida4="__:__";


void setupMenuBotonera(){
// pinMode(PIN_FLECHA_ABAJO, INPUT); 
// pinMode(PIN_FLECHA_ARRIBA, INPUT); 
// pinMode(PIN_SELECCION, INPUT); 
// pinMode(PIN_CANCELAR, INPUT); 
// pinMode(PIN_ACEPTAR, INPUT);  


}

String identificarEstado(){
  if(isFlechaAbajo()){
    sumarContadorPrimerNivel();
    sumarContadorSegundoNivel();
  }
  if(isFlechaArriba()){
    restarContadorPrimerNivel();
    restarContadorSegundoNivel();
  }
  
  //Permite ciclar en caso de superar las opciones permitidas
  if(contadorPrimerNivel>3 || contadorPrimerNivel<0 || contadorSegundoNivel>4 || contadorSegundoNivel<0){
    Serial.print("contadorPrimerNivel:");
    Serial.println(contadorPrimerNivel);
    Serial.print("contadorSegundoNivel:");
    Serial.println(contadorSegundoNivel);
    resetearContadorPrimerNivel();
    resetearContadorSegundoNivel();
  }
  //estado!=0 es para evitar que seleccionar genere algun evento en el primer estado del menu
  if(isSeleccion() && itemSeleccionado!="0.0"){            
    isSegundoNivel=true;
  }
  if(isCancelar() && isSegundoNivel){
    isSegundoNivel=false;    
  }
    Serial.print("itemSeleccionado:");
    Serial.println(itemSeleccionado);
    delay(2000);
        Serial.print("INDICE_PRIMER_NIVEL:");
    Serial.println(contadorSegundoNivel);
         Serial.print("INDICE_SEGUNDO_NIVEL:");
    Serial.println(contadorPrimerNivel);
  //Setea el estado generara resultados del estilo "1.3"/ "0.0"
  char bufferPrimerNivel[1];
  sprintf(bufferPrimerNivel, "%1d", contadorPrimerNivel);
  Serial.print("contador: ");
  Serial.println(bufferPrimerNivel[0]);

  itemSeleccionado[INDICE_PRIMER_NIVEL]=bufferPrimerNivel[0];
  char bufferSegundoNivel[1];
  sprintf(bufferSegundoNivel, "%1d", contadorSegundoNivel);
  Serial.print("contador2: ");
  Serial.println(bufferSegundoNivel[0]);  
  itemSeleccionado[INDICE_SEGUNDO_NIVEL]=bufferSegundoNivel[0];
contadorPrimerNivel++;
  return itemSeleccionado;
}

void startMenuBotonera(){
  itemSeleccionado=identificarEstado();
  Serial.println(itemSeleccionado);
  //Items primer nivel
  if(itemSeleccionado=="0.0"){
    //printLcdLine1("123");
    // lcd.print("222, world!");
    printLcd("Bienvenido","hora actual");
    delay(4000);
  }
  //Items de menu
  programarComida(itemSeleccionado);
  definirPorcionComida(itemSeleccionado);
  informacionUpdate(itemSeleccionado);
}

void programarComida(String itemSeleccionado){
    if(itemSeleccionado=="1.0"){
      printLcd("Programar","comidas");
   }  
   if(itemSeleccionado=="1.1"){    
    //Evento de keyPad para seteo de hora de comida
    keypad.addEventListener(setearHoraComida);
    char key = keypad.getKey(); 
   }    
}


String hhmmBuffer="__:__";
int index=0;
void setearHoraComida(KeypadEvent key){
    switch (keypad.getState()){      
      case PRESSED:{
               if(itemSeleccionado=="1.1"){                  
                  if(index==2){index++;} //Esto es para que se saltee el ":"
                  horaComida1[index]=key;   
                  printLcdLine2(horaComida1);               
                  index++;
                  //if(index==6) printLcd(hhmmBuffer,"guardado");
               }
               Serial.println(horaComida1);
        }       
    }
    if(isAceptar()){
       index=0;
       keypad.addEventListener(0);       
    }
    if(isCancelar()){
       index=0;
       if(itemSeleccionado=="1.1"){     
        horaComida1=HORA_VACIA;
       }
       keypad.addEventListener(0);       
    }    
}


void definirPorcionComida(String itemSeleccionado){
  if(itemSeleccionado=="2.0"){
    printLcd("Porcion de","comida");
  }  
}

void informacionUpdate(String itemSeleccionado){
  if(itemSeleccionado=="3.0"){
    printLcd("Informacion","update");
  }    
}



/**
 * HELPERS
 */

 
void sumarContadorPrimerNivel(){
  if(!isSegundoNivel){
    contadorPrimerNivel++;
  }
}

void restarContadorPrimerNivel(){
  if(!isSegundoNivel){
    contadorPrimerNivel--;
  }
}

void resetearContadorPrimerNivel(){
  if(!isSegundoNivel){
    contadorPrimerNivel=0;
  }
}

void sumarContadorSegundoNivel(){
  if(isSegundoNivel){
    contadorSegundoNivel++;
  }
}

void restarContadorSegundoNivel(){
  if(isSegundoNivel){
    contadorSegundoNivel--;
  }
} 

void resetearContadorSegundoNivel(){
  if(isSegundoNivel){
    contadorSegundoNivel=0;
  }
}

//Helpers botones presionados
boolean isFlechaAbajo(){
  return presedButton(PIN_FLECHA_ABAJO);
}

boolean isFlechaArriba(){
  return presedButton(PIN_FLECHA_ARRIBA);
}

boolean isSeleccion(){
  return presedButton(PIN_SELECCION);
}

boolean isCancelar(){
  return presedButton(PIN_CANCELAR);
}

boolean isAceptar(){
  return presedButton(PIN_ACEPTAR);
}

boolean presedButton(byte buttonPin){
  // return digitalRead(buttonPin)==HIGH;
      return false;
}



