#include <Servo.h>

Servo myservo; // create servo object to control a servo
#define SERVO_PIN 22

void setupServo()
{
    myservo.attach(SERVO_PIN); // attaches the servo on pin 9 to the servo object
    moveServo(7); //petals closed
    #if defined(DEVMODE)
        Serial.println("SERVO setup");
    #endif
}

void moveServo(byte angle)
{    
    myservo.write(angle); // sets the servo position according to the scaled value
}
