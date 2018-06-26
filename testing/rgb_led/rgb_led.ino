// pin a cui collegare i piedini del LED RGB  
const int GREEN = 9 ;  
const int BLU = 12;  
const int RED = 8;  
  
// tempo di transizione colore  
const int delayTime = 20;  
  
void setup() {  
  
  // imposta il pin digitale come output  
  pinMode(GREEN, OUTPUT);  
  pinMode(BLU, OUTPUT);  
  pinMode(RED, OUTPUT);  
  
  
  // si impostano ad HIGH i pin VERDE, BLU, ROSSO  
  // inizialmente il led RGB sarà spento  
  digitalWrite(GREEN, HIGH);  
  digitalWrite(BLU, HIGH);  
  digitalWrite(RED, HIGH);  
}  
  
// definizione di variabili globali  
int ValVerde;  
  
void loop() {  
  // spegnimento graduale del verde  
  
  // coordinate RGB del rosso: 0, 255, 0  
  
  ValVerde = 255;  
  
  for( int i = 0 ; i < 255 ; i += 1 ){  
  
    ValVerde -= 1;  
  
    /* ad ogni ciclio la differenza 
     255 - ValVerde AUMENTA 
     provocando un graduale spegnimento del verde 
     */  
  
    analogWrite( GREEN, 255 - ValVerde );  
  
    // attesa di 20 ms per percepire il colore  
    delay( delayTime );  
  }  
}  


