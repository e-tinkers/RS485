/*
  RS-485 Passthrough

  This sketch relays data sent and received between the Serial port and the RS-485 interface

  Circuit:
   - MKR board
   - MKR 485 Shield
     - ISO GND connected to GND of the RS-485 device
     - Y connected to A of the RS-485 device
     - Z connected to B of the RS-485 device
     - A connected to Y of the RS-485 device
     - B connected to Z of the RS-485 device
     - Jumper positions
       - FULL set to ON
       - Z \/\/ Y set to ON, if the RS-485 device doesn't provide termination
       - B \/\/ A set to ON, if the RS-485 device doesn't provide termination

  created 4 July 2018
  by Sandeep Mistry
*/

#include <ArduinoRS485.h>

RS485 rs485(Serial2, 16, 17, NOT_A_PIN, NOT_A_PIN);

void setup() {
  Serial.begin(9600);
  rs485.begin(9600);

  // enable transmisson
  rs485.beginTransmission();

  // enable reception
  rs485.receiveMode();
}

void loop() {
  if (Serial.available()) {
    rs485.write(Serial.read());
  }

  if (rs485.available()) {
    Serial.write(rs485.read());
  }
}
