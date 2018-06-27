// #### ANIMATIONS ####
enum Animation_enum {LOOKING, SADNESS, EXCITEMENT, JOY, ANGER, FEAR, DISGUST}; // all possible animations of the robot

// ### DEFINITION ###
#define LOOKING_TIME_OUT 800
#define JOY_SERVO_TIME_OUT 200
#define DISGUST_SERVO_TIME_OUT 150
#define JOY_EYE_TIME_OUT 6500
#define SAD_SERVO_TIME_OUT 1500
#define FEAR_SERVO_TIME_OUT 2000

byte current_animation; // current aniamtion of the robot
bool first_time_animation;

// #### TIME ####
unsigned long initial_animation_time;
unsigned long timer_anim_sad;

void playAnimation() {
    switch (current_animation) {
        case LOOKING:
            /* LOOKING
            *  Here the robot is moving the eye left and right
            *  Internal petals are closed
            *  External petals are open
            */
            if(first_time_animation){
                first_time_animation = false;
                #if defined(DEVMODE)
                    Serial.print("Animation: ");
                    Serial.println("LOOKING");
                #endif
                setEye(LOOKING);
            }
            else {
                showEyeAnimation();
            }
            break;
        case SADNESS:
            /* SADNESS
            * Open and semi-close petals very slowly
            * Eye with sad patterns
            * Make sound from a set of sad sounds
            * Sphere of blue colors
            */
            if(first_time_animation){
              first_time_animation = false;
              timer_anim_sad = millis(); 
              moveServo(30);
              sphereSadness();
              playAudio(SADNESS);
              setEye(SADNESS);

              #if defined(DEVMODE)
                Serial.print("Animation: ");
                Serial.println("SADNESS");
              #endif
            }
            else {
                showEyeAnimation();
                switch(selection(millis() - timer_anim_sad, SAD_SERVO_TIME_OUT, 4)){
                    case 0:
                        moveServo(0);
                        break;
                     case 1:
                        moveServo(45);
                        break;
                     case 2:
                        moveServo(0);
                        break;
                    case 3:
                        moveServo(30);
                        break;
                    default:
                        break;
                }
            }
            break;
        case EXCITEMENT:
            /* EXCITEMENT
            * 
            */
            break;
        case JOY:
            /* JOY
            *  Open and close rapidly internal
            *  Make a random sound from a set of happy sounds
            *  Eye with happy patterns
            *  Sphere with bright colors
            */
            /*
            if( first_time_animation){
              first_time_animation = false;
               #if defined(DEVMODE)
                    Serial.print("Animation: ");
                    Serial.println("JOY");
                #endif
              moveServo(45);
              if(millis() - initial_animation_time > JOY_SERVO_TIME_OUT){
                 moveServo(90);
                 long newTime = millis();
                 if(millis() - newTime > JOY_SERVO_TIME_OUT){
                  moveServo(0);
                  newTime = millis();
                  if(millis() - newTime > JOY_SERVO_TIME_OUT){
                    moveServo(60);
                  }
                 }
              }             
              showEyeAnimation();
              if(millis() - initial_animation_time > JOY_EYE_TIME_OUT){
               long newTime = millis();
               if(millis() - newTime > JOY_SERVO_TIME_OUT){
                  moveServo(80);
                  newTime = millis();
                  if(millis() - newTime > JOY_SERVO_TIME_OUT){
                    moveServo(60);
                  }
                 }
              }
            }
            */
            break;
        case ANGER:
            /* ANGER
            * 
            */
            #if defined(DEVMODE)
                Serial.print("Animation: ");
                Serial.println("ANGER");
            #endif
            break;
        
        case FEAR:
            /* FEAR
            * Closed and semi-open petals: internal petals closed and 
            * external open; all petals closed
            * Eye with fear patterns
            * Make sound from a set of fear sounds
            * Sphere of violet colors
            */
            /*
            if(first_time_animation){
              first_time_animation = false;
               #if defined(DEVMODE)
                    Serial.print("Animation: ");
                    Serial.println("FEAR");
                #endif
              sphereFear();
              moveServo(0);
              if(millis() - initial_animation_time > FEAR_SERVO_TIME_OUT){
                moveServo(60);
                 showEyeAnimation(); 
              }
            } 
            */
            break;
        case DISGUST:
            /* DISGUST
            *  Open and semi-closed petals
            *  Eye with disgust patterns
            *  Make sound from a set of disgust sounds
            *  Sphere of green colors
            */
            /*
            if(first_time_animation){
              first_time_animation = false;
              #if defined(DEVMODE)
                Serial.print("Animation: ");
                Serial.println("DISGUST");
                #endif 
              
              moveServo(0);
              if(millis() - initial_animation_time > DISGUST_SERVO_TIME_OUT){
                moveServo(60);
                sphereDisgust();
                showEyeAnimation();
              }             
            }  
            */               
            break;
        default:
            break;
    }
}

void setupAnimation(){
    initial_animation_time = millis();
    current_animation = LOOKING;
    first_time_animation = true;
}

void setAnimation(byte animation) {
    current_animation = animation;
    first_time_animation = true;
    initial_animation_time = millis();
}

