/*
  RS-485 Receiver

  This sketch receives data over RS-485 interface and outputs the data to the Serial interface

  Circuit:
   - MKR board
   - MKR 485 shield
     - ISO GND connected to GND of the RS-485 device
     - A connected to A/Y of the RS-485 device
     - B connected to B/Z of the RS-485 device
     - Jumper positions
       - FULL set to ON
       - A \/\/ B set to OFF

  created 4 July 2018
  by Sandeep Mistry
*/

#include <ArduinoRS485.h>

RS485 rs485(Serial2, 16, 17, NOT_A_PIN, NOT_A_PIN);

void setup() {
  Serial.begin(9600);
  while (!Serial);

  rs485.begin(9600);
  rs485.receiveMode();
}

void loop() {
  if (rs485.available()) {
    Serial.write(rs485.read());
  }
}
