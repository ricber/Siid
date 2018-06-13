#include <NewPing.h>

#define TRIGGER_PIN 6
#define ECHO_PIN 7
#define MAX_DISTANCE 400
#define DISTANCE_CLOSE 100

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

 
bool front_sonar() {
    delay(50);
    unsigned int distance = sonar.ping_cm();
    #if defined(DEVMODE)
       Serial.print(distance);
       Serial.println("cm");
    #endif
    if (distance <= DISTANCE_CLOSE){
        return true;
    }
    else {
        return false;
    }
}
