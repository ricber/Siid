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


#define ERR_TEMP 1
float calibrationSum = 0;               // Sum computed during calibration
unsigned int calibrationCounter = 0;    // Samples considered in the mean
float meanTemp;

// #### TIME ####
unsigned long timer_calibration;

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setupThermoSensor() {
    
    mlx.begin();
    
    timer_calibration = millis();    
    // calibration
    while (millis() - timer_calibration < 500){
        calibrateTemperature();        
    }
    meanTemp = calibrationSum / calibrationCounter;
    #if defined(DEVMODE)
        Serial.print("Thermosensor SETUP begin. Mean temperature:"); 
        Serial.println(meanTemp);
    #endif
}

// Compute the calibration data
void calibrateTemperature() {
    // Acquire the temperature and update the sum
    calibrationSum += mlx.readObjectTempC();
    // Increment the counter
    calibrationCounter++;
}

boolean thermosensor() {
    float objectTemp = mlx.readObjectTempC();
    
    if(objectTemp >= meanTemp + ERR_TEMP){
        //There is a hand that is really near the sphere of the robot
        #if defined(DEVMODE)
            Serial.print("Thermo State: HAND DETECTED. Object temperature: ");
            Serial.println(objectTemp);
        #endif 
        return true;
    }
    return false;    
  }
