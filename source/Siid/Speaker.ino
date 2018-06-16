#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX

#define enum emotion_state {NEUTRAL, JOY, ANGER, SADNESS, FEAR, DISGUST} //define all the possible emotion states
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
void printDetail(uint8_t type, int value);

void setupSpeaker() {

  mySoftwareSerial.begin(9600);
  Serial.begin(115200);
  
  Serial.println();
  Serial.println("DFPlayer Mini Demo");
  Serial.println("Initializing DFPlayer ... (May take 3~5 seconds)");

  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));
  
  myDFPlayer.volume(10);  //Set volume value. From 0 to 30
  }

void printDetail(uint8_t type, int value){
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  } 
}

void playAudio(int emotionNumber){
  switch(emotion){
    case JOY:
    for(int i=0; i<2; i++){
       if (random(10) <= SOUND_PROB){
          myDFPlayer.playFolder(01,001);
        }else{
         myDFPlayer.playFolder(01,002);
        }
    }
    break;
    case ANGER:
     for(int i=0; i<2; i++){
       if (random(10) <= SOUND_PROB){
          myDFPlayer.playFolder(02,001);
        }else{
         myDFPlayer.playFolder(02,002);
        }
    break;
    case SADNESS:
     for(int i=0; i<2; i++){
       if (random(10) <= SOUND_PROB){
          myDFPlayer.playFolder(03,001);
        }else{
         myDFPlayer.playFolder(03,002);
        }
    break;
    case FEAR:
     for(int i=0; i<2; i++){
       if (random(10) <= SOUND_PROB){
          myDFPlayer.playFolder(04,001);
        }else{
         myDFPlayer.playFolder(04,002);
        }
    break;
    case DISGUST:
     for(int i=0; i<2; i++){
       if (random(10) <= SOUND_PROB){
          myDFPlayer.playFolder(05,001);
        }else{
         myDFPlayer.playFolder(05,002);
        }
    break;
    default: break;
  }
}

