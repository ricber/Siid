/* Utilisation du capteur Ultrason HC-SR04 */

// définition des broches utilisées
int  trig = 12;
int  echo = 11;
long lecture_echo;


// Constant
int DELAY_VIT_CALCULATION = 500;
// Variables
int distprec = 0; // precedent distance
int dist     = 0; // distance calculée
int vit      = 0; // velocity of the approching object
int count    = 0; // counter

void
setup()
{
    pinMode(trig, OUTPUT);
    digitalWrite(trig, LOW);
    pinMode(echo, INPUT);
    Serial.begin(9600);
}

void
loop()
{
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    lecture_echo = pulseIn(echo, HIGH); // lecture of the sensor
    distprec =
        lecture_echo / 58; // calculation of the distance from the signal input
    Serial.print("distprec :");
    Serial.print(distprec);
    delay(DELAY_VIT_CALCULATION);
    if (distprec < 500) // if it is at less than 5m
    {
        digitalWrite(trig, HIGH);
        delayMicroseconds(10);
        digitalWrite(trig, LOW);
        lecture_echo = pulseIn(echo, HIGH); // lecture of the sensor
        dist         = lecture_echo
               / 58; // calculation of the distance from the signal input
        Serial.print("    dist :");
        Serial.println(dist);
        if ((dist < distprec) && (abs(distprec - dist) < 200))
        {
            vit = (distprec - dist) / 0.2; // calcul of the approaching velocity
            Serial.print("Vitesse en cm/s : ");
            Serial.println(vit);
            if (vit >= 80) // he is afraid
            {
                Serial.print("Haa");
                while (count < 200) // 200*25=5000ms=5s We are making it scream
                {
                    while (count < 100)
                    {
                        Serial.print("a");
                        count++;
                        delay(25);
                    }
                    Serial.println("a");
                    while (count < 200)
                    {
                        Serial.print("a");
                        count++;
                        delay(25);
                    }
                }
                Serial.println(" !!!");
                Serial.println("");
                count = 0;
            }
            else
            {
                Serial.println("Sono felice");
                Serial.println(" ");
            }
        }
    }
}
