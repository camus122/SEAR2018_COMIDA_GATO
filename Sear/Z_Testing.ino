bool botonFlechaAbajoOK=false;
bool botonFlechaArribaOK=false;
bool botonSeleccionOK=false;
bool botonCancelarOK=false;
bool botonAceptarOK=false;
bool servoMotorOK=false;
bool LCDOK=false;

//bool botonFlechaAbajoOK=true;
//bool botonFlechaArribaOK=true;
//bool botonSeleccionOK=true;
//bool botonCancelarOK=true;
//bool botonAceptarOK=true;
//bool servoMotorOK=true;
//bool LCDOK=true;


bool keyPadOK=false;
int delayEntreBotones=500;

String LCD_TEST_LINEA="ABCDEFGHIJKLMNOP";

void startModoTesting(){
        
   if(!LCDOK){
      printLcd("MODO TESTING","PROBAR LCD");
      delay(1000);
      String data="                ";
      for (int i = 0; i < 16; i = i+1) {
        data[i]=LCD_TEST_LINEA[i];       
        printLcd(data,data);
        delay(200);
      }
            
      LCDOK=true;
      delay(1000);
     }

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

    if(isAceptar()){      
      printLcd("FLECHA ACEPTAR","OK!!");
      botonAceptarOK=true;
      delay(delayEntreBotones);
    }

    if(botonFlechaAbajoOK && botonFlechaArribaOK && botonSeleccionOK && botonCancelarOK && botonAceptarOK && !keyPadOK){
        printLcd("PROBANDO","KEYPAD");
        delay(1000);
        boolean todasTeclasPresionadas=false;
        String keyPadPresionado="1234567890*#";
        String dataEmpty="            ";
        while(!todasTeclasPresionadas){
            printLcd("PRESIONAR TECLAS",dataEmpty);
           char key = keypad.getKey(); 
           switch(key){
              case '1':dataEmpty[0]=key; break;
              case '2':dataEmpty[1]=key; break;
              case '3':dataEmpty[2]=key; break;
              case '4':dataEmpty[3]=key; break;
              case '5':dataEmpty[4]=key; break;
              case '6':dataEmpty[5]=key; break;
              case '7':dataEmpty[6]=key; break;
              case '8':dataEmpty[7]=key; break;
              case '9':dataEmpty[8]=key; break;
              case '0':dataEmpty[9]=key; break;
              case '*':dataEmpty[10]=key; break;
              case '#':dataEmpty[11]=key; break;               
           }
           delay(200);
           if(keyPadPresionado == dataEmpty){
            todasTeclasPresionadas=true;
            keyPadOK=true;
             printLcd("MODO TESTING","KEYPAD OK!!"); 
             delay(1000);
           }
        }

    }

    

    
    if(keyPadOK && LCDOK && servoMotorOK && botonFlechaAbajoOK && botonFlechaArribaOK && botonSeleccionOK && botonCancelarOK && botonAceptarOK){
      printLcd("BOTONES","OK!! =D");   
      delay(2000);
      printLcd("PROBANDO","BUZZER");   
      marchaImperialSound();
      printLcd("TESTING","FINALIZADO!");
      delay(3000);
      MODO=MODO_NORMAL;
    }
 }


