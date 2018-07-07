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


//Constantes de pins de botones
const byte PIN_FLECHA_ABAJO = 26; 
const byte PIN_FLECHA_ARRIBA = 24; 
const byte PIN_SELECCION = 28; 
const byte PIN_CANCELAR = 30; 
const byte PIN_ACEPTAR = 32; 

//PULL_DOWN
const byte PIN_LINEA_DOWN = 22;


//Estados iniciales del menu
const byte cantidadMaximaMenuPrimario=3; 
const int INDICE_PRIMER_NIVEL=0;
const int INDICE_SEGUNDO_NIVEL=2;
boolean isSegundoNivel=false;
String itemSeleccionado="0.0"; //Variable  global de estado seleccionado
int contadorPrimerNivel=0;
int contadorSegundoNivel=0;



void setupMenuBotonera(){
 pinMode(PIN_FLECHA_ABAJO, INPUT_PULLUP); 
 pinMode(PIN_FLECHA_ARRIBA, INPUT_PULLUP); 
 pinMode(PIN_SELECCION, INPUT_PULLUP); 
 pinMode(PIN_CANCELAR, INPUT_PULLUP); 
 pinMode(PIN_ACEPTAR, INPUT_PULLUP);  
//LINEA PULL DOWN
  pinMode(PIN_LINEA_DOWN, OUTPUT); 
  digitalWrite(PIN_LINEA_DOWN,LOW);
  inicializarProgramarComida();
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
    sumarContadorSegundoNivel();

  }
  if(isCancelar() && isSegundoNivel){
    isSegundoNivel=false;    
    restarContadorSegundoNivel();
  }

  itemSeleccionado=obtenerNivelActual();
  return itemSeleccionado;
}

String obtenerNivelActual(){
  char bufferPrimerNivel[1];
  sprintf(bufferPrimerNivel, "%1d", contadorPrimerNivel);
  itemSeleccionado[INDICE_PRIMER_NIVEL]=bufferPrimerNivel[0];
  char bufferSegundoNivel[1];
  sprintf(bufferSegundoNivel, "%1d", contadorSegundoNivel);
  itemSeleccionado[INDICE_SEGUNDO_NIVEL]=bufferSegundoNivel[0];
  return itemSeleccionado;
}

void startMenuBotonera(){
  itemSeleccionado=identificarEstado();
  Serial.println(itemSeleccionado);
  //Items primer nivel
  if(itemSeleccionado=="0.0"){    
    printLcd("Bienvenido","hora actual");
    
  }
  //Items de menu
  programarComida(itemSeleccionado);
  definirPorcionComida(itemSeleccionado);
  informacionUpdate(itemSeleccionado);
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
  return presedButton(PIN_FLECHA_ABAJO,"BOTON_ABAJO");
}

boolean isFlechaArriba(){
  return presedButton(PIN_FLECHA_ARRIBA,"BOTON_ARRIBA");
}

boolean isSeleccion(){
  return presedButton(PIN_SELECCION,"BOTON_SELECCION");
  //return false;
}

boolean isCancelar(){
  return presedButton(PIN_CANCELAR,"BOTON_CANCELAR");
  //return false;
}

boolean isAceptar(){
  return presedButton(PIN_ACEPTAR,"BOTON_ACEPTAR");
  //return false;
}

boolean presedButton(byte buttonPin,String desc){
    if(digitalRead(buttonPin)==LOW){
      Serial.println(desc);      
      delay(500);
      return true;
  }  
  // return digitalRead(buttonPin)==HIGH;
      return false;
}



