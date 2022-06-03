/*
  This library is modified based on ArduinoRS485 for supporting ESP32/ESP8266 in
  addition to original's work which only designed for AVR-based Arduino.

  Modified by: Henry Cheung
  Date:        15 May, 2022

  Copyright (c) 2022 e-tinkers.com. All rights reserved.

  Original Library by Arduino SA. (https://github.com/arduino-libraries/ArduinoRS485)
  Copyright (c) 2018 Arduino SA. All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "RS485.h"

RS485::RS485(HardwareSerial& hwSerial, int txPin, int rxPin, int dePin, int rePin) :
  _serial(&hwSerial),
  _txPin(txPin),
  _rxPin(rxPin),
  _dePin(dePin),
  _rePin(rePin),
  _transmisionBegun(false)
{
}

void RS485::begin(unsigned long baudrate)
{
  begin(baudrate, SERIAL_8N1, RS485_DEFAULT_PRE_DELAY, RS485_DEFAULT_POST_DELAY);
}

void RS485::begin(unsigned long baudrate, int predelay, int postdelay)
{
  begin(baudrate, SERIAL_8N1, predelay, postdelay);
}

void RS485::begin(unsigned long baudrate, RS485_SER_CONFIG_T config)
{
  begin(baudrate, config, RS485_DEFAULT_PRE_DELAY, RS485_DEFAULT_POST_DELAY);
}

void RS485::begin(unsigned long baudrate, RS485_SER_CONFIG_T config, int predelay, int postdelay)
{
  _baudrate = baudrate;
  _config = config;
  _predelay = predelay;
  _postdelay = postdelay;

  if (_dePin > -1) {
    pinMode(_dePin, OUTPUT);
    digitalWrite(_dePin, LOW);
  }

  if (_rePin > -1) {
    pinMode(_rePin, OUTPUT);
    digitalWrite(_rePin, HIGH);
  }

  _transmisionBegun = false;

  _serial->begin(baudrate, config);

}

void RS485::end()
{
  _serial->end();

  if (_rePin > -1) {
    digitalWrite(_rePin, LOW);
    pinMode(_dePin, INPUT);
  }

  if (_dePin > -1) {
    digitalWrite(_dePin, LOW);
    pinMode(_rePin, INPUT);
  }
}

int RS485::available()
{
  return _serial->available();
}

int RS485::peek()
{
  return _serial->peek();
}

int RS485::read(void)
{
  return _serial->read();
}

void RS485::flush()
{
  return _serial->flush();
}

size_t RS485::write(uint8_t b)
{
  if (!_transmisionBegun) {
    setWriteError();
    return 0;
  }

  return _serial->write(b);
}

void RS485::beginTransmission()
{
  if (_dePin > -1) {
    digitalWrite(_dePin, HIGH);
    if (_predelay) delayMicroseconds(_predelay);
  }

  _transmisionBegun = true;
}

void RS485::endTransmission()
{
  _serial->flush();

  if (_dePin > -1) {
    if (_postdelay) delayMicroseconds(_postdelay);
    digitalWrite(_dePin, LOW);
  }

  _transmisionBegun = false;
}

void RS485::sendBreak(unsigned int duration)
{
  _serial->flush();
  _serial->end();
  pinMode(_txPin, OUTPUT);
  digitalWrite(_txPin, LOW);
  delay(duration);
  _serial->begin(_baudrate, _config);
}

void RS485::sendBreakMicroseconds(unsigned int duration)
{
  _serial->flush();
  _serial->end();
  pinMode(_txPin, OUTPUT);
  digitalWrite(_txPin, LOW);
  delayMicroseconds(duration);
  _serial->begin(_baudrate, _config);
}
