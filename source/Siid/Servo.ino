#include <Servo.h>

Servo myservo; // create servo object to control a servo

void setupServo()
{
    myservo.attach(9); // attaches the servo on pin 9 to the servo object
    Serial.begin(9600);
}

void moveServo(byte angle, byte waitTime)
{    
    myservo.write(angle); // sets the servo position according to the scaled value
    delay(waitTime); // waits for the servo to get there
}
