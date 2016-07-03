--------------------------------------------------------------------------
READMEFILE of the Arduino_datagram_example of Broentech Solutions A.S.
--------------------------------------------------------------------------
This is a draft on how to use Arduino Board as example of IoT fog device. It can be used as starting point for your own device!
It is meant to be used in combination with Broentech Py_Gateway. You can see the sensor data online by using broentech cloud solution TALAIOT.io
read more on www.broentech.no

--------------------------------------------------------------------------
HARDWARE: 
This project show how to read data from pressure sensor BMP085 (Adafruit) and from a analog light sensor and send it over serial port in a broentech datagram format!
   Connections for BMP085 
   ===========
   Connect SCL to analog 5
   Connect SDA to analog 4
   Connect VCC/VDD to 3.3V DC
   Connect GROUND to common ground
   Connect ARef pin to 3.3V
   
   For Light sensor:
   ==================
   Connect the Light-analog-sensor to analog pin A0

--------------------------------------------------------------------------
SOFTWARE:
This code read pressure, temperature and altitude from the Adafruit BMP085 pressure sensor and the lux value from an analog light sensor. It converts the values into broentech datagrams and send it over serial port. The code stops if it fails to initialize the BMP085 sensor!
It is meant to be used in combination with PyGateway from Broentech Solution. This code can be used as starting point for your project. 
The Datagram_structure_example.h show how to construct and send float values as broentech datagram.
