//h+//////////////////////////////////////////////////////////////////////////
/*!
//  \file      Arduino_datagram_example.ino
//
//  \brief     This File Show an example of integration between ARDUINO board and the Broentech PyGateway software.
//             Read data from the BMP085 pressure sensor and send it over the serial port (pressure, temperature and sea level altitude).
//             Read data from the analog light sensor and send it over serial port encoded in as float!
//
//
//  \author    Luca Petricca
//
//  \date      19.06.2015
//
//  \Copyright(c) 2016 BroenTech Solutions AS
//   Permission is hereby granted, free of charge, to any person obtaining a copy of this
//   software and associated documentation files (the "Software"), to deal in the Software
//   without restriction, including without limitation the rights to use, copy, modify, merge,
//   publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons
//   to whom the Software is furnished to do so, subject to the following conditions:
//
//   The above copyright notice and this permission notice shall be included in all copies or substantial
//   portions of the Software.
//
//   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
//   INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
//   AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
//   DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
//  \par       Revision History
//             Released under MIT license
//
//
//    ADAPTED FROM ADAFRUIT EXAMPLE FILE!
//
*/
//h-//////////////////////////////////////////////////////////////////////////

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>
#include "Datagram_structure_example.h"

/* This driver uses the Adafruit unified sensor library (Adafruit_Sensor),
   which provides a common 'type' for sensor data and some helper functions.
   
   To use this driver you will also need to download the Adafruit_Sensor
   library and include it in your libraries folder.

   You should also assign a unique ID to this sensor for use with
   the Adafruit Sensor API so that you can identify this particular
   sensor in any data logs, etc.  To assign a unique ID, simply
   provide an appropriate value in the constructor below (12345
   is used by default in this example).
   
   Connections
   ===========
   Connect SCL to analog 5
   Connect SDA to analog 4
   Connect VCC/VDD to 3.3V DC
   Connect GROUND to common ground
   Connect A0 to light sensor anolog outpur
   Connect ARef pin to 3.3V
    

Also connect the Light analog sensor to analog pin A0
*/
   
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);

char myid[5]     = "$A01"; //id of the board
int sensorPin  = A0;     // select the input pin for the light sensor
float rawRange = 1024;   // 3.3v
float logRange = 5.0;    // 3.3v = 10^5 lux



//Function that convert voltage into lux value for the light sensor!
float RawToLux(int raw)
{
  float logLux = raw * logRange / rawRange;
  return pow(10, logLux);
}

/**************************************************************************/
/*
    Arduino setup function (automatically called at startup)
*/
/**************************************************************************/

void setup(void) 
{
  Serial.begin(9600);     //lets start the serial 
  analogReference(EXTERNAL); 
  
  /* Initialise the pressure sensor */
  if(!bmp.begin())          //initialize the pressure sensor
  {
    /* There was a problem detecting the BMP085 ... check your connections */
    Serial.print("Ooops, no BMP085 detected ... Check your wiring or I2C ADDR!"); //remove this line when you connect it to PyGateway... this is for debug purpose only!

    while(1);   //we stop the execution if we are unable to initialize the sensor
  }
}

/**************************************************************************/
/*
    Arduino loop function, called once 'setup' is complete (your own code
    should go here)
*/
/**************************************************************************/
void loop(void) 
{
  /* Get a new sensor event */ 
  sensors_event_t event;
  bmp.getEvent(&event);
 
  /*Every time there is an pressure event, we sent all the sensor data (pressure, temperature, light, altitude)!*/
    
  if (event.pressure)      
  {
    sendDatagramfloat(myid, "PRES", "P---", event.pressure, 0, 0);      //lets send the datagram with the pressure in hPa
   
    float temperature;
    bmp.getTemperature(&temperature);
    sendDatagramfloat(myid, "TEMP", "C---", temperature, 0, 0 );        //lets send the temperature datagram in celsius degree
    
    int rawValue = analogRead(sensorPin); 
    sendDatagramfloat(myid, "LIGH","L---", RawToLux(rawValue), 0, 0);   //lets send the light value in lux

    float seaLevelPressure = SENSORS_PRESSURE_SEALEVELHPA;  
    sendDatagramfloat(myid, "ALTI", "m---", bmp.pressureToAltitude(seaLevelPressure, event.pressure), 0,0 );  //Lets send the altitute from the sea level
  }
  else
  {
  }
  delay(1000);
}

