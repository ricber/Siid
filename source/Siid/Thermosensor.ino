/*************************************************** 
  This is a library example for the MLX90614 Temp Sensor

  Designed specifically to work with the MLX90614 sensors in the
  adafruit shop
  ----> https://www.adafruit.com/products/1748
  ----> https://www.adafruit.com/products/1749
  These sensors use I2C to communicate, 2 pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include <Adafruit_MLX90614.h>


/**
 * Temperature to be ignored: >= 45 °C
 * Relevant Temperature (near): >= 29.5°C and <45°C
 * Body presence (not so near): >=27°C and <29.5°C
 */
#define MAX_TEMP 45
#define VERY_NEAR_TEMP 29.5

// #### TIME ####
unsigned long last_measurement_time_thermo; // state beginning execution time

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setupThermoSensor() {
    /*
    #if defined(DEVMODE)
        Serial.println("Thermosensor SETUP begin"); 
    #endif
    mlx.begin();  
    */
}

void front_thermo() {
    /*
  if (millis() - last_measurement_time_thermo >= MSRMNT_TIME_OUT){
    //read the temperature
    float ambientTemp = mlx.readAmbientTempC();
    float objectTemp = mlx.readObjectTempC();
    last_measurement_time_thermo = millis();
    
    #if defined(DEVMODE)
    Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC()); 
    Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
     #endif

   if(objectTemp >= VERY_NEAR_TEMP && objectTemp < MAX_TEMP){
      //There is a hand that is really near the sphere of the robot
       #if defined(DEVMODE)
           Serial.print("Thermo State: ");
           Serial.println("VERY_NEAR_TEMPERATURE");
      #endif      
      float actualObjTemp = mlx.readObjectTempC(); 
           
      if (mlx.readObjectTempC() - objectTemp >= 1.5){
        //the changement of temperature was SLOW -> HAPPY REACTION
        setState(RANDOM_ANIMATION);
      }else{
        //the changement of temperature was FAST -> FEAR REACTION
         setState(FEAR_STATE);
      }
    }
  }
   */
}
