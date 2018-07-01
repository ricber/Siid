#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(10,11); // RX, TX

/**
 * folders: 
 * 01_happiness
 * 02_angry
 * 03_sadness
 * 04_fear
 * 05_disgust
 */
DFRobotDFPlayerMini myDFPlayer;

void setup() {

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
  
  myDFPlayer.volume(30);  //Set volume value. From 0 to 30
}



void loop() {
  // put your main code here, to run repeatedly:

     myDFPlayer.playFolder(06, 001);
            delay(15000);
            myDFPlayer.playFolder(06, 003);
            delay(15000);
            myDFPlayer.playFolder(06, 004);
            delay(15000);
            myDFPlayer.playFolder(06, 005);
            delay(15000);
            myDFPlayer.playFolder(06, 006);
            delay(15000);
  }

  

