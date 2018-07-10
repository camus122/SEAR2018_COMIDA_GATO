#define DEBUG true 

void setup()
{
 delay(500);
  Serial.begin(115200);
  Serial3.begin(115200); 
  
 // sendData("AT+RST\r\n",2000,DEBUG); // reset del módulo
  //delay(10000);
  sendData("AT+CWMODE=3\r\n",1000,DEBUG); // configuración punto de acceso
  sendData("AT+CIPMUX=1\r\n",1000,DEBUG); // multiples conexiones
  sendData("AT+CIPSERVER=1,80\r\n",1000,DEBUG); // encender servidor en puerto 80
  delay(10000);
  sendData("AT+CWJAP=\"Fibertel WiFi084 2.4GHz\",\"0043173535\"\r\n",1000,DEBUG);//red wifi, usuario y clave
  delay(10000);
  sendData("AT+CIFSR\r\n",1000,DEBUG); // se obtienen direcciones IP 
  delay(10000);

}

void loop()
{
  
  if(Serial3.available()) // Comprueba si el ESP esta enviando mensaje
  {
    if(Serial3.find("+IPD,")){
     delay(1000);    
   
     int connectionId = Serial3.read()-48; // Restar 48 porque la función read () devuelve 
     String webpage = "<head><meta http-equiv=""refresh"" content=""5""></head>"; //refresh de 5 segundos
     webpage+="<h1>Tenemos nuestra conexion WiFi</h1></br><h3>:)</h3>";
     webpage+="<h2>Fue de utilidad para ti? ... Contactanos para mas informacion</h2>";
     sendData("AT+CIPSEND=" + String(connectionId) + "," + webpage.length() + "\r\n", 500, true);
     sendData(webpage, 1000, true); // 
     sendData("AT+CIPCLOSE=" + String(connectionId) + "\r\n", 1000, true); 
     }
  }
}

String sendData(String command, const int timeout, boolean debug)
{
    String response = "";
    Serial3.print(command); // Se envía el carácter de lectura a la esp8266
    long int time = millis();
    while( (time+timeout) > millis())
    {while(Serial3.available())
      { 
        char c = Serial3.read(); // Lee el siguiente carácter.
        response+=c;
      }  
    }
    
    if(debug)
    {
      Serial.print(response);
    }    
    return response;
}

