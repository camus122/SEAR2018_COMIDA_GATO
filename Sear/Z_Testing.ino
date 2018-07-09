bool botonFlechaAbajoOK=false;
bool botonFlechaArribaOK=false;
bool botonSeleccionOK=false;
bool botonCancelarOK=false;
bool botonAceptarOK=false;
bool servoMotorOK=false;
int delayEntreBotones=1000;

void startModoTesting(){
    printLcd("MODO TESTING","PROBAR BOTONES");

    if(!servoMotorOK){
      printLcd("PROBANDO","SERVO");
      abrirServoTesting();
      delay(100);
      cerrarServo();
      servoMotorOK=true;
      delay(1000);
      
    }
    
     
    if(isFlechaAbajo()){
      printLcd("FLECHA ABAJO","OK!!");      
      botonFlechaAbajoOK=true;
      delay(delayEntreBotones);
    }
    if(isFlechaArriba()){
      printLcd("FLECHA ARRIBA","OK!!");
      botonFlechaArribaOK=true;
      delay(delayEntreBotones);
    }
    if(isSeleccion()){
      printLcd("FLECHA SELECCION","OK!!");
      botonSeleccionOK=true;
      delay(delayEntreBotones);
    }
    if(isCancelar()){
      printLcd("FLECHA CANCELAR","OK!!");
      botonCancelarOK=true;
      delay(delayEntreBotones);
    }
    if(isAceptar()){      
      printLcd("FLECHA ACEPTAR","OK!!");
      botonAceptarOK=true;
      delay(delayEntreBotones);
    }
    if(servoMotorOK && botonFlechaAbajoOK && botonFlechaArribaOK && botonSeleccionOK && botonCancelarOK && botonAceptarOK){
      printLcd("BOTONES","OK!! =D");   
      delay(2000);
      printLcd("PROBANDO","BUZZER");   
      marchaImperialSound();
      printLcd("TESTING","FINALIZADO!");
      delay(3000);
      MODO=MODO_NORMAL;
    }
 }

