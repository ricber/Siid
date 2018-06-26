#include <NewPing.h>

#define TRIGGER_PIN 46
#define ECHO_PIN 44
#define MAX_DISTANCE 400
#define DISTANCE_VERY_CLOSE 4
#define DISTANCE_NEAR 80 
#define DISTANCE_FAR 200
#define DISTANCE_MEDIUM 120
#define MSRMNT_TIME_OUT 50 // measurement timeout

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

enum sonar_state {FRONT_SONAR_NEAR, FRONT_SONAR_MEDIUM, FRONT_SONAR_FAR, FRONT_SONAR_COLLISION}; //distance states of the sonar

// #### TIME ####
unsigned long last_measurement_time; // state beginning execution time

 
byte front_sonar() {
     if (millis() - last_measurement_time >= MSRMNT_TIME_OUT){
        unsigned int distance = sonar.ping_cm();
        last_measurement_time = millis();
        
        #if defined(DEVMODE)
            Serial.print("Sonar distance: ");
            Serial.print(distance);
            Serial.println("cm");
        #endif
    
        if(distance >= DISTANCE_FAR || distance == 0){
          
          //case state FRONT_SONAR_FAR or OUT OF RANGE
          #if defined(DEVMODE)
                Serial.print("Sonar State: ");
                Serial.println("FRONT SONAR FAR");
         #endif
         return FRONT_SONAR_FAR;
            
        }else if(distance <= DISTANCE_MEDIUM && distance > DISTANCE_NEAR){
            //case state FRONT_SONAR_MEDIUM 
            
              #if defined(DEVMODE)
                  Serial.print("Sonar State: ");
                  Serial.println("FRONT SONAR MEDIUM");
              #endif
            return FRONT_SONAR_MEDIUM; 
            
        }else if(distance <= DISTANCE_NEAR && distance > DISTANCE_VERY_CLOSE){
            //case state FRONT_SONAR_NEAR 
            
            #if defined(DEVMODE)
                  Serial.print("Sonar State: ");
                  Serial.println("FRONT SONAR NEAR");
              #endif
            return FRONT_SONAR_NEAR;
            
        }else if(distance <= DISTANCE_VERY_CLOSE){
            //case state FRONT_SONAR_COLLISION the object detected is too close 
            #if defined(DEVMODE)
                  Serial.print("Sonar State: ");
                  Serial.println("FRONT SONAR COLLISION");
              #endif
              setState(7);
            return FRONT_SONAR_COLLISION;
        }
     } 
}

void setupSonars(){
    last_measurement_time = millis();
}

