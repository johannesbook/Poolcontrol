/*
 * joh@nnes.se 2016
 * Simple hack to control pool heating (and a few extras)
 * Works together witih a secondary Arduino, controlling the relays and measuring power and energy
 * 
 */

 /*
  * TODO:
  * Testa utesensorer (flera)
  * knappar + flytt mellan skärmar
  * relä + timräknare + effektmätare + energiräknare
  * inställning av gränstemp
  * väderprognos
  */

const int minIndoorTemp = 3; //Temp when the indoor heater fan should turn on
const int minOutdoorTempForBath = 19; //temp when the pool heater should turn on

#define DS3231_I2C_ADDRESS 0x68

#include <DHT.h>
#include <openGLCD.h>
#include <include/openGLCD_GLCDv3.h> // GLCDv3 compatibilty mode
#include "fonts/allFonts.h"        
#include "Wire.h"


DHT dht;
float indoorTemp = 88;
float outdoorTemp = 88;
int indoorHumidity = 88;
int screen = 1; //state machine holding screen state. 
                // 0 = main 
                // 1 = sensor info
                // 2 = relay info
bool indoorHeaterRelay = false;
bool poolHeaterRelay = false;
String systemStatus = "Today is a good day.";
byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
                

void setup()
{
  Serial.begin(115200); //initialize serial port
  Wire.begin();         //initialize I2C library
  dht.setup(2);         //initialize indoor temp/humidity sensor on pin 2
  GLCD.Init();          //initialize LCD driver library

  //Set clock: DS3231 seconds, minutes, hours, day, date, month, year
  // - onlh needed when battery has run out
  //setDS3231time(0,10,12,6,18,8,16);
}

void loop() //this routine loops approximately every second
{
  //  ----------------------------
  //  Read temp & humidity sensors 
  //  ----------------------------
  indoorTemp = dht.getTemperature();
  indoorHumidity = dht.getHumidity();
  outdoorTemp = 17.4;  /*todo: read outdoor sensor too*/

  //  ----------------------------
  //  Read time from clock module
  //  ----------------------------
  readDS3231time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year); 
  
  //  --------------------------------------------
  //  Check if indoor temp is too low - start fan? 
  // --------------------------------------------

  if (indoorTemp <= minIndoorTemp) {
    indoorHeaterRelay = true; 
  } 
  if (indoorTemp > minIndoorTemp + 2) {  // 2 degrees hysteresis 
    indoorHeaterRelay = false;
  }
  
  //  -------------------------------------------
  //  Check swimming weather - start pool heater? 
  //  -------------------------------------------
  if ( (hour == 10) and (minute = 0) and (second = 0) ) {  //make this check at 10.00 
    if (outdoorTemp > minOutdoorTempForBath) {
      poolHeaterRelay = true;
      systemStatus = "Pool heater on";
    }
  }
  if ( (hour == 18) and (minute = 0) and (second = 0) ) {
    poolHeaterRelay = false; //always turn off heater at 18.00
    systemStatus = "Pool heater off";
  }

  //  ----------------------------
  //  Update relays
  //  ----------------------------
  //todo - send I2C commands to relay-arduino
  
  //  ----------------------------
  //  Update display
  //  ----------------------------
  drawScreen(screen); //update display

  //  ----------------------------
  //  Read buttons
  //  ----------------------------
  //todo
  
  delay(1000); // wait a second, no need to do this too often

}

