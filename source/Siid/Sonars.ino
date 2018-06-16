#include <NewPing.h>

#define TRIGGER_PIN 6
#define ECHO_PIN 7
#define MAX_DISTANCE 400
#define DISTANCE_VERY_CLOSE 5
#define DISTANCE_NEAR 70 
#define DISTANCE_FAR 200
#define DISTANCE_MEDIUM 150

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

enum sonar_state {FRONT_SONAR_NEAR, FRONT_SONAR_MEDIUM, FRONT_SONAR_FAR, FRONT_SONAR_COLLISION}; //distance states of the sonar

 
byte front_sonar() {
    delay(50);
    unsigned int distance = sonar.ping_cm();
    #if defined(DEVMODE)
       Serial.print(distance);
       Serial.println("cm");
    #endif
    
    if(distance >= DISTANCE_FAR || distance == 0){
      //case state FRONT_SONAR_FAR or OUT OF RANGE
      return FRONT_SONAR_FAR;
    }else if(distance <= DISTANCE_MEDIUM && distance > DISTANCE_NEAR){
      //case state FRONT_SONAR_MEDIUM 
      return FRONT_SONAR_MEDIUM; 
    }else if(distance <= DISTANCE_NEAR && distance > 0){
       //case state FRONT_SONAR_NEAR 
       return FRONT_SONAR_NEAR;
    }else if(distance <= DISTANCE_VERY_CLOSE){
      //case state FRONT_SONAR_COLLISION the object detected is too close 
      return FRONT_SONAR_COLLISION;
    }
}
