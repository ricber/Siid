/* Utilisation du capteur Ultrason HC-SR04 */

// définition des broches utilisées
int trig = 12;
int echo = 11;
long lecture_echo;


//Constant
int DELAY_VIT_CALCULATION=200;
//Variables
int distprec=0;//precedent distance
int dist=0;//distance calculée
int vit=0; //velocity of the approching object
int count=0; // counter

void setup()
{
  pinMode(trig, OUTPUT);
  digitalWrite(trig, LOW);
  pinMode(echo, INPUT);
  Serial.begin(9600);
}

void loop()
{
  distprec=dist; // we save the precedent distance in order to calculate the velocity bellow
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  lecture_echo = pulseIn(echo, HIGH);// lecture of the sensor
  dist = lecture_echo / 58; //calculation of the distance from the signal input
  
  if ((abs(distprec-dist)<200)&&(dist<2000)) // 200 is a value we have to set uo !!!!
     { 
      Serial.print("Distance en cm : ");
      Serial.println(dist);
      vit=(distprec-dist)/(DELAY_VIT_CALCULATION/1000); // calcul of the approaching velocity
      Serial.print("Vitesse en cm/s : ");
      Serial.println(vit);
      if (vit>=50) //he is afraid
        { Serial.print ("Haa");
          while (count<200) // 200*25=5000ms=5s We are making it scream
            {
             while(count<100)
               {
                 Serial.print ("a");
                 count++;
                 delay(25); 
               }
             Serial.println("a");
             while(count<200)
               {
                 Serial.print ("a");
                 count++;
                 delay(25); 
               }
             }
          Serial.println(" !!!");
          Serial.println("");
          count=0;
        }
      else
        {
          Serial.println ("Sono felice");
          Serial.println (" ");
        }
     }
   
  delay(DELAY_VIT_CALCULATION);
}
