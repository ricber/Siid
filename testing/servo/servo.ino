#include <Servo.h>

Servo myservo; // create servo object to control a servo


void setup()
{
    Serial.begin(115200);
    myservo.attach(22); // attaches the servo on pin 9 to the servo object
}

void loop()
{
    for (int i = 85; i > 30; i--){
        myservo.write(i);
        delay(200); // waits for the servo to get there
        Serial.println(i);
    }    
}
