// #### LIBRARIES ####
#include <SparkFun_TB6612.h>


// #### DEFINITIONS ####
#define LK_TIME_OUT 2000 // LOOK_AROUND timeout
#define SPOT_TIME_OUT 5000  // SPOT ROTATION timeout
#define SAD_TIME_OUT 5000 // sad animation timeout
#define EXC_TIME_OUT 3000 // excitement timeout
#define RAND_ANIM_TIME_OUT 5000 //random animation timeout
#define HAPPY_PROB 7 // the probability we want our robot to be happy in the random animation (value range [0, 10])
#define SAD_PROB 5 // the probability to random start the sad animation
#define ROTATION_TIME_OUT 1000 // amount of time of left and right rotation


// #### ROBOT STATE ####

enum State_enum {LOOK_AROUND, SPOT_ROTATION, RANDOM_SAD , RANDOM_ANIMATION, ANGRY, EXCITEMENT, WAIT_INTERACTION, COLLISION}; // all possible states of the robot
byte current_state  = LOOK_AROUND; // current state of the robot
byte previous_state = LOOK_AROUND; // previous state of the robot
bool first_time_state; // boolean variable that indicates if you are entering a state for the first time or not
                                   
                                   
/* all possible sensors inputs
* THERMOSENSOR_UP means that it has detected a person
* THERMOSENSOR_DWN means that the obstacle is an object
*/
enum Sensors_enum
{NO_INPUT, THERMOSENSOR_UP, THERMOSENSOR_DWN, ACCELEROMETER};
byte sensors = NO_INPUT;


// #### TIME ####
unsigned long starting_time_state; // state beginning execution time


// #### WHEELS MOTORS ####

// Pins for all inputs, keep in mind the PWM defines must be on PWM pins
// the default pins listed are the ones used on the Redbot (ROB-12097) with
// the exception of STBY which the Redbot controls with a physical switch
#define AIN1 9
#define BIN1 11
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


// state machine that controls the robot. Based on the current state and on the
// input it performs certain outputs and goes in the next state.
void stateMachine() {
    switch (current_state)
    {
    case LOOK_AROUND:
        /* LOOK AROUND
         *  In this state the robot is searching for people.
         *  The eye is moving left and right
         *  Internal petals are closed
         *  External petals are opened
         */
        setAnimation(LOOKING);
        if (sensors == THERMOSENSOR_UP)
        {
            setState(PERSON_DET); // person detected
        }
        else if (millis() - starting_time_state > LK_TIME_OUT)
        {
            setState(FORWARD); // move forward
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

        sensor = front_sonar();
        if (sensors == FRONT_SONAR_NEAR)
        {
            setState(RANDOM_ANIM_PERSON_CHECK);
        }

        break;
    case EXCITEMENT: 
        /* EXCITEMENT
         * In this state the robot moves the Internal petals 
         * continuosly opening and closing them
         * it makes also excitement and joy sound
         */
         
    break;     
    case RANDOM_SAD:
        /* RANDOM SAD
         * In this state we perform randomly the animation sad 
         * with a certain probability otherwise it go back in the previous state
         * Sad animation : In this state the robot turn right or left
         * Then it starts the sad animation because it likes to interact with
         * people and so it's sad when approches an obstacle
         */
         if (first_time_state) {
            first_time_state = false;  
            if(random(1)) {
                left(motor1, motor2, 100);
            }
            else {
                right(motor1, motor2, 100);
            }  
         }
         else if (millis() - starting_time_state > ROTATION_TIME_OUT) {
            brake(motor1, motor2);
            setAnimation(SADNESS);
            
            if (millis() - starting_time_state > SAD_TIME_OUT){
                setState(LOOK_AROUND);
            }
            else if (front_sonar()){
                setState(STOP_CHECK);
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
            setAnimation(JOY);
        }
        else{
            setAnimation(DISGUST);
        }

        if (sensors == ACCELEROMETER){
            setState(ANGRY);
        }
        break;
    default:
        break;
    }
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
    break;
    case WAIT_INTERACTION: 
     /* WAIT
      * The robot enters this state after performing 
      * an animation and wait for an event
      */    
    break;
}


// sets the current state of the robot and saves the previous one
void setState(byte state) {
    previous_state      = current_state;
    current_state       = state;
    first_time_state = true;
    starting_time_state = millis();
    #if defined(DEVMODE)
        Serial.print("State: ");
        Serial.println(state);
    #endif
}

void setupState() {
    starting_time_state = millis();
    first_time_state = true;
}
