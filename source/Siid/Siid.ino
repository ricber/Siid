// uncomment this for dev mode (this is a trick to save precious memory space)
#define DEVMODE 1


void setup() {
    #if defined(DEVMODE)
        Serial.begin(115200);   // the speaker is communicating with the usual 9600 baud 
        Serial.println("Devmode ON");
    #endif
        
    randomSeed(millis()); // we initialize the random generator

    setupAll(); // setup of all components
}

void loop() {    
    //STATE UPDATES
    stateMachine();

    //PLAY ANIMATION
    playAnimation();
}

//Setup all the single components
void setupAll() {
    setupSpeaker();
    setupMatrix();
    setupThermoSensor();
    setupServo();
    setupState();
    setupSonars();
    setupAnimation();
    setupSphere();
}





