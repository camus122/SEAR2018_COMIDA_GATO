/*
  Software serial multple serial test

 Receives from the hardware serial, sends to software serial.
 Receives from software serial, sends to hardware serial.

 The circuit:
 * RX is digital pin 10 (connect to TX of other device)
 * TX is digital pin 11 (connect to RX of other device)

 Note:
 Not all pins on the Mega and Mega 2560 support change interrupts,
 so only the following can be used for RX:
 10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69

 Not all pins on the Leonardo support change interrupts,
 so only the following can be used for RX:
 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).

 created back in the mists of time
 modified 25 May 2012
 by Tom Igoe
 based on Mikal Hart's example

 This example code is in the public domain.

 */
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX
long int boud_rate_array[] = {1200,2400,4800,9600,19200,38400,57600, 74880,115200};


void setup() {
  Serial.begin(9600);  // Open serial communications and wait for port to open:
  while (!Serial);// wait for serial port to connect. Needed for native USB port only
  Serial.println("Goodnight moon!");
}
void loop() { // run over and over
  boolean f=Serial.available();
  String data="F :";
  if(f){
    data+="TRUE";
  }else{
    data+="false";
  }
  
  Serial.println(data);
  delay(1000);
  if (Serial.available()) {
    for (int i = 0; i<9;i++){
      set_esp8266_boud_rate(boud_rate_array[i]);
    }
  }
}

void set_esp8266_boud_rate(long int boud_rate){
  boolean boud_found=false;
  Serial.println(String(boud_rate) + "....");
  mySerial.begin(boud_rate); delay(2000);
/*
AT+UART - UART configuration, [@deprecated]
AT+UART_CUR - UART current configuration
AT+UART_DEF - UART default configuration, save to flash
*/
  mySerial.print("AT+UART_DEF\r\n");
//  mySerial.print("AT+CIOBAUD=115200\r\n");
  mySerial.print("AT+RESTORE\r\n");
  mySerial.print("AT\r\n");
  delay(100);
    boolean f=mySerial.available();
    String data="F33 :";
    if(f){
      data+="TRUE";
    }else{
      data+="false";
    }
      Serial.println(data);

  while (mySerial.available()) {
    Serial.print((char)mySerial.read());
    boud_found= true;
  }
  if (boud_found){
    boud_found = false;
    Serial.println("Boud rate: "+ String(boud_rate));
    delay(1000);
    while (Serial.available() < 1 );
  }
}

