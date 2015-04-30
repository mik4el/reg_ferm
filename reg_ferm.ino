/*************************************************** 
  This is an example for the Adafruit Thermocouple Sensor w/MAX31855K

  Designed specifically to work with the Adafruit Thermocouple Sensor
  ----> https://www.adafruit.com/products/269

  These displays use SPI to communicate, 3 pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <SPI.h>
#include "Adafruit_MAX31855.h"

// Default connection is using software SPI, but comment and uncomment one of
// the two examples below to switch between software SPI and hardware SPI:

// Example creating a thermocouple instance with software SPI on any three
// digital IO pins.
#define DO   12
#define CS1  10
#define CS2  11
#define CS3  9
#define CLK  8

Adafruit_MAX31855 thermocouple1(CLK, CS1, DO);
Adafruit_MAX31855 thermocouple2(CLK, CS2, DO);
Adafruit_MAX31855 thermocouple3(CLK, CS3, DO);

// Example creating a thermocouple instance with hardware SPI (Uno/Mega only)
// on a given CS pin.
//#define CS   11
//Adafruit_MAX31855 thermocouple(CS);

const int R1KYL = 7;
const int R2VARME = 5;
const double intervall = 0.5;


void setup() {
  
  pinMode(R1KYL, OUTPUT);
  pinMode(R2VARME, OUTPUT);
  
  digitalWrite(R1KYL, HIGH);
  digitalWrite(R2VARME, HIGH);

  Serial.begin(9600);
  
  //Serial.println("MAX31855 test");
  // wait for MAX chip to stabilize
  delay(500);
}

void loop() {
  // basic readout test, just print the current temp
  //Serial.print("Internal Temp = ");
  //Serial.println(thermocouple1.readInternal());
   
  double setpoint = 4;
  
  // say what you got:
  Serial.print(setpoint);
  Serial.print(","); 

  double T_fermentor = thermocouple1.readCelsius();
   
  Serial.print(T_fermentor);
  Serial.print(","); 
  
  delay(400);

  double T_isolering = thermocouple2.readCelsius();
   
  Serial.print(T_isolering);
  Serial.print(",");
   
  double T_kylvatten = thermocouple3.readCelsius();
   
  Serial.print(T_kylvatten);
  Serial.print(",");
   
  double T_luft = thermocouple1.readInternal();
  
  Serial.println(T_luft);
   
  // seriella kommunikationen har ordningen (setpoint, T_fermentor, T_isolering, T_kylvatten, T_luft)
  
  delay(1000);
   
  double setpoint_max = setpoint + intervall;
  double setpoint_min = setpoint - intervall;
  
  if (T_fermentor >= setpoint_max) {
    digitalWrite(R1KYL, LOW); 
  } else { 
    digitalWrite(R1KYL, HIGH);
  }
        
  if (T_fermentor <= setpoint_min) {
    digitalWrite(R2VARME, LOW);
  } else { 
    digitalWrite(R2VARME, HIGH);
  }
            
  delay(300000);
}
