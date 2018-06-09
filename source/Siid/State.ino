// #### DEFINITIONS ####
#define LK_TIME_OUT 10000 // LOOK_AROUND timeout
#define FW_TIME_OUT 5000 // FORWARD timeout
#define SAD_TIME_OUT 5000 // sad animation timeout

// #### ROBOT STATE ####
enum State_enum {LOOK_AROUND, PERSON_DET, FORWARD, STOP_CHECK, ROTATE_SAD}; // all possible states of the robot
/* all possible sensors inputs
 * THERMOSENSOR_UP means that it has detected a person
 * THERMOSENSOR_DWN means that the obstacle is an object
 */
enum Sensors_enum {NONE, THERMOSENSOR_UP, THERMOSENSOR_DWN, FRONT_SONAR}; 
byte current_state = LOOK_AROUND;           // current state of the robot
byte previous_state = LOOK_AROUND;          // previous state of the robot



// #### TIME ####
unsigned long starting_time_state;          // state beginning execution time


// state machine that controls the robot. Based on the current state and on the input it performs certain outputs and goes in the next state. 
void state_machine(byte sensors){
  switch(current_state){
    case LOOK_AROUND:
      /* LOOK AROUND
       *  In this state the robot is searching for people. 
       *  The eye is moving left and right
       *  Internal petals are closed
       *  External petals are opened
       */
       if (sensors == THERMOSENSOR_UP){
        setState(PERSON_DET); // person detected
        
       }
       else if (millis() - starting_time_state > LK_TIME_OUT){
            setState(FORWARD); // move forward
            wheels_forward();
       }
       break;
    case PERSON_DET:
      /* PERSON DETECTED
       *  In this state the robot has detected a person
       *  It wants to know how far is the person
       *  and if the person is approching fast
       */
       
      break;
    case FORWARD:
    /* FORWARD
     *  In this state the robot move forward
     *  It stops after a certain amount of time
     *  or if the front sonar detect something close
     */
       if (millis() - starting_time_state > FW_TIME_OUT){
            setState(LOOK_AROUND); 
       }
       else if (sensors == FRONT_SONAR){
        setState(STOP_CHECK);
        
       }

        break;
     case STOP_CHECK:
     /* STOP_CHECK
      * In this state the robot first stops the wheels movement
      * and then it checks what is in front of it, a person or an obstacle
      */
      if (sensors == THERMOSENSOR_DWN) {
        setState(ROTATE_SAD);
        
      }
      else if (sensors == THERMOSENSOR_UP) {
        setState(PERSON_DET);
      }
        
        break;
     case ROTATE_SAD:
        /* ROTATE
         * In this state the robot turn randomly right or left to avoid the obstacle
         * Then it starts the sad animation because it likes to interact with people and so it's sad when approches an obstacle 
         */
         if (millis() - starting_time_state > SAD_TIME_OUT) {
            setState(LOOK_AROUND);
         }
         else if (sensors == FRONT_SONAR) {
            setState(STOP_CHECK);
         }         
         break;
    default:
      break;
  }
}


// sets the current state of the robot and saves the previous one
void setState(byte state) {
  previous_state = current_state;
  current_state = state;
  starting_time_state = millis();
  #if defined(DEVMODE)
    Serial.print("State: ");
    Serial.println(state);
  #endif
  
}



