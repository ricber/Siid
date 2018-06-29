#include <NewPing.h>

#define TRIGGER_PIN 46
#define ECHO_PIN 44
#define MAX_DISTANCE 400
#define MSRMNT_TIME_OUT 50 // measurement timeout

#define DISTANCE_VERY_CLOSE 5
#define DISTANCE_NEAR 50 
#define DISTANCE_MEDIUM 160
#define DISTANCE_FAR 250


NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
enum Sonar_enum{FRONT_SONAR_NEAR, FRONT_SONAR_MEDIUM, FRONT_SONAR_FAR, FRONT_SONAR_COLLISION};


// #### TIME ####
unsigned long last_measurement_time; // state beginning execution time

 
byte front_sonar() {
     if (millis() - last_measurement_time >= MSRMNT_TIME_OUT){
        unsigned int distance = sonar.ping_cm();
        last_measurement_time = millis();
        
        if(distance >= DISTANCE_FAR || distance == 0){
          
            //case state FRONT_SONAR_FAR or OUT OF RANGE
            return FRONT_SONAR_FAR;
            
        }else if(distance <= DISTANCE_MEDIUM && distance > DISTANCE_NEAR){
            
            return FRONT_SONAR_MEDIUM; 
            
        }else if(distance <= DISTANCE_NEAR && distance > DISTANCE_VERY_CLOSE){
                      
            return FRONT_SONAR_NEAR;
            
        }else if(distance <= DISTANCE_VERY_CLOSE){
            
            //the object detected is too close
            return FRONT_SONAR_COLLISION;
        }
     }
}

void setupSonars(){
    last_measurement_time = millis();
}

