// pin a cui collegare i piedini del LED RGB  
const int GREEN = 9 ;  
const int BLU = 12;  
const int RED = 8;  
  
void setupRGBLed() {  
  
  // set the digital pin as OUTPUT  
  pinMode(GREEN, OUTPUT);  
  pinMode(BLU, OUTPUT);  
  pinMode(RED, OUTPUT);   
  
  // At the beginning the LED is turned off  
  turnOff(); 
}  
  
// definizione di variabili globali  
int ValVerde;  

/**
 * The Sphere turn off 
 */
void turnOff(){
   // set GREEN, YELLOW and RED to the HIGH Value 
   Serial.print("LED OFF");
  digitalWrite(GREEN, HIGH);  
  digitalWrite(BLU, HIGH);  
  digitalWrite(RED, HIGH);  
}


/**
 * The sphere changes colors 
 * within the range of ORANGE and YELLOW
 * continuosly
 */
void colorJoy(){
  //ORANGE
   Serial.print("LED JOY");
   analogWrite( RED, 250);  
   analogWrite(BLU,0);
   analogWrite(GREEN,155);

   //TRANSITION TO YELLOW
   for(int i=1; i< 90; i++){
     analogWrite(GREEN,155 + i);
     //TODO: Add Delay 
   }
}

/**
 * The sphere blink continuosly 
 * with a RED color (RED -> OFF)
 */
void colorAnger(){
  Serial.print("LED ANGER");
   analogWrite( RED, 190);  
   analogWrite(BLU,0);
   analogWrite(GREEN,0);   
}

/**
 * The sphere blink slowly 
 * within the color range of DARK BLUE and
 * a MEDIUM BLU
 */
void colorSadness(){
  //Dark Blue
  Serial.print("LED SADNESS");
   analogWrite( BLU, 150);  
   analogWrite(RED,0);
   analogWrite(GREEN,0);
   
  for(int i= 1; i<100; i++){
     analogWrite( BLU, 150 + i);  
     //TODO: Add Timer
  }
}

/**
 * The sphere colors of GREEN
 */
void colorDisgust(){
  //GREEN
  Serial.print("LED DISGUST");
   analogWrite( BLU, 0);  
   analogWrite(RED,0);
   analogWrite(GREEN,190);
}

/**
 * The sphere become PURPLE
 */
void colorFear(){
  //PURPLE
  Serial.print("LED FEAR");
   analogWrite( BLU, 240);  
   analogWrite(RED,190);
   analogWrite(GREEN,0);
}  


