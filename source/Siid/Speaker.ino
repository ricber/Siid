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

void setupSpeaker() {
    mySoftwareSerial.begin(9600);
 
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
            if(random(10) > SOUND_PROB){
                myDFPlayer.playFolder(01, 1);
            }else{
                myDFPlayer.playFolder(01, 2);
            } 

            #if defined(DEVMODE)
                Serial.println("SPEAKER JOY");
            #endif 
            break;
        case ANGER:
            myDFPlayer.playFolder(02, 1);  

            #if defined(DEVMODE)
                Serial.println("SPEAKER ANGER");
            #endif
            break;
        case SADNESS:
            myDFPlayer.playFolder(03, 001);

            #if defined(DEVMODE)
                Serial.print("SPEAKER SADNESS");
            #endif
            break;
        case FEAR:
            myDFPlayer.playFolder(04, 001);

            #if defined(DEVMODE)
                Serial.print("SPEAKER FEAR");
            #endif
            break;
        case DISGUST:    
            if (random(10) > SOUND_PROB){
                myDFPlayer.playFolder(05, 001);
            }else{
                myDFPlayer.playFolder(05, 002);
            } 
            break;
        default: 
            break;
    }
}

