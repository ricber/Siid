// pin a cui collegare i piedini del LED RGB  
#define RED_PIN 8
#define GREEN_PIN 12
#define BLUE_PIN 9

  
void setupSphere(){  
  
  // set the digital pin as OUTPUT  
  pinMode(GREEN_PIN, OUTPUT);  
  pinMode(BLUE_PIN, OUTPUT);  
  pinMode(RED_PIN, OUTPUT);   

   #if defined(DEVMODE)
        Serial.println("LED setup");
   #endif
  
  // At the beginning the LED is turned off  
  turnOff(); 
}  

/**
 * The sphere turns off 
 */
void turnOff(){
    // set GREEN, YELLOW and RED to the HIGH Value 
    #if defined(DEVMODE)
        Serial.println("LED OFF");
    #endif
    
    digitalWrite(RED_PIN, LOW); 
    digitalWrite(GREEN_PIN, LOW);  
    digitalWrite(BLUE_PIN, LOW);    
}


void sphereLooking(){
    //Dark Blue
  
    setColor(0, 255, 50);

    #if defined(DEVMODE)
        Serial.println("LED LOOKING");
    #endif 
}

void shpereExcitement(){
    // TODO
}

/**
 * The sphere changes colors 
 * within the range of ORANGE and YELLOW
 * continuosly
 */
void sphereJoy(){
    //ORANGE

    setColor(250, 155, 0);
    
    #if defined(DEVMODE)
        Serial.print("LED JOY");
    #endif 
}

/**
 * The sphere blink continuosly 
 * with a RED color (RED -> OFF)
 */
void sphereAnger(){
    /*
    #if defined(DEVMODE)
        Serial.print("LED ANGER");
    #endif 
   analogWrite( RED, 190);  
   analogWrite(BLU,0);
   analogWrite(GREEN,0); 
   */  
}

/**
 * The sphere blink slowly 
 * within the color range of DARK BLUE and
 * a MEDIUM BLU
 */
void sphereSadness(){
  //Dark Blue
  #if defined(DEVMODE)
    Serial.println("LED SADNESS");
  #endif 
  setColor(0, 0, 150);
  /*
  for(int i= 1; i<100; i++){
     setColor(0, 0, 150 + i); 
     //TODO: Add Timer
  }
  */
}

/**
 * The sphere colors of GREEN
 */
void sphereDisgust(){
    /*
    //GREEN
    #if defined(DEVMODE)
        Serial.print("LED DISGUST");
    #endif
   analogWrite(BLU, 0);  
   analogWrite(RED,0);
   analogWrite(GREEN,190);
   */
}

/**
 * The sphere become PURPLE
 */
void sphereFear(){
    /*
    //PURPLE
    #if defined(DEVMODE)
        Serial.print("LED FEAR");
    #endif
    analogWrite( BLU, 240);  
    analogWrite(RED,190);
    analogWrite(GREEN,0);
    */
}  

void setColor(int red, int green, int blue)
{
  analogWrite(RED_PIN, red);
  analogWrite(GREEN_PIN, green);
  analogWrite(BLUE_PIN, blue);  
}


