#define DEBUG true

// Credenciales del WiFi
#define SSID "ssid"
#define PASS "passwd" // AccessAir

// Datos API ThingSpeak
#define THINGSPEAK "184.106.153.149"   // thingspeak.com184.106.153.149
String statusChWriteKey = "7HAsdsaHF4QB0BNTWZ";
String statusChId = "511182";

// MiniBomba
String pumpChReadKey = "DGSAW"EQB45HIGS";
String pumpChId = "53229454";

// Lampara
String lampChReadKey = "42Casdasd6JBR";
String lampChId = "531236";


// LCD
#include <LiquidCrystal.h>
#define LCD_RS 40
#define LCD_E 41
#define LCD_D4 42
#define LCD_D5 43
#define LCD_D6 44
#define LCD_D7 45
LiquidCrystal lcd (LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);  

// ESP8266
#include <SoftwareSerial.h>
SoftwareSerial EspSerial(11, 12); // Rx, Tx
#define HARDWARE_RESET_ESP 8

// DS18B20
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 36 // DS18B20 on pin D5 
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature ds18b20(&oneWire);

//DHT
#include "DHT.h"
#include <stdlib.h>
int pinDHT = 37;
int tipoDHT =  DHT22;
DHT dht(pinDHT, tipoDHT); 

// Soil humidity
#define pinSoilHum A10

// LDR (Light)
#define pinLDR A11

// Relay Actuadores
int pinRelayPump = 2;
int pinRelayLamp = 3;


// Variables para enviar en el Status
boolean pump = 0; 
boolean lamp = 0;
int airTemp = 0;
int airHum = 0;
int soilTemp = 0;
int soilHum = 0;
int light = 0;

boolean error;


void setup() 
{
    Serial.begin(9600);
    EspSerial.begin(9600); // Comunicacion com Modulo WiFi

    pinMode(HARDWARE_RESET_ESP,OUTPUT);
    digitalWrite(HARDWARE_RESET_ESP, HIGH);
  
    lcd.begin(16,2);
    ds18b20.begin();
    dht.begin();

    pinMode(pinRelayPump, OUTPUT);
    pinMode(pinRelayLamp, OUTPUT);
    digitalWrite(pinRelayPump, HIGH);
    digitalWrite(pinRelayLamp, HIGH);
    
    EspConfigInit();
    EspHardwareReset(); //Reset do Modulo WiFi
}

void loop() {

    error = 0;
  
    delay(2000);

    int command = readThingSpeak(pumpChId, pumpChReadKey);
    if (command != 9) pump = command;

    delay (2000);
    
    command = readThingSpeak(lampChId, lampChReadKey);
    if (command != 9) lamp = command;
    
    takeActions();

    readSensors();
    
    writeThingSpeak();
  
    if (error == 1)
    {       
        Serial.println(" <<<< ERROR >>>>");
        delay (2000);
    } else showLcdReadSensors(2000);
}


/********* Read Actuators command from ThingSpeak *************/
int readThingSpeak(String channelID, String key)
{
    startThingSpeakCmd();
    int command;
    // preparacao da string GET
    String getStr = "GET /channels/";
    getStr += channelID;
    getStr += "/fields/1/last/?api_key=";
    getStr += key;
    getStr += "\r\n\r\n";

    String messageDown = sendThingSpeakGetCmd(getStr);
    if (messageDown[5] == 49) 
        command = messageDown[7]-48;  
    else command = 9;
    return command;
}


void takeActions(void)
{
    if (pump == 1) digitalWrite(pinRelayPump, LOW);
    else digitalWrite(pinRelayPump, HIGH);

    if (lamp == 1) digitalWrite(pinRelayLamp, LOW);
    else digitalWrite(pinRelayLamp, HIGH);
}


/********* Read Sensors value *************/
void readSensors(void)
{
    airTemp = dht.readTemperature();
    airHum = dht.readHumidity();

    ds18b20.requestTemperatures(); 
    soilTemp = random(10,30);//ds18b20.getTempCByIndex(0); // Sensor 0 will capture Soil Temp in Celcius
             
    light = map(analogRead(pinLDR), 1023, 0, 100, 0); //LDRDark:0  ==> light 100%  
    soilHum = random(10, 90);// map(analogRead(pinSoilHum), 370, 1000, 100, 0);
}


/********** Show LCD monitor ***************/
void showLcdReadSensors(int timeout)
{    
    showDataInLcd("Estado del Aire", "Temp.", airTemp, "C", timeout);
    showDataInLcd("Estado del Aire", "Hume.", airHum, "%", timeout);
    showDataInLcd("Estado del Suelo", "Temp.", soilTemp, "C", timeout);
    showDataInLcd("Estado del Suelo", "Humedad", soilHum, "%", timeout);
    showDataInLcd("Estado de la Luz", "Intensidad", light, "%", timeout);
}


/********* Conexion con TCP con Thingspeak *******/
void writeThingSpeak(void)
{
    startThingSpeakCmd();

    String getStr = "GET /update?api_key=";
    getStr += statusChWriteKey;
    getStr += "&field1=";
    getStr += String(pump);
    getStr += "&field2=";
    getStr += String(lamp);
    getStr += "&field3=";
    getStr += String(airTemp);
    getStr += "&field4=";
    getStr += String(airHum);
    getStr += "&field5=";
    getStr += String(soilTemp);
    getStr += "&field6=";
    getStr += String(soilHum);
    getStr += "&field7=";
    getStr += String(light);
    getStr += "\r\n\r\n";

    sendThingSpeakGetCmd(getStr); 
}

void EspConfigInit() 
{
    Serial.println("Inicio Configurando ESP8266 ..."); 
    sendData("AT+UART_DEF=9600,8,1,0,0\r\n", 1000);
    sendData("AT+CWMODE=1\r\n", 1000);
    String cmd = "AT+CWJAP=\"";
    cmd += SSID;
    cmd += "\",\"";
    cmd += PASS;
    cmd += "\"\r\n";
    sendData(cmd, 5000);
    sendData("AT+CIFSR\r\n",5000);
    Serial.println("Fin Configuracion ..."); 
}


/********* Reset ESP *************/
void EspHardwareReset(void)
{
    Serial.println("Reseteando......."); 
    digitalWrite(HARDWARE_RESET_ESP, LOW); 
    delay(500);
    digitalWrite(HARDWARE_RESET_ESP, HIGH);
    delay(10000);    // Tiempo necesario para comenzar a leer 
    Serial.println("RESET"); 
}


/********* Start communication with ThingSpeak*************/
void startThingSpeakCmd(void)
{
    EspSerial.flush();      // limpa el buffer antes de comezar a grabar

    String cmd = "AT+CIPSTART=\"TCP\",\"";
    cmd += THINGSPEAK;      // IP de api.thingspeak.com
    cmd += "\",80\r\n";

    if (sendData(cmd, 1000).indexOf("Error") > 0){
        Serial.println("AT+CIPSTART error");
        return;
    }
}


/********* send a GET cmd to ThingSpeak *************/
String sendThingSpeakGetCmd(String getStr)
{
    String cmd = "AT+CIPSEND=";
    cmd += String(getStr.length());
    cmd += "\r\n";
    if (sendData(cmd, 2000).indexOf(">") > 0) 
    {
        //return sendData(getStr, 1000);
        
        EspSerial.print(getStr);
        Serial.println("========== Debug ESP8266 ===========");
        Serial.println("# Enviado ==> ");
        Serial.println(getStr);
        delay(500);//tempo para processar o GET, sem este delay apresenta busy no próximo comando

        String messageBody = "";
        while (EspSerial.available()) 
        {
          String line = EspSerial.readStringUntil('\n');
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



/**************** Show Lcd *****************/
void showDataInLcd(String title, String key, int value, String unit, int timeout)
{
    String text = "";
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(title);
    lcd.setCursor(0, 1);
    text = key;
    text += ": ";
    text += value;
    text += " ";
    text += unit;
    lcd.print(text);
    delay(timeout);
    lcd.clear();
}


String sendData(String command, int timeout)
{
    String response = "";
    
    EspSerial.print(command); // Se envía el carácter de lectura a la esp8266
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