// #### ANIMATIONS ####
enum Animation_enum {NEUTRAL, JOY, ANGER, SADNESS, FEAR, DISGUST, LOOKING, EXCITEMENT,}; // all possible animations of the robot

byte current_animation = LOOKING; // current state of the robot

void setAnimation(byte animation) {
    current_animation = animation;
    #if defined(DEVMODE)
        Serial.print("Animation: ");
        Serial.println(animation);
    #endif
}

void playAnimation() {
    switch (current_animation) {
    case NEUTRAL:
        break;
    case LOOKING:
        /* LOOKING
         *  Here the robot is moving the eye left and right
         *  Internal petals are closed
         *  External petals are open
         */
        break;
    case EXCITEMENT:
        /* LOOKING
         *  Here the robot is moving the eye left and right
         *  Internal petals are closed
         *  External petals are open
         */
        break;
    case JOY:
        /* LOOKING
         *  Here the robot is moving the eye left and right
         *  Internal petals are closed
         *  External petals are open
         */
     break;
    case ANGER:
        /* LOOKING
         *  Here the robot is moving the eye left and right
         *  Internal petals are closed
         *  External petals are open
         */
     break;
     case SADNESS:
        /* LOOKING
         *  Here the robot is moving the eye left and right
         *  Internal petals are closed
         *  External petals are open
         */
     break;
     case FEAR:
        /* LOOKING
         *  Here the robot is moving the eye left and right
         *  Internal petals are closed
         *  External petals are open
         */
     break;
     case DISGUST:
        /* LOOKING
         *  Here the robot is moving the eye left and right
         *  Internal petals are closed
         *  External petals are open
         */
     break;
    default:
        break;
    }
}
