/*
  RS-485 Sender

  This sketch periodically sends a string over the RS-485 interface

  Circuit:
   - MKR board
   - MKR 485 shield
     - ISO GND connected to GND of the RS-485 device
     - Y connected to A of the RS-485 device
     - Z connected to B of the RS-485 device
     - Jumper positions
       - FULL set to ON
       - Z \/\/ Y set to ON

  created 4 July 2018
  by Sandeep Mistry
*/

#include <ArduinoRS485.h>

int counter = 0;

RS485 rs485(Serial2, 16, 17, NOT_A_PIN, NOT_A_PIN);

void setup() {
  rs485.begin(9600);
}

void loop() {
  rs485.beginTransmission();
  rs485.print("hello ");
  rs485.println(counter);
  rs485.endTransmission();

  counter++;

  delay(1000);
}
