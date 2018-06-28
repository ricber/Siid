#include <Servo.h>

Servo myservo; // create servo object to control a servo


void setup()
{
    myservo.attach(22); // attaches the servo on pin 9 to the servo object
}

void loop()
{
    for (int i = 0; i < 5; i++){
        myservo.write(0);
        delay(2000); // waits for the servo to get there
        myservo.write(85);
        delay(2000);
    }
     // sets the servo position according to the scaled value
    
}
