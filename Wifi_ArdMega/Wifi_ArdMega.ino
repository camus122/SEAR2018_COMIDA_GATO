#define DEBUG true 
#define TIMEOUT     5000                                          // mS
#define CONTINUE    false                                         // Define for readability
#define HALT        true    
void setup()
{
 delay(500);
  Serial.begin(115200);
  Serial.begin(115200); 
  
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

void echoSkip()
{
  echoFind("\n");        // Search for nl at end of command echo
  echoFind("\n");        // Search for 2nd nl at end of response.
  echoFind("\n");        // Search for 3rd nl at end of blank line.
}

boolean echoCommand(String cmd, String ack, boolean halt_on_fail)
{
  Serial.println(cmd);
  if (ack == "")                 // If no ack response specified, skip all available module output.
    echoSkip();                  
  else                           // Otherwise wait for ack.
    if (!echoFind(ack))          // timed out waiting for ack string 
      if (halt_on_fail)          // If halt on failure
        errorHalt();             // Critical failure halt.
      else
        return false;            // Let the caller handle it.
  return true;                   // ack blank or ack found
}

void errorHalt()
{
  while(true){};
}

boolean echoFind(String keyword)
{
  byte current_char   = 0;
  byte keyword_length = keyword.length();
  
  long deadline = millis() + TIMEOUT;              // Calculate timeout deadline
  while(millis() < deadline)                       // Try until deadline
  {
    if (Serial.available())                        // If characters are available
    {
      char ch = Serial.read();
      if (ch == keyword[current_char])
      {
        if (++current_char == keyword_length)
          return true;
      }
    }
  }
  return false;                                    // Timed out
}

void loop()
{
  
  if(Serial.available()) // Comprueba si el ESP esta enviando mensaje
  {
    if(Serial.find("+IPD,")){
     delay(1000);    
   
     int connectionId = Serial.read()-48; // Restar 48 porque la función read () devuelve 
     String webpage = "<head><meta http-equiv=""refresh"" content=""5""></head>"; //refresh de 5 segundos
     webpage+="<h1>Tenemos nuestra conexion WiFi</h1></br><h3>:)</h3>";
     webpage+="<h2>Fue de utilidad para ti? ... Contactanos para mas informacion</h2>";
     sendData("AT+CIPSEND=" + String(connectionId) + "," + webpage.length() + "\r\n", 500, true);
     sendData(webpage, 1000, true); // 
     sendData("AT+CIPCLOSE=" + String(connectionId) + "\r\n", 1000, true); 
     }
  String cmd;                            // Command string to the ESP8266

     // Build HTTP request.
      cmd = "GET ";
      cmd += "https://alimentador-e82e9.firebaseio.com/hora1.json";
      cmd += " HTTP/1.1\r\n\r\n";
        if (!echoCommand("AT+CIPSEND=0,"+String(cmd.length()), ">", CONTINUE))
       {
        echoCommand("AT+CIPCLOSE", "", CONTINUE);
        return;
     }
      // Ready the module to receive raw data
  }
}

String sendData(String command, const int timeout, boolean debug)
{
    String response = "";
    Serial.print(command); // Se envía el carácter de lectura a la esp8266
    long int time = millis();
    while( (time+timeout) > millis())
    {while(Serial.available())
      { 
        char c = Serial.read(); // Lee el siguiente carácter.
        response+=c;
      }  
    }
    
    if(debug)
    {
      Serial.print(response);
    }    
    return response;
}

