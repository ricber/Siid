// #### ANIMATIONS ####
enum Animation_enum {NO_ANIM, LOOKING, EXCITEMENT, JOY, ANGER, SADNESS, FEAR, DISGUST}; // all possible animations of the robot

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
    case NO_ANIM:
        break;
    case LOOKING:
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
