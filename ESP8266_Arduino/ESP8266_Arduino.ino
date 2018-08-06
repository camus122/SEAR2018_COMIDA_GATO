#define DEBUG true

// Credenciales del WiFi
#define SSID "Fibertel WiFi084 2.4GHz"
#define PASS "0043173535" // AccessAir



// ESP8266
#include <SoftwareSerial.h>
int RX_AMARILLLO= 5;
int TX_AZUL= 6;
SoftwareSerial EspSerial(RX_AMARILLLO, TX_AZUL); // Rx, Tx
//#define HARDWARE_RESET_ESP 8


#include <stdlib.h>

boolean error;


void setup() 
{
    Serial.begin(115200);
    EspSerial.begin(115200); // Comunicacion com Modulo WiFi
//
//    pinMode(HARDWARE_RESET_ESP,OUTPUT);
//    digitalWrite(HARDWARE_RESET_ESP, HIGH);
  
     
    EspConfigInit();
//    EspHardwareReset(); //Reset do Modulo WiFi
}

void loop() {

    error = 0;
  
    delay(2000);

    int command = readThingSpeak();
//    if (command != 9) pump = command;

    delay (2000);
    
//    command = readThingSpeak(lampChId, lampChReadKey);
//    if (command != 9) lamp = command;
    
    
//    writeThingSpeak();
  
    if (error == 1)
    {       
        Serial.println(" <<<< ERROR >>>>");
        delay (2000);
    }
}


/********* Read Actuators command from ThingSpeak *************/
int readThingSpeak()
{
    startThingSpeakCmd();
    int command;
    // preparacao da string GET
    String getStr = "GET /home/getConfiguration";   
    getStr += "\r\n\r\n";
    Serial.print("readThingSpeak: ");
    Serial.println(getStr);
    String messageDown = sendThingSpeakGetCmd(getStr);
    Serial.println(messageDown);
//    if (messageDown[5] == 49) 
//        command = messageDown[7]-48;  
//    else command = 9;
    return command;
}







/********* Conexion con TCP con Thingspeak *******/
void writeThingSpeak(void)
{
    startThingSpeakCmd();

    String getStr = "GET /home/getConfiguration";

    getStr += "\r\n\r\n";

    sendThingSpeakGetCmd(getStr); 
}

void EspConfigInit() 
{
    Serial.println("Inicio Configurando ESP8266 ..."); 
//    AT+UART_DEF=9600,8,1,0,3
//    sendData("AT+UART_CUR=9600,8,1,0,0\r\n", 1000);
    sendData("AT+CWMODE=3\r\n", 2000);
    String cmd = "AT+CWJAP=\"";
    cmd += SSID;
    cmd += "\",\"";
    cmd += PASS;
    cmd += "\"\r\n";
    sendData(cmd, 15000);
    sendData("AT+CIPMUX=0\r\n",4000);
    
//    sendData("AT+CIFSR\r\n",5000);
    Serial.println("Fin Configuracion ..."); 
}


/********* Reset ESP *************/
//void EspHardwareReset(void)
//{
//    Serial.println("Reseteando......."); 
//    digitalWrite(HARDWARE_RESET_ESP, LOW); 
//    delay(500);
//    digitalWrite(HARDWARE_RESET_ESP, HIGH);
//    delay(10000);    // Tiempo necesario para comenzar a leer 
//    Serial.println("RESET"); 
//}


/********* Start communication with ThingSpeak*************/
void startThingSpeakCmd(void)
{
    EspSerial.flush();      // limpa el buffer antes de comezar a grabar

    String cmd = "AT+CIPSTART=\"TCP\",\"";
    cmd += "sear.condordevs.com";      // IP de api.thingspeak.com
    cmd += "\",80\r\n";

    if (sendData(cmd, 1000).indexOf("Error") > 0){
        Serial.println("AT+CIPSTART error");
        return;
    }else{
      Serial.println("AT+CIPSTART OK!");
    }
}


/********* send a GET cmd to ThingSpeak *************/
String sendThingSpeakGetCmd(String getStr)
{
    String cmd = "AT+CIPSEND=";
    cmd += String(getStr.length());
//    cmd += "\r\n";
    String data=sendData(cmd, 2000);
    Serial.print("data: ");
    Serial.println(data);
    if (data.indexOf(">") > 0) 
    {
        Serial.println("entre sendThingSpeakGetCmd");
//        return sendData(getStr, 1000);
          String cmd = "AT+CIPSEND=";
          cmd += getStr;
          cmd += "\r\n";
          sendData(cmd, 2000);
        EspSerial.print(getStr);
        Serial.println("========== Debug ESP8266 ===========");
        Serial.println("# Enviado ==> ");
        Serial.println(getStr);
        delay(500);//tempo para processar o GET, sem este delay apresenta busy no prÃ³ximo comando

        String messageBody = "";
        Serial.println("Senviando data antes de ESPSerial.Avaiablele()");
        while (EspSerial.available()) 
        {
          Serial.println("ENTRE AL ESPSerial.Avaiablele()");
          String line = EspSerial.readStringUntil('\n');
          Serial.print("LINE:");
          Serial.println(line);
          if (line.length() == 1) 
          { //actual content starts after empty line (that has length 1)
            messageBody = EspSerial.readStringUntil('\n');
          }
        }

        Serial.println("# Recibido ==> ");
        Serial.println(messageBody);
        Serial.println("====================================");
        return messageBody;
    }
    else 
    {
        sendData("AT+CIPCLOSE\r\n", 1000);
        error = 1;
        return "error";
    }
}






String sendData(String command, int timeout)
{
    String response = "";
    
    EspSerial.print(command); // Se envÃ­a el carÃ¡cter de lectura a la esp8266
    delay(500);

    long int time = millis();
    while( (time+timeout) > millis()){
        while(EspSerial.available()){
            char c = EspSerial.read();
            response += c;
        }
    }
    
    if (DEBUG)
    {
        Serial.println("========== Debug ESP8266 ===========");
        Serial.println("# Enviado ==> ");
        Serial.println(command);
        Serial.println("# Recibido ==> ");
        Serial.println(response);
        Serial.println("====================================");
    }    
        
    return response;
 }

