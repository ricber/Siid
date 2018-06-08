// #### DEFINITIONS ####
#define LK_TIME_OUT 10000 // LOOK_AROUND timeout
#define FW_TIME_OUT 5000 // FORWARD timeout

// #### ROBOT STATE ####
enum State_enum {LOOK_AROUND, PERSON_DET, FORWARD, STOP_CHECK}; // all possible states of the robot
enum Sensors_enum {NONE, THERMOSENSOR, FRONT_SONAR}; // all possible sensors inputs
uint8_t current_state = LOOK_AROUND;           // current state of the robot
uint8_t previous_state = LOOK_AROUND;          // previous state of the robot



// #### TIME ####
unsigned long starting_time_state;              // state beginning execution time


// state machine that controls the robot. Based on the current state and on the input it performs certain outputs and goes in the next state. 
void state_machine(uint8_t sensors){
  switch(current_state){
    case LOOK_AROUND:
      /* LOOK AROUND
       *  In this state the robot is searching for people. 
       *  The eye is moving left and right
       *  Internal petals are closed
       *  External petals are opened
       */
       if (sensors == THERMOSENSOR){
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
        
        break;
    default:
      break;
  }
}


// sets the current state of the robot and saves the previous one
void setState(uint8_t state) {
  previous_state = current_state;
  current_state = state;
  starting_time_state = millis();
  #if defined(DEVMODE)
    Serial.print("State: ");
    Serial.println(state);
  #endif
  
}



