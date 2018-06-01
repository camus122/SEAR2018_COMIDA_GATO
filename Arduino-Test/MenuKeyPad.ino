/* @file EventSerialKeypad.pde
 || @version 1.0
 || @author Alexander Brevig
 || @contact alexanderbrevig@gmail.com
 ||
 || @description
 || | Demonstrates using the KeypadEvent.
 || #
 || link: https://www.arduino.cc/en/Reference/LiquidCrystal
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
byte ledPin = 13; 

boolean blink = false;
boolean ledPin_state;


void setupKeyPad(){  
    pinMode(ledPin, OUTPUT);              // Sets the digital pin as output.
    digitalWrite(ledPin, HIGH);           // Turn the LED on.
    ledPin_state = digitalRead(ledPin);   // Store initial LED state. HIGH when LED is on.
    keypad.addEventListener(keypadEvent); // Add an event listener for this keypad
}



void startKeyPad(){    
    char key = keypad.getKey();
    if (key) {
        Serial.println(key);
    }
     if(key=='1'){
      keypadEvent(key);
      keypad.addEventListener(keypadEvent);
    }
    if (blink){
        digitalWrite(ledPin,!digitalRead(ledPin));    // Change the ledPin from Hi2Lo or Lo2Hi.
        delay(100);
    }
}



String hhmmBuffer="__:__";
// Taking care of some special events.
void keypadEvent(KeypadEvent key){
    keyEventPressed=true;
    switch (keypad.getState()){      
      case PRESSED:{
          if (key == '#') {
              digitalWrite(ledPin,!digitalRead(ledPin));       
              ledPin_state = digitalRead(ledPin);        // Remember LED state, lit or unlit.            
          }
          if (key == '1') {
              printLcdLine1("Aguante..");
              printLcdLine2("FLEMA!!");
          }
  
          if (key == '2') {
              printLcdLine1("PUTO EL QUE");
              printLcdLine2("    LEEE!!    xD");
              
          }   
          if (key == '0') {
              printLcdLine1("Contador:");
              keyEventPressed=false;
              keypad.addEventListener(0);
          }          
          break;
      }
      case RELEASED:{
          if (key == '*') {
              digitalWrite(ledPin,ledPin_state);    // Restore LED state from before it started blinking.
              blink = false;
          }
          break;
      }
      case HOLD:{
          if (key == '*') {
              blink = true;    // Blink the LED when holding the * key.
             printLcd("comida 1 HH MM ",hhmmBuffer);
              keypad.addEventListener(subMenuSetHour);        
           
          }
          
          break;
        }
      default:      Serial.flush();       
  
    }

    return;
}

int index=0;
void subMenuSetHour(KeypadEvent key){
    switch (keypad.getState()){      
      case PRESSED:{
               if(key!='#'){                  
                  if(index==2){index++;} //Esto es para que se saltee el ":"
                  hhmmBuffer[index]=key;   
                  printLcdLine2(hhmmBuffer);               
                  index++;
                  if(index==6) printLcd(hhmmBuffer,"guardado");
               }
               Serial.println(hhmmBuffer);
        }
       case HOLD:{
          if (key == '#') {
              blink = true;    // Blink the LED when holding the * key.
              sweepServo();
          }
       }
    }
}


