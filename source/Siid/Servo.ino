#include <Servo.h>

Servo myservo; // create servo object to control a servo

void setupServo()
{
    myservo.attach(24); // attaches the servo on pin 9 to the servo object
}

void moveServo(byte angle, byte waitTime)
{    
    myservo.write(angle); // sets the servo position according to the scaled value
    //TODO: Add Timer
    delay(waitTime); // waits for the servo to get there
}
