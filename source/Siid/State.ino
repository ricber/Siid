// #### LIBRARIES ####
#include <SparkFun_TB6612.h>

// #### DEFINITIONS ####

//---- LOOK AROUND ----
#define LK_TIME_OUT 8000 // look around timeout

//---- SPOT ROTATION ----
#define WHE_SPOT_ROT_TIME_OUT 1000 // the amount of time the robot moves left, right, forward and backward
#define SPOT_ROT_SPEED 200

//---- SAD ----
#define RAND_SAD_TIME_OUT 12000 // random sad animation timeout
#define RAND_SAD_PROB 50 // the probability (from 0 to 10000) to random start the sad animation
#define WHE_SAD_TIME_OUT 1000 // the amount of time each motor action in rand_sad_state lasts
#define RAND_SAD_SPEED 150  // the speed when the robot is sad (should be low)

//---- ANGER ----
#define ANGER_TIME_OUT 6700 // anger animation timeout 
#define ANGER_SPEED_BACK 150
#define ANGER_SPEED_FRONT 240
#define ANGER_PROB 9 

//---- FEAR ----
#define FEAR_TIME_OUT 4000 // fear animation time out
#define WHE_FEAR_TIME_OUT 500 // the amount of time each motor action go back
#define FEAR_SPEED 255
#define FEAR_PROB 4 

//---- DISGUST ----
#define DISGUST_TIME_OUT 4000 // disgust animation time out
#define WHE_DISGUST_TIME_OUT 500 // the amount of time each motor action go back


//---- EXCITEMENT ----
#define EXC_TIME_OUT 4500 // excitement timeout
#define EXCITEMENT_SPEED 200
#define WHE_EXC_TIME_OUT 1000 // the amount of time the wheels go left or right
#define BETWEEN_EXC_TIME_OUT 30000 // the amount of time in between two excitements 

//---- JOY ----
#define JOY_TIME_OUT 5000 //joy animation timeout
#define JOY_PROB 6 // the probability we want our robot to be happy in the random animation (value range [0, 10)); the prob of dishust is (10 - JOY_PROB)
#define WHE_JOY_TIME_OUT 500
#define JOY_SPEED 200

//---- WAITING INTERACTION ----
#define WAIT_TIME_OUT 15000 // time out after which we return in the looking around state

//---- GIGGLE STATE ----
#define GIGGLE_TIME_OUT 5000
#define WHE_GIGGLE_TIME_OUT 1000

//---- FRIGHT STATE ----
#define FRIGHT_TIME_OUT 5000

//---- SERVO ----
#define SERVO_CLOSED_DEGREE 85
#define SERVO_OPEN_DEGREE 30

// #### ROBOT STATE ####
enum State_enum {LOOK_AROUND, SPOT_ROTATION, RANDOM_SAD, JOY_STATE, DISGUST_STATE, ANGRY_STATE, EXCITEMENT_STATE, WAIT_INTERACTION, 
                 FRONT_COLLISION_STATE, REAR_COLLISION_STATE, FEAR_STATE, GIGGLE_STATE, FRIGHT_STATE, GO_AWAY}; // all possible states of the robot
byte current_state;     // current state of the robot
bool first_time_state; // boolean variable that indicates if you are entering a state for the first time or not


// #### TIME ####
unsigned long starting_time_state; // state beginning execution time
unsigned long last_excitement;
unsigned long timer_state1;
unsigned long timer_state2;
unsigned long timer_state3;
unsigned long timer_state4;
unsigned long timer_state5;
unsigned long timer_state6;
unsigned long timer_state7;
bool  case_state1;
bool  case_state2;
bool  case_state3;
bool  case_state4;
bool  case_state5;
bool  case_state6;
bool  case_state7;

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


// #### STATE MACHINE ####
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
            if (first_time_state){
                setAnimation(LOOKING);
                first_time_state = false;

                 #if defined(DEVMODE)
                    Serial.print("State: ");
                    Serial.println("LOOK AROUND");
                #endif
            }
            else if (millis() - starting_time_state > LK_TIME_OUT){
                setState(SPOT_ROTATION);               
            }
            else {
                byte sensors = front_sonar(); //read sonars distance

                if(sensors == SONAR_NEAR){
                    if(random(10) >= (10 - JOY_PROB)){
                        setState(JOY_STATE);
                    }
                    else {
                        setState(DISGUST_STATE);
                    }
                    #if defined(DEVMODE)
                        Serial.print("Sonar State: ");
                        Serial.println("FRONT SONAR NEAR");
                    #endif             
                }
                else if(sensors == SONAR_MEDIUM){
                    if (millis() - last_excitement >= BETWEEN_EXC_TIME_OUT) {
                        last_excitement = millis();
                        setState(EXCITEMENT_STATE);

                        #if defined(DEVMODE)
                            Serial.print("Sonar State: ");
                            Serial.println("FRONT SONAR MEDIUM");
                        #endif
                    } 
                }
                else if(sensors == SONAR_FAR){
                    #if defined(DEVMODE)
                        Serial.print("State: ");
                        Serial.println("FRONT SONAR FAR");
                    #endif
                    if(random(10000) >= (10000 - RAND_SAD_PROB)){
                        setState(RANDOM_SAD);
                    }
                }
                else if(thermosensor()){
                    setState(FRIGHT_STATE);

                    #if defined(DEVMODE)
                        Serial.println("Thermosensor HAND DETECTED");
                    #endif
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
                timer_state1 = millis() - WHE_SPOT_ROT_TIME_OUT;
                case_state1 = true;
                setAnimation(EXCITEMENT);

                #if defined(DEVMODE)
                    Serial.print("State: ");
                    Serial.println("SPOT ROTATION");
                #endif 
            }
            else {
                    if(millis() - timer_state1 >= WHE_SPOT_ROT_TIME_OUT && case_state1) {
                        left(motor1, motor2, SPOT_ROT_SPEED);  
                        case_state1 = false;
                        case_state2 = true;
                        timer_state2 = millis();
                    }
                    else if (millis() - timer_state2 >= WHE_SPOT_ROT_TIME_OUT && case_state2){
                        right(motor1, motor2, SPOT_ROT_SPEED);
                        case_state2 = false;
                        case_state3 = true;
                        timer_state3 = millis();
                    }
                    else if (millis() - timer_state3 >= WHE_SPOT_ROT_TIME_OUT && case_state3){
                        left(motor1, motor2, SPOT_ROT_SPEED);
                        case_state3 = false;
                        case_state4 = true;
                        timer_state4 = millis();
                    }
                    else if (millis() - timer_state4 >= WHE_SPOT_ROT_TIME_OUT && case_state4){
                        right(motor1, motor2, SPOT_ROT_SPEED);
                        case_state4 = false;
                        case_state5 = true;
                        timer_state5 = millis();
                    }
                    else if (millis() - timer_state5 >= WHE_SPOT_ROT_TIME_OUT && case_state5){
                        forward(motor1, motor2, 150);
                        case_state5 = false;
                        case_state6 = true;
                        timer_state6 = millis();
                    }
                    else if (millis() - timer_state6 >= WHE_SPOT_ROT_TIME_OUT && case_state6){
                        back(motor1, motor2, 150);
                        case_state6 = false;
                        case_state7 = true;
                        timer_state7 = millis();
                    }  
                    else if(millis() - timer_state7 >= WHE_SPOT_ROT_TIME_OUT && case_state7){
                         brake(motor1, motor2);
                         setState(LOOK_AROUND);        
                    }
            }                  
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
                timer_state1 = millis() - WHE_EXC_TIME_OUT;
                case_state1 = true;

                #if defined(DEVMODE)
                    Serial.print("State: ");
                    Serial.println("EXCITEMENT");
                #endif
            }else if(millis() - starting_time_state >= EXC_TIME_OUT){
                brake(motor1, motor2);  
                setState(LOOK_AROUND);
            } 
            else {
                if(millis() - timer_state1 >= WHE_EXC_TIME_OUT && case_state1) {
                    left(motor1, motor2, EXCITEMENT_SPEED); 
                    case_state1 = false;
                    case_state2 = true;
                    timer_state2 = millis();
                }
                else if (millis() - timer_state2 >= WHE_EXC_TIME_OUT && case_state2){
                    right(motor1, motor2, EXCITEMENT_SPEED);
                    case_state2 = false;
                    case_state1 = true;
                    timer_state1 = millis();
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
                timer_state1 = millis() - WHE_SAD_TIME_OUT;
                case_state1 = true;
            
                #if defined(DEVMODE)
                    Serial.print("State: ");
                    Serial.println("RANDOM SAD");
                #endif
            } 
            else if (millis() - starting_time_state >= RAND_SAD_TIME_OUT) {
                brake(motor1, motor2);  
                delay(1000); 
                setState(LOOK_AROUND); 
            }
            else if (front_sonar() == SONAR_COLLISION){
                brake(motor1, motor2);
                setState(FRONT_COLLISION_STATE);
            }
            else {
                if(millis() - timer_state1 >= WHE_SAD_TIME_OUT && case_state1) {
                    left(motor1, motor2, RAND_SAD_SPEED); 
                    case_state1 = false;
                    case_state2 = true;
                    timer_state2 = millis();
                }
                else if (millis() - timer_state2 >= WHE_SAD_TIME_OUT && case_state2){
                    forward(motor1, motor2, RAND_SAD_SPEED);
                    case_state2 = false;
                    case_state3 = true;
                    timer_state3 = millis();
                }
                else if (millis() - timer_state3 >= WHE_SAD_TIME_OUT && case_state3){
                    right(motor1, motor2, RAND_SAD_SPEED);
                    case_state3 = false;
                    case_state4 = true;
                    timer_state4 = millis();
                }
                else if (millis() - timer_state4 >= WHE_SAD_TIME_OUT && case_state4){
                    forward(motor1, motor2, RAND_SAD_SPEED);
                    case_state4 = false;
                    case_state1 = true;
                    timer_state1 = millis();
                }
            }  
            break;
        case JOY_STATE:
            /* JOY_STATE
             * In this state we perform a joy animation
            *  Then we continue to check if the object is still there
            *  If it remains there we wait for an interaction
            */
            if(first_time_state){
                first_time_state = false;
                setAnimation(JOY);
                timer_state1 = millis() - WHE_JOY_TIME_OUT;
                case_state1 = true;
                
                #if defined(DEVMODE)
                    Serial.print("State: ");
                    Serial.println("RANDOM ANIMATION JOY");
                #endif       
            }
            else if (millis() - starting_time_state >= JOY_TIME_OUT){
                brake(motor1, motor2);
                moveServo(SERVO_OPEN_DEGREE);
                setState(WAIT_INTERACTION);
            }
            else if (front_sonar() == SONAR_COLLISION){
                brake(motor1, motor2);
                setState(FRONT_COLLISION_STATE);
            }
            else{
                if(millis() - timer_state1 >= WHE_JOY_TIME_OUT && case_state1) {
                    left(motor1, motor2, JOY_SPEED); 
                    case_state1 = false;
                    case_state2 = true;
                    timer_state2 = millis();
                }
                else if (millis() - timer_state2 >= WHE_JOY_TIME_OUT && case_state2){
                    right(motor1, motor2, JOY_SPEED);
                    case_state2 = false;
                    case_state1 = true;
                    timer_state1 = millis();
                }
            }
        break;
    case DISGUST_STATE:
        /* DISGUST STATE
         * 
         */
        if(first_time_state){
            first_time_state= false; 
            setAnimation(DISGUST);
            timer_state1 = millis() - WHE_DISGUST_TIME_OUT;
            case_state1 = true;
            
            #if defined(DEVMODE)
                Serial.print("State: ");
                Serial.println("RANDOM ANIMATION DISGUST");
            #endif
         }else if (millis() - starting_time_state >= DISGUST_TIME_OUT){
                brake(motor1, motor2);
                moveServo(85);
                setState(GO_AWAY);
         }
         else if (rear_sonar() == SONAR_COLLISION){
                brake(motor1, motor2);
                setState(REAR_COLLISION_STATE);
         }
         else{
            if(millis() - timer_state1 >= 1000 && case_state1) {
                left(motor1, motor2, 140); 
                case_state1 = false;
                case_state2 = true;
                timer_state2 = millis();
             }
             else if (millis() - timer_state2 >= WHE_DISGUST_TIME_OUT && case_state2){
                right(motor1, motor2, 140);
                case_state2 = false;
                case_state3 = true;
                timer_state3 = millis();
              }
              else if (millis() - timer_state3 >= WHE_DISGUST_TIME_OUT && case_state3){
                back(motor1, motor2, 140);
                case_state3 = false;
                case_state1 = true;
                timer_state1 = millis();
              }
          }            
        break;
    case FRONT_COLLISION_STATE: 
        {
        /* COLLISION
        * In this state the object detected is too close
        * the robot stop moving
        * and it performs the FEAR animation.      * 
        * fear animation: the robot moves BACKWARD
        * emits scared sounds 
        * the eye reproduce the fear animation 
        * internal petals close
        */
        
        delay(500);
        back(motor1, motor2, 160);
        delay(1500); 
        setState(LOOK_AROUND);

        /*
        byte f_sonar = front_sonar();
        if(f_sonar == SONAR_NEAR || f_sonar == SONAR_MEDIUM || f_sonar == SONAR_FAR){
            setState(LOOK_AROUND);
        }  
        */
        }
        break;
    case REAR_COLLISION_STATE: 
        {
        /* COLLISION
        * In this state the object detected is too close
        * the robot stop moving
        * and it performs the FEAR animation. 
        * fear animation: the robot moves BACKWARD
        * emits scared sounds 
        * the eye reproduce the fear animation 
        * internal petals close
        */
        delay(500);
        forward(motor1, motor2, 160);
        delay(1500); 
        setState(LOOK_AROUND);
        /*
        byte r_sonar = rear_sonar();
        if(r_sonar == SONAR_NEAR || r_sonar == SONAR_MEDIUM || r_sonar == SONAR_FAR){
            setState(WAIT_INTERACTION);
        } 
        */ 
        }
        break;
    case WAIT_INTERACTION: 
        /* WAIT
         * The robot enters this state after performing 
        * an animation and wait for an event
        */
       if(first_time_state){
                first_time_state = false;
                setAnimation(LOOK_AROUND);
                                
                #if defined(DEVMODE)
                    Serial.println("State: WAIT INTERACTION");
                #endif       
        }
        else if (millis() - starting_time_state >= WAIT_TIME_OUT){
                setState(LOOK_AROUND);   
        }
        else if (thermosensor()){
            int probability = random(15);
            
            if(probability <= FEAR_PROB){
                setState(FEAR_STATE);
            }
            else if(probability <= ANGER_PROB && probability > FEAR_PROB){
                setState(ANGRY_STATE);
            }
            else{
              setState(GIGGLE_STATE);
            }
         }
        break;
    case ANGRY_STATE:
      if(first_time_state){
            first_time_state = false;
            timer_state1 = millis() - 400;
            case_state1 = true;
            setAnimation(ANGER);
                                
            #if defined(DEVMODE)
                Serial.println("State: ANGRY STATE");
            #endif       
       }
       else if (millis() - starting_time_state >= ANGER_TIME_OUT){
            brake(motor1, motor2);
            setState(LOOK_AROUND);   
       }
       else if (front_sonar() == SONAR_COLLISION){
            brake(motor1, motor2);
            setState(FRONT_COLLISION_STATE);
       }
       else if (rear_sonar() == SONAR_COLLISION){
            brake(motor1, motor2);
            setState(REAR_COLLISION_STATE);
       }
       else {
            if(millis() - timer_state1 >= 1000 && case_state1) {
                back(motor1, motor2, ANGER_SPEED_BACK); 
                moveServo(60);
                case_state1 = false;
                case_state2 = true;
                timer_state2 = millis();
            }
            else if (millis() - timer_state2 >= 600 && case_state2){
                forward(motor1, motor2, ANGER_SPEED_FRONT); 
                moveServo(SERVO_OPEN_DEGREE);
                case_state2 = false;
                case_state1 = true;
                timer_state1 = millis();
            }
        }      
        break;
    case FEAR_STATE:
        /*FEAR
        * In this state the robot trig the Fear animation
        * the wheels go backward fast
        */
        if(first_time_state){
            first_time_state = false;
            timer_state1 = millis() - WHE_FEAR_TIME_OUT;
            case_state1 = true;
            setAnimation(FEAR); 

            #if defined(DEVMODE)
                Serial.println("State: FEAR STATE");
            #endif
        }else if(millis() - starting_time_state > FEAR_TIME_OUT){
            brake(motor1,motor2);
            moveServo(SERVO_CLOSED_DEGREE);
            delay(1000);
            setState(LOOK_AROUND);
        }
        else if (rear_sonar() == SONAR_COLLISION){
            brake(motor1, motor2);
            setState(REAR_COLLISION_STATE);
        }                        
        else {
          if(millis() - timer_state1 >= WHE_FEAR_TIME_OUT && case_state1) {
                back(motor1, motor2, 255); 
                case_state1 = false;
                case_state2 = true;
                timer_state2 = millis();                  
            }
            else if (millis() - timer_state2 >= 3000 && case_state2){
                left(motor1, motor2, 255);
                case_state2 = false;
            }
        }
        break;
      /**
       * GIGGLE 
       * In this state the robot laugh 
       * in response of the human prossimity
       */
     case GIGGLE_STATE: 
       if(first_time_state){
            first_time_state = false;
            timer_state1 = millis() - WHE_GIGGLE_TIME_OUT;
            case_state1 = true;
            
            setAnimation(GIGGLE); 

            #if defined(DEVMODE)
                Serial.println("State: GIGGLE STATE");
            #endif
        }else if(millis() - starting_time_state > GIGGLE_TIME_OUT){
            playAudio(GOOD_BYE);
            moveServo(75);
            setState(GO_AWAY);
        }
        else {
            if(millis() - timer_state1 >= WHE_GIGGLE_TIME_OUT && case_state1) {
                left(motor1, motor2, 200); 
                case_state1 = false;
                case_state2 = true;
                timer_state2 = millis();                  
            }
            else if (millis() - timer_state2 >= WHE_GIGGLE_TIME_OUT && case_state2){
                right(motor1, motor2, 200);
                case_state2 = false;
                case_state1 = true;
                timer_state1 = millis();
            } 
        }
        break;
    case GO_AWAY:
        if(first_time_state){
            first_time_state = false;
            timer_state1 = millis() - 500;
            case_state1 = true;

            #if defined(DEVMODE)
                Serial.println("State: GO AWAY");
            #endif
        }
        else if (millis() - starting_time_state > 3000){
             setState(LOOK_AROUND);
        }
        else if (front_sonar() == SONAR_COLLISION){
            brake(motor1, motor2);
            setState(FRONT_COLLISION_STATE);
        }
        else {
            if(millis() - timer_state1 >= 500 && case_state1) {
                right(motor1, motor2, 230);
                case_state1 = false;
                case_state2 = true;
                timer_state2 = millis();                  
            }
            else if (millis() - timer_state2 >= 1000 && case_state2){
                forward(motor1, motor2, 230);  
                case_state2 = false;
                case_state3 = true;
                timer_state3 = millis();   
            }
            else if(millis() - timer_state3 >= 2000 && case_state3){
                brake(motor1, motor2);
                case_state3 = false;
            }    
         } 
        break;
    case FRIGHT_STATE:
        if(first_time_state){
            first_time_state = false;
            timer_state1 = millis() - 3000;
            case_state1 = true;
            
            setAnimation(FEAR); 

            #if defined(DEVMODE)
                Serial.println("State: FRIGHT STATE");
            #endif
        }else if(millis() - starting_time_state > FRIGHT_TIME_OUT){
            brake(motor1,motor2);
            moveServo(SERVO_CLOSED_DEGREE);
            delay(1000);
            setState(LOOK_AROUND);
        }
        else if (front_sonar() == SONAR_COLLISION){
            brake(motor1, motor2);
            setState(FRONT_COLLISION_STATE);
        }
        else {
            if(millis() - timer_state1 >= 500 && case_state1) {
                forward(motor1, motor2, 240); 
                case_state1 = false;
                case_state2 = true;
                timer_state2 = millis();                  
            }
            else if (millis() - timer_state2 >= 3000 && case_state2){
                left(motor1, motor2, 255);
                case_state2 = false;
            }
        }
        break;
    default: 
        break;
    }
}

// sets the current state of the robot and saves the previous one
void setState(byte state) {
    current_state       = state;
    first_time_state = true;
    starting_time_state = millis();
    case_state1 = false;
    case_state2 = false;
    case_state3 = false;
    case_state4 = false;
    case_state5 = false;
    case_state6 = false;
    case_state7 = false;
}

void setupState() {
    starting_time_state = millis();
    first_time_state = true;
    current_state  = LOOK_AROUND;
    last_excitement = millis();
}
