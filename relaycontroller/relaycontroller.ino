/*
 * joh@nnes.se 2016
 * Simple hack to control pool heating (and a few extras)
 * Works together witih a first Arduino, with the UI and other sensors
 */

 /*
  * TODO:
  * Test current measurement and calculate power usage. Calibrate. 
  * Count used hours, used power
  * Store data to eeprom
  * Get I2C-link to work
  * Develop some nice I2C protocol
  */

#include "Wire.h"

void setup()
{
  //Serial.begin(115200); //initialize serial port
  //Wire.begin();         //initialize I2C library
  pinMode(3,OUTPUT);
  digitalWrite(3,HIGH);   //Relay off from start
  Serial.begin(115200);
}

void loop() 
{
  /*
  digitalWrite(3,HIGH);
  delay(1000);
  digitalWrite(3,LOW); //relay on
  delay(2000);
  */
  
  // ******************
  // React on instructions from control panel
  // ******************

  // ******************
  // Measure power
  // ******************
  measurePower();

  // ******************
  // Store power-data to eeprom
  // ******************
  // How many hours did all outputs do today
  // How many hours did all outputs run (> 50W) since start
  // How much power did all outputs use since start (resettable) 
  
}

//ISR to fetch I2C communication? Or polled?
