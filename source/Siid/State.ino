// #### LIBRARIES ####
#include <SparkFun_TB6612.h>


// #### DEFINITIONS ####
#define LK_TIME_OUT 10000 // LOOK_AROUND timeout
#define FW_TIME_OUT 5000  // FORWARD timeout
#define SAD_TIME_OUT 5000 // sad animation timeout
#define HAPPY_PROB 7 // the probability we want our robot to be happy in the random animation (value range [0, 10])


// #### ROBOT STATE ####
enum State_enum {LOOK_AROUND, PERSON_DET, FORWARD, STOP_CHECK, ROTATE_SAD, RANDOM_ANIM_PERSON_CHECK, ANGRY}; // all possible states of the robot
byte current_state  = LOOK_AROUND; // current state of the robot
byte previous_state = LOOK_AROUND; // previous state of the robot
                                   
                                   
/* all possible sensors inputs
* THERMOSENSOR_UP means that it has detected a person
* THERMOSENSOR_DWN means that the obstacle is an object
*/
enum Sensors_enum
{NO_INPUT, THERMOSENSOR_UP, THERMOSENSOR_DWN, FRONT_SONAR, ACCELEROMETER};
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
    case PERSON_DET:
        /* PERSON DETECTED
         *  In this state the robot has detected a person
         *  It wants to know how far is the person
         *  and if the person is approching fast
         */
        if (sensors == FRONT_SONAR)
        {
            setState(RANDOM_ANIM_PERSON_CHECK);
        }

        break;
    case FORWARD:
        /* FORWARD
         *  In this state the robot move forward
         *  It stops after a certain amount of time
         *  or if the front sonar detect something close
         */
        forward(motor1, motor2, 150); // go forward
        if (millis() - starting_time_state > FW_TIME_OUT)
        {
            brake(motor1, motor2);
            setState(LOOK_AROUND);
        }
        else if (sensors == FRONT_SONAR)
        {
            setState(STOP_CHECK);
        }
        break;
    case STOP_CHECK:
        /* STOP_CHECK
         * In this state the robot first stops the wheels movement
         * and then it checks what is in front of it, a person or an obstacle
         */
        if (sensors == THERMOSENSOR_DWN)
        {
            setState(ROTATE_SAD);
        }
        else if (sensors == THERMOSENSOR_UP)
        {
            setState(PERSON_DET);
        }
        break;
    case ROTATE_SAD:
        /* ROTATE
         * In this state the robot turn randomly right or left to avoid the
         * obstacle
         * Then it starts the sad animation because it likes to interact with
         * people and so it's sad when approches an obstacle
         */
        if (millis() - starting_time_state > SAD_TIME_OUT){
            setState(LOOK_AROUND);
        }
        else if (front_sonar()){
            setState(STOP_CHECK);
        }
        break;
    case RANDOM_ANIM_PERSON_CHECK:
        /* RANDOM ANIMATION and PERSON PRESENCE CHECK
         *  In this state we perform a random animation between joy and disgust
         *  Then we continue to check if the person is still there
         *  If the person remains there we wait for an interaction
         *  Otherwise the robot goes away
         */
        if (random(10 <= HAPPY_PROB)){
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
}


// sets the current state of the robot and saves the previous one
void setState(byte state) {
    previous_state      = current_state;
    current_state       = state;
    starting_time_state = millis();
    #if defined(DEVMODE)
        Serial.print("State: ");
        Serial.println(state);
    #endif
}

void setupState() {
    starting_time_state = millis();
}
