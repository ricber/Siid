// #### ANIMATIONS ####
enum Animation_enum {NEUTRAL, LOOKING, EXCITEMENT, JOY, ANGER, SADNESS, FEAR, DISGUST}; // all possible animations of the robot

// ### DEFINITION ###
#define LOOKING_TIME_OUT 800
#define JOY_SERVO_TIME_OUT 200
#define DISGUST_SERVO_TIME_OUT 150
#define JOY_EYE_TIME_OUT 6500
#define SAD_SERVO_TIME_OUT 1500
#define SAD_ANIM_TIME_OUT 8000
#define FEAR_SERVO_TIME_OUT 2000

byte current_animation; // current aniamtion of the robot

bool first_animation_state;

// #### TIME ####
unsigned long initial_animation_time;



void setAnimation(byte animation) {
    current_animation = animation;
    first_animation_state = true;
    initial_animation_time = millis();
}

void playAnimation() {
    switch (current_animation) {
        case NEUTRAL:
            #if defined(DEVMODE)
            Serial.print("Animation: ");
            Serial.println("NEUTRAL");
            #endif
            moveServo(0);
            break;
        case LOOKING:
            /* LOOKING
            *  Here the robot is moving the eye left and right
            *  Internal petals are closed
            *  External petals are open
            */
            #if defined(DEVMODE)
            Serial.print("Animation: ");
            Serial.println("LOOKING");
            #endif
            moveServo(20);
            if(millis() - initial_animation_time > LOOKING_TIME_OUT){
              moveServo(0);
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
            #if defined(DEVMODE)
            Serial.print("Animation: ");
            Serial.println("JOY");
            #endif

            if( first_animation_state){
              first_animation_state = false;
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
              showEyeAnimation(JOY);
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
        case SADNESS:
            /* SADNESS
            * Open and semi-close petals very slowly
            * Eye with sad patterns
            * Make sound from a set of sad sounds
            * Sphere of blue colors
            */
            #if defined(DEVMODE)
            Serial.print("Animation: ");
            Serial.println("SADNESS");
            #endif

            if(first_animation_state){
              first_animation_state = false;
              moveServo(30);
              colorSadness();
              playAudio(SADNESS);
              if(millis() - initial_animation_time > SAD_SERVO_TIME_OUT){
                moveServo(0);
                long newTime = millis();
                if(millis() - newTime > SAD_SERVO_TIME_OUT){
                  moveServo(45);
                  showEyeAnimation(SADNESS);                  
                }
              }

              if(millis() - initial_animation_time > SAD_ANIM_TIME_OUT){
                moveServo(0);
              }
              
            }
            break;
        case FEAR:
            /* FEAR
            * Closed and semi-open petals: internal petals closed and 
            * external open; all petals closed
            * Eye with fear patterns
            * Make sound from a set of fear sounds
            * Sphere of violet colors
            */
            #if defined(DEVMODE)
            Serial.print("Animation: ");
            Serial.println("FEAR");
            #endif
            if(first_animation_state){
              first_animation_state = false;
              colorFear();
              moveServo(0);
              if(millis() - initial_animation_time > FEAR_SERVO_TIME_OUT){
                moveServo(60);
                 showEyeAnimation(FEAR); 
              }
            } 
            break;
        case DISGUST:
            /* DISGUST
            *  Open and semi-closed petals
            *  Eye with disgust patterns
            *  Make sound from a set of disgust sounds
            *  Sphere of green colors
            */
            #if defined(DEVMODE)
            Serial.print("Animation: ");
            Serial.println("DISGUST");
            #endif 

            if(first_animation_state){
              first_animation_state = false;
              
              moveServo(0);
              if(millis() - initial_animation_time > DISGUST_SERVO_TIME_OUT){
                moveServo(60);
                 colorDisgust();
                showEyeAnimation(DISGUST);
              }             
            }                 
            break;
        default:
            break;
    }
}

void setupAnimation(){
    initial_animation_time = millis();
    current_animation = LOOKING;
}

