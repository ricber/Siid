#include <Servo.h>

Servo myservo; // create servo object to control a servo

void setupServo()
{
    myservo.attach(50); // attaches the servo on pin 9 to the servo object
}

void moveServo(byte angle, byte waitTime)
{    
    myservo.write(angle); // sets the servo position according to the scaled value
    delay(waitTime); // waits for the servo to get there
}
