// #### LIBRARIES ####
#include <SparkFun_TB6612.h>

// #### DEFINITIONS ####
#define LK_TIME_OUT 5000 // LOOK_AROUND timeout
#define BACK_TIME_OUT 500 // timeout to go BACKWARD
#define SPOT_TIME_OUT 10000  // SPOT ROTATION timeout
#define RAND_SAD_TIME_OUT 5000 // random sad animation timeout
#define EXC_TIME_OUT 8000 // excitement timeout
#define RAND_ANIM_TIME_OUT 4500 //random animation timeout
#define HAPPY_PROB 7 // the probability we want our robot to be happy in the random animation (value range [0, 10])
#define RAND_SAD_PROB 5 // the probability (from 0 to 10000) to random start the sad animation
#define ROTATION_TIME_OUT 1000 // amount of time of left and right rotation
#define MOVE_TIME_OUT 2000
#define WAIT_TIME_OUT 2000 //time out for waiting to do another action
#define EXCITEMENT_SPEED 255
#define WHE_EXC_TIME_OUT 1000 // the amount of time the wheels go left or right
#define WHE_SAD_TIME_OUT 1000 // the amount of time each motor action in rand_sad_state lasts
#define RAND_SAD_SPEED 255

// #### ROBOT STATE ####

enum State_enum {LOOK_AROUND, SPOT_ROTATION, RANDOM_SAD , RANDOM_ANIMATION, ANGRY, EXCITEMENT_STATE, WAIT_INTERACTION, COLLISION, FEAR_STATE}; // all possible states of the robot
byte current_state; // current state of the robot
byte previous_state; // previous state of the robot
bool first_time_state; // boolean variable that indicates if you are entering a state for the first time or not
                                   
                                   
/* all possible sensors inputs
* THERMOSENSOR_UP means that it has detected a person
* THERMOSENSOR_DWN means that the obstacle is an object
*/
byte sensors;


// #### TIME ####
unsigned long starting_time_state; // state beginning execution time
unsigned long timer_excitement;
unsigned long timer_rand_sad;

// #### WHEELS MOTORS ####
// Pins for all inputs, keep in mind the PWM defines must be on PWM pins
// the default pins listed are the ones used on the Redbot (ROB-12097) with
// the exception of STBY which the Redbot controls with a physical switch
#define AIN1 34
#define BIN1 38
#define AIN2 32
#define BIN2 40
#define PWMA 2
#define PWMB 3
#define STBY 36

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


// state machine that controls the robot. Based on the current state and on the
// input it performs certain outputs and goes in the next state.
void stateMachine() {
    switch (current_state){
    case LOOK_AROUND:
        /* LOOK AROUND
         *  In this state the robot is searching for people.
         *  The eye is moving left and right
         *  Internal petals are closed
         *  External petals are opened
         */ 
        sensors = front_sonar();
        if (first_time_state){
            setAnimation(LOOKING);
            #if defined(DEVMODE)
                Serial.print("State: ");
                Serial.println("LOOK AROUND");
            #endif
            first_time_state = false;
        }
        else if (millis() - starting_time_state > LK_TIME_OUT){
              setState(SPOT_ROTATION);               
            }
        else if(sensors == FRONT_SONAR_COLLISION){ 
              #if defined(DEVMODE)
                  Serial.print("Sonar State: ");
                  Serial.println("FRONT SONAR COLLISION");
              #endif   
              setState(COLLISION);
            }
        else if(sensors == FRONT_SONAR_NEAR){
              #if defined(DEVMODE)
                  Serial.print("Sonar State: ");
                  Serial.println("FRONT SONAR NEAR");
              #endif
              setState(RANDOM_ANIMATION);              
            }
        else if(sensors == FRONT_SONAR_MEDIUM){
              #if defined(DEVMODE)
                  Serial.print("Sonar State: ");
                  Serial.println("FRONT SONAR MEDIUM");
              #endif
              setState(EXCITEMENT_STATE);
        }
        else if(sensors == FRONT_SONAR_FAR){
            /*
            #if defined(DEVMODE)
                Serial.print("Sonar State: ");
                Serial.println("FRONT SONAR FAR");
            #endif
            */
           if(random(10000) >= (10000 - RAND_SAD_PROB)){
                    setState(RANDOM_SAD);
              }
        }
       break;
    case SPOT_ROTATION:
        /* SPOT ROTATION
         *  In this state the robot has detected an object 
         *  that is far or has not detected anything.
         *  The robot rotate LEFT and RIGHT and
         *  makes little movement FORWARD and BACKWARD.
         *  The Eye is in the neutral state 
         *  Internal petals open and close 
         *  External petals close
         */
        if(first_time_state){
            first_time_state = false;
            left(motor1, motor2, 200);       
            right(motor1, motor2, 200);
            left(motor1, motor2, 200);
            right(motor1,motor2,200);

            #if defined(DEVMODE)
                Serial.print("State: ");
                Serial.println("SPOT ROTATION");
            #endif
        }else if (millis() - starting_time_state > ROTATION_TIME_OUT) {
            brake(motor1, motor2);
        }        
        forward(motor1, motor2, 100);
        back(motor1,motor2,100);
        if(millis() -  starting_time_state > MOVE_TIME_OUT){
          brake(motor1,motor2);
        }
        setState(LOOK_AROUND);                    
        break;
    case EXCITEMENT_STATE: 
        /* EXCITEMENT
         * In this state the robot moves the Internal petals 
         * continuosly opening and closing them
         * it makes also excitement and joy sound
         */
        if(first_time_state){
            first_time_state = false; 
            setAnimation(EXCITEMENT);  
            timer_excitement = millis();

            #if defined(DEVMODE)
                Serial.print("State: ");
                Serial.println("EXCITEMENT");
            #endif
        }else if(millis() - starting_time_state >= EXC_TIME_OUT){
          brake(motor1, motor2);  
          setState(LOOK_AROUND);
        } 
        else {
            switch(selection(millis() - timer_excitement, WHE_EXC_TIME_OUT, 2)){
                case 0:
                    left(motor1, motor2, EXCITEMENT_SPEED); 
                    break;
                case 1:
                    right(motor1, motor2, EXCITEMENT_SPEED);
                    break;
                default:
                    break;
            }
        }
    break;     
    case RANDOM_SAD:
        /* RANDOM SAD
         * In this state we perform randomly the animation sad 
         * with a certain probability otherwise it go back in the previous state
         * Sad animation : In this state the robot turn right and left very or  
         * moves very slowly
         */
         if (first_time_state) {
            first_time_state = false;  
            setAnimation(SADNESS);
            timer_rand_sad = millis(); 

            #if defined(DEVMODE)
                Serial.print("State: ");
                Serial.println("RANDOM SAD");
            #endif
         } 
         else if (millis() - starting_time_state >= RAND_SAD_TIME_OUT) {
            brake(motor1, motor2);   
            setState(LOOK_AROUND); 
         }
         else {
             switch(selection(millis() - timer_rand_sad, WHE_SAD_TIME_OUT, 4)){
                case 0:
                    left(motor1, motor2, RAND_SAD_SPEED); 
                    break;
                case 1:
                    forward(motor1, motor2, RAND_SAD_SPEED);
                    break;
                case 2:
                    right(motor1, motor2, RAND_SAD_SPEED);
                    break;
                case 3:
                    forward(motor1, motor2, RAND_SAD_SPEED);
                    break;
                default:
                    break;
            }  
         }
        break;
    case RANDOM_ANIMATION:
        /* RANDOM ANIMATION 
         *  In this state we perform a random animation between joy and disgust
         *  Then we continue to check if the object is still there
         *  If the it remains there we wait for an interaction
         *  Otherwise the robot moves
         */
        if (random(10) <= HAPPY_PROB){

            if(first_time_state){
              first_time_state= false;

               #if defined(DEVMODE)
                    Serial.print("State: ");
                    Serial.println("RANDOM ANIMATION JOY");
               #endif
              left(motor1, motor2, 300);
              right(motor1, motor2, 300);
              left(motor1, motor2, 300);
              right(motor1, motor2, 300);
              sensors = front_sonar();
              if(sensors == FRONT_SONAR_COLLISION){
                  setState(COLLISION);
                  break;
               }
              if(millis() - starting_time_state > ROTATION_TIME_OUT){
                brake(motor1, motor2);
              }          
              setAnimation(JOY);
            }
        }
        else{
           if(first_time_state){
             first_time_state= false;  
              #if defined(DEVMODE)
                    Serial.print("State: ");
                    Serial.println("RANDOM ANIMATION DISGUST");
               #endif
                        
              back(motor1,motor2,50);
              if(millis() - starting_time_state > ROTATION_TIME_OUT ){
                left(motor1,motor2,25);
                right(motor1,motor2,25);
                sensors = front_sonar();
                if(sensors == FRONT_SONAR_COLLISION){
                  setState(COLLISION);
                  break;
                }
                brake(motor1,motor2);
              }
             setAnimation(DISGUST);
           }
        }
        if(millis() - starting_time_state > RAND_ANIM_TIME_OUT){
           sensors = front_sonar();
                if(sensors == FRONT_SONAR_COLLISION){
                  setState(COLLISION);
                }else{
                  setState(WAIT_INTERACTION);
                }
              }
        break;
    case COLLISION: 
     /* COLLISION
      * In this state the object detected is too close
      * the robot stop moving
      * and it performs the FEAR animation.      * 
      * fear animation: the robot moves BACKWARD
      * emits scared sounds 
      * the eye reproduce the fear animation 
      * internal petals close
      */
       if(first_time_state){
             first_time_state= false;

             #if defined(DEVMODE)
                Serial.print("State: ");
                Serial.println("COLLISION");
             #endif
             
             brake(motor1, motor2);
              
             if(random(1)>0){
                left(motor1,motor2,50);
                right(motor1,motor2,50);
                left(motor1,motor2,50);
                right(motor1,motor2,50);
              if(millis() - starting_time_state > ROTATION_TIME_OUT ){
                brake(motor1,motor2);
              }
             }else{
              back(motor1,motor2,300);
              if(millis() - starting_time_state > BACK_TIME_OUT){
                brake(motor1,motor2);
              }
             }
             setAnimation(FEAR);

             sensors = front_sonar();

             if(sensors == FRONT_SONAR_NEAR || FRONT_SONAR_MEDIUM || FRONT_SONAR_FAR){
                setState(WAIT_INTERACTION);
             }else {
                setState(COLLISION);
             }
           }    
      
        break;
    case WAIT_INTERACTION: 
        /* WAIT
         * The robot enters this state after performing 
        * an animation and wait for an event
        */
       
        setState(LOOK_AROUND);
        break;
    case FEAR_STATE:
        /*FEAR
        * In this state the robot trig the Fear animation
        * the wheels go backward fast
        */
        if(first_time_state){
        first_time_state= false;
         #if defined(DEVMODE)
             Serial.print("State: ");
             Serial.println("FEAR STATE");
        #endif
        back(motor1,motor2,255);
        if(millis() - starting_time_state > BACK_TIME_OUT){
            brake(motor1,motor2);
        }
        setAnimation(FEAR);       
        }
        break;
    default: 
        break;
    }
}

// sets the current state of the robot and saves the previous one
void setState(byte state) {
    previous_state      = current_state;
    current_state       = state;
    first_time_state = true;
    starting_time_state = millis();
}

void setupState() {
    starting_time_state = millis();
    first_time_state = true;
    current_state  = LOOK_AROUND;
    previous_state = LOOK_AROUND;
    sensors = NO_INPUT;
}

// this function return a number between 0 and (mod-1). It tells how much times has elapsed a "timeout" amount of time modulo "mod"
byte selection(unsigned long current_delay, unsigned long timeout, byte mod){
    int integer_division = current_delay / timeout;
    return integer_division % mod;
}

