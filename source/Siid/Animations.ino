// #### ANIMATIONS ####
enum Animation_enum {NEUTRAL, LOOKING, EXCITEMENT, JOY, ANGER, SADNESS, FEAR, DISGUST}; // all possible animations of the robot

byte current_animation; // current aniamtion of the robot

void setAnimation(byte animation) {
    current_animation = animation;
}

void playAnimation() {
    switch (current_animation) {
        case NEUTRAL:
            #if defined(DEVMODE)
            Serial.print("Animation: ");
            Serial.println("NEUTRAL");
            #endif
            moveServo(0,0);
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
            moveServo(20, 1000);
            moveServo(0, 1000);
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
            moveServo(45, 500);
            moveServo(90, 2000);
            moveServo(0, 500);
            moveServo(60, 200);
            showEyeAnimation(JOY);
            moveServo(80, 200);
            moveServo(60, 200);
            moveServo(80, 200);
            showEyeAnimation(JOY);
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
            moveServo(30, 1000);
            moveServo(0, 1000);
            playAudio(SADNESS);
            moveServo(45, 1000);
            moveServo(0, 1000);
            moveServo(60, 500);
            showEyeAnimation(SADNESS);
            moveServo(0, 0);
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
            colorFear();
            moveServo(0,0);
           showEyeAnimation(FEAR);
            //turn off the sphere
            turnOff(); 
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
            moveServo(0,0);
            moveServo(45, 100);
            colorDisgust();
            showEyeAnimation(DISGUST);
            moveServo(0,0);
            showEyeAnimation(DISGUST);
            //turn off the sphere
            turnOff();         
            break;
        default:
            break;
    }
}

void setupAnimation(){
    current_animation = LOOKING;
}

