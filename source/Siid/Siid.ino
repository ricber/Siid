// uncomment this for dev mode (this is a trick to save precious memory space)
//#define DEVMODE 1


void setup() {
  #if defined(DEVMODE)
    Serial.begin(9600);
    Serial.print("Devmode ON");
  #endif
  
  // setup of all components
  setupAll();
  

}

void loop() {
  // put your main code here, to run repeatedly:

}

void setupAll(){

  
}

