#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX

#define SOUND_PROB 5 //probability to play a sound instead of another

/**
 * folders: 
 * 01_happiness
 * 02_angry
 * 03_sadness
 * 04_fear
 * 05_disgust
 */
 
DFRobotDFPlayerMini myDFPlayer;
// ####TIMER####
 static unsigned long timer = millis();

void setupSpeaker() {
  mySoftwareSerial.begin(9600);
  
  Serial.println();
 
  Serial.println("Initializing DFPlayer ... (May take 3~5 seconds)");

  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));

  myDFPlayer.volume(30);  //Set volume value. From 0 to 30
}

void playAudio(byte emotion){
  switch(emotion){
    case JOY:
     #if defined(DEVMODE)
        Serial.print("SPEAKER JOY");
    #endif 
    myDFPlayer.playFolder(01,1);
    delay(50);
    break;
    case ANGER:
     #if defined(DEVMODE)
        Serial.print("SPEAKER ANGER");
    #endif
     myDFPlayer.playFolder(02,1);      
    break;
    case SADNESS:
     for(int i=0; i<2; i++){
       if (random(10) <= SOUND_PROB){
          myDFPlayer.playFolder(03,001);
        }else{
         myDFPlayer.playFolder(03,002);
        }
     }
    break;
    case FEAR:
     for(int i=0; i<2; i++){
       if (random(10) <= SOUND_PROB){
          myDFPlayer.playFolder(04,001);
        }else{
         myDFPlayer.playFolder(04,002);
        }
     }
    break;
    case DISGUST:
     for(int i=0; i<2; i++){
       if (random(10) <= SOUND_PROB){
          myDFPlayer.playFolder(05,001);
        }else{
         myDFPlayer.playFolder(05,002);
        }
     }
    break;
    default: break;
  }
}

