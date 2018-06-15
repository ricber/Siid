// uncomment this for dev mode (this is a trick to save precious memory space)
#define DEVMODE 1


void setup() {
    #if defined(DEVMODE)
        Serial.begin(9600);
        Serial.print("Devmode ON");
    #endif

    randomSeed(millis()); // we initialize the random generator

    setupAll(); // setup of all components
}

void loop() {
    // put your main code here, to run repeatedly:

    stateMachine();
    playAnimation();
}

void setupAll() {
    setupSpeaker();
    setupMatrix();
    setupState();
}



