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

void sphereExcitement(){
    // TODO
}

/**
 * The sphere changes colors 
 * within the range of ORANGE and YELLOW
 * continuosly
 */
void sphereJoy(){
    //ORANGE YELLOW
    setColor(255, 180, 0);
        
    #if defined(DEVMODE)
        Serial.print("LED JOY");
    #endif 
}

/**
 * The sphere blink continuosly 
 * with a RED color (RED -> OFF)
 */
void sphereAnger(){
    setColor(215,0,0);  
    
    #if defined(DEVMODE)
        Serial.print("LED ANGER");
    #endif 
}

/**
 * The sphere blink slowly 
 * within the color range of DARK BLUE and
 * a MEDIUM BLU
 */
void sphereSadness1(){
  //Dark Blue
  setColor(0, 0, 190);
    
  #if defined(DEVMODE)
    Serial.println("LED SADNESS");
  #endif
}

void sphereSadness2(){
  //Dark Blue
  setColor( 0, 100, 255);
  
  #if defined(DEVMODE)
    Serial.println("LED SADNESS");
  #endif 
}

/**
 * The sphere colors of GREEN
 */
void sphereDisgust(){
    //GREEN
    setColor(0, 140, 40);
    
    #if defined(DEVMODE)
        Serial.print("LED DISGUST");
    #endif
}

/**
 * The sphere become PURPLE
 */
void sphereFear(){
    //PURPLE
     setColor(150,0,200);
     
    #if defined(DEVMODE)
        Serial.print("LED FEAR");
    #endif
}  

void setColor(int red, int green, int blue)
{
  analogWrite(RED_PIN, red);
  analogWrite(GREEN_PIN, green);
  analogWrite(BLUE_PIN, blue);  
}


