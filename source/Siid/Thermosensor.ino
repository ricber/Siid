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
#define ERR_TEMP 2

// #### TIME ####


Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setupThermoSensor() {
    #if defined(DEVMODE)
        Serial.println("Thermosensor SETUP begin"); 
    #endif
    mlx.begin(); 
}

boolean thermosensor() {
    float ambientTemp = mlx.readAmbientTempC();
    float objectTemp = mlx.readObjectTempC();

    #if defined(DEVMODE)
        Serial.print("Ambient = "); 
        Serial.print(mlx.readAmbientTempC()); 
        Serial.print("*C\tObject = "); 
        Serial.print(mlx.readObjectTempC()); 
        Serial.println("*C");
    #endif

   if(objectTemp >= ambientTemp + ERR_TEMP){
        //There is a hand that is really near the sphere of the robot
        #if defined(DEVMODE)
            Serial.print("Thermo State: ");
            Serial.println("VERY_NEAR_TEMPERATURE");
        #endif 
        return true;
    }
    return false;    
  }
