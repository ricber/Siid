#include <Adafruit_NeoPixel.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_GFX.h>
#include <Servo.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>
#include <SparkFun_TB6612.h>

//LED MATRIX

enum emotions {NEUTRAL, JOY}; // all possible animations of the robot

//define constants 
int DELAY_EYE = 1; // in ms

//define variables
byte emotion_prec = 0; //we define it on neutral
int emot=0;

//PIN LED
 //we define the pin that our NeoPixel panel is plugged into
  #define PIN 2
//we initialize our 8×8 matrix using the NeoMatrix library
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PIN,
  NEO_MATRIX_BOTTOM + NEO_MATRIX_LEFT +
  NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
  NEO_GRB + NEO_KHZ800);

struct RGB{
  byte r;
  byte g;
  byte b;
};
 
// Define some colors we'll use frequently
RGB vanillia = { 225, 246, 201 }; //neutral 254,254,226

RGB yellow1= { 255, 240, 183 };
RGB yellow2= { 255, 236, 143 };
RGB yellow3= { 255, 231, 113 };
RGB yellow4= { 255, 215, 0 }; //happy

RGB off = { 0, 0, 0 };

//define emotions
  bool const happy1[8][8] = {  
             {0, 0, 1, 1, 1, 1, 0, 0},
             {0, 1, 1, 1, 1, 1, 1, 0},
             {1, 1, 1, 1, 1, 1, 1, 1},
             {1, 1, 1, 0, 0, 1, 1, 1},
             {1, 1, 1, 0, 0, 1, 1, 1},
             {1, 1, 1, 1, 1, 1, 1, 1},
             {0, 1, 1, 1, 1, 1, 1, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
            };
  bool const happy2 [8][8] = {  
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 1, 1, 1, 1, 0, 0},
             {0, 1, 1, 1, 1, 1, 1, 0},
             {1, 1, 1, 0, 0, 1, 1, 1},
             {1, 1, 1, 0, 0, 1, 1, 1},
             {1, 1, 1, 1, 1, 1, 1, 1},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
            };        
  bool const happy3 [8][8] = {  
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 1, 1, 1, 1, 0, 0},
             {0, 1, 1, 1, 1, 1, 1, 0},
             {1, 1, 1, 0, 0, 1, 1, 1},
             {1, 1, 1, 1, 1, 1, 1, 1},
             {1, 0, 0, 0, 0, 0, 0, 1},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
            };         
  bool const happy4[8][8] = {  
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 1, 1, 1, 1, 0, 0},
             {0, 1, 1, 1, 1, 1, 1, 0},
             {1, 1, 0, 0, 0, 0, 1, 1},
             {1, 0, 0, 0, 0, 0, 0, 1},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0}
            };

   bool const neutral1[8][8] = {  
             {0, 0, 1, 1, 1, 1, 0, 0},
             {0, 1, 1, 1, 1, 1, 1, 0},
             {1, 1, 1, 1, 1, 1, 1, 1},
             {1, 1, 1, 0, 0, 1, 1, 1},
             {1, 1, 1, 0, 0, 1, 1, 1},
             {1, 1, 1, 1, 1, 1, 1, 1},
             {0, 1, 1, 1, 1, 1, 1, 0},
             {0, 0, 1, 1, 1, 1, 0, 0}
            };

   bool const neutral2[8][8] = {  
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 1, 1, 1, 1, 1, 1, 0},
             {1, 1, 1, 1, 1, 1, 1, 1},
             {1, 1, 1, 0, 0, 1, 1, 1},
             {1, 1, 1, 0, 0, 1, 1, 1},
             {1, 1, 1, 1, 1, 1, 1, 1},
             {0, 1, 1, 1, 1, 1, 1, 0},
             {0, 0, 0, 0, 0, 0, 0, 0}
            };

   bool const neutral3[8][8] = {  
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {1, 1, 1, 1, 1, 1, 1, 1},
             {1, 1, 1, 0, 0, 1, 1, 1},
             {1, 1, 1, 0, 0, 1, 1, 1},
             {1, 1, 1, 1, 1, 1, 1, 1},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0}
            };

    bool const neutral4[8][8] = {  
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {1, 1, 1, 1, 1, 1, 1, 1},
             {1, 1, 1, 1, 1, 1, 1, 1},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0}
            };   
            
   bool const turned_off[8][8] = {  
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0}
            };

//SERVO
Servo myservo; // create servo object to control a servo

//SPEAKER
//PIN SPEAKER
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

//MOTORS
//PIN MOTORS
// Pins for all inputs, keep in mind the PWM defines must be on PWM pins
// the default pins listed are the ones used on the Redbot (ROB-12097) with
// the exception of STBY which the Redbot controls with a physical switch
  #define AIN1 7
  #define BIN1 13
  #define AIN2 8
  #define BIN2 12
  #define PWMA 3
  #define PWMB 5
  #define STBY 10
// these constants are used to allow you to make your motor configuration
// line up with function names like forward.  Value can be 1 or -1
const int offsetA = 1;
const int offsetB = 1;

// Initializing motors.  The library will allow you to initialize as many
// motors as you have memory for.  If you are using functions like forward
// that take 2 motors as arguements you can either write new functions or
// call the function more than once.
Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);


void setup() {
  // put your setup code here, to run once:
   Serial.begin(115200);
   myservo.attach(9); // attaches the servo on pin 9 to the servo object
   setupSpeaker();
   setupLedMatrix();   
}

void loop() {
  // put your main code here, to run repeatedly:
 //put eyes to neutral and do 5 blink at each blink we can consider robot does something with petals. Or we choose to do an action afterwards
  for (int i=0; i<5; i++)
  {
     eyesInlight(NEUTRAL);
     delay(8*DELAY_EYE); //time to let the programm fully do the animation
     delay(1500);//to let time before changing
   
   // Movement of the petals
   
   //Movement on the wheels
   
}
 
 //changes eye to joy
  eyesInlight(JOY);
  //delay(8*DELAY_EYE); //time to let the programm fully do the animation
 //moves petals
  myservo.write(80);
  delay(100);
  myservo.write(60);
  delay(100);
  myservo.write(90);
  delay(100);
  myDFPlayer.playFolder(01,001);
  myservo.write(60);
  delay(100);
  myservo.write(90);
//plays sound
   myDFPlayer.playFolder(01,002);
 //moves wheels
   left(motor1, motor2, 300);
   delay(100);
   right(motor1, motor2, 300);
   delay(100);
   left(motor1, motor2, 300);
   delay(100);
   right(motor1, motor2, 300);
   delay(50);
   brake(motor1,motor2);
   myservo.write(0);
   delay(5000);
 
 
}

/**
 * setup the LED MATRIX
 */
void setupLedMatrix(){
    matrix.begin();
    matrix.setBrightness(5);
    matrix.setTextColor(matrix.Color(255, 255, 255) );
    matrix.setTextWrap(false);
}

/**
 * setup the SPEAKER
 */
void setupSpeaker(){
  mySoftwareSerial.begin(9600);
  
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
  
  myDFPlayer.volume(20);  //Set volume value. From 0 to 30
}

// Check the pixel one after another and fill them if necessary
void drawEye(bool eye[8][8], struct RGB color) {
  for(uint16_t row=0; row < 8; row++) {
    for(uint16_t column=0; column < 8; column++) {
      if (eye[row][column] == 1) { 
          matrix.drawPixel(column, row, matrix.Color(color.r, color.g, color.b));
          matrix.show();
        }
      else
      {
          matrix.drawPixel(column, row, matrix.Color(0, 0, 0));
          matrix.show();
      }
    }
  }
}

/**
 * Define the sequence of eye position for each emotion
 * and display them with a delay
 */
void eyesInlight(byte emotion)
{
  /*##########
   * 0 neutral
   * 1 happy
   * 2 angry
   * 3 sadness
   * 4 fear
   * 5 disgust
   ##########*/
  if (emotion!=emotion_prec) { 
     switch(emotion_prec) {
        case NEUTRAL:
          drawEye(neutral1, vanillia);
          delay(DELAY_EYE);
          drawEye(neutral2, vanillia);
          delay(DELAY_EYE);
          drawEye(neutral3, vanillia);
          delay(DELAY_EYE);
          drawEye(neutral4, vanillia);
          delay(DELAY_EYE);
          drawEye(turned_off, vanillia);
          delay(DELAY_EYE);
          drawEye(neutral4, vanillia);
          delay(DELAY_EYE);
          drawEye(neutral3, vanillia);
          delay(DELAY_EYE);
          drawEye(neutral2, vanillia);
          delay(DELAY_EYE);
          drawEye(neutral1, vanillia);
          break;
          
        case JOY:
          drawEye(happy4, yellow4);
          delay(DELAY_EYE);
          drawEye(happy3, yellow3);
          delay(DELAY_EYE);
          drawEye(happy2, yellow2);
          delay(DELAY_EYE);
          drawEye(happy1, yellow1);
          delay(DELAY_EYE);
          drawEye(neutral1, vanillia);
          delay(DELAY_EYE);
          break;
                    
        default:
          drawEye(turned_off, vanillia);                
          break;
     }
 
    switch(emotion) {
        case NEUTRAL:
          drawEye(neutral1, vanillia);
          delay(DELAY_EYE);
          drawEye(neutral2, vanillia);
          delay(DELAY_EYE);
          drawEye(neutral3, vanillia);
          delay(DELAY_EYE);
          drawEye(neutral4, vanillia);
          delay(DELAY_EYE);
          drawEye(turned_off, vanillia);
          delay(DELAY_EYE);
          drawEye(neutral4, vanillia);
          delay(DELAY_EYE);
          drawEye(neutral3, vanillia);
          delay(DELAY_EYE);
          drawEye(neutral2, vanillia);
          delay(DELAY_EYE);
          drawEye(neutral1, vanillia);
          break;
          
        case JOY:
          drawEye(neutral1, vanillia);
          delay(DELAY_EYE);
          drawEye(happy1, yellow1);
          delay(DELAY_EYE);
          drawEye(happy2, yellow2);
          delay(DELAY_EYE);
          drawEye(happy3, yellow3);
          delay(DELAY_EYE);
          drawEye(happy4, yellow4);
          delay(DELAY_EYE);
          break;
           
        default:
          drawEye(turned_off, vanillia);                
          break;
       }
       emotion_prec=emotion;
       Serial.println(emotion_prec);
     }
  
   else
     {
       switch(emotion) {
        case NEUTRAL:
          drawEye(neutral1, vanillia);
          delay(DELAY_EYE);
          drawEye(neutral2, vanillia);
          delay(DELAY_EYE);
          drawEye(neutral3, vanillia);
          delay(DELAY_EYE);
          drawEye(neutral4, vanillia);
          delay(DELAY_EYE);
          drawEye(turned_off, vanillia);
          delay(DELAY_EYE);
          drawEye(neutral4, vanillia);
          delay(DELAY_EYE);
          drawEye(neutral3, vanillia);
          delay(DELAY_EYE);
          drawEye(neutral2, vanillia);
          delay(DELAY_EYE);
          drawEye(neutral1, vanillia);
          emotion_prec=emotion;  
          break;
          
        case JOY:
          drawEye(happy4, yellow4);
          emotion_prec=emotion;
          break;
          
        default:
          drawEye(turned_off, vanillia);            
          break;
       }
     }
}

/**
 * Print the speaker details on the Serial
 */
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



