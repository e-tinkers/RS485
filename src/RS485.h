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

#ifndef _RS485_H_INCLUDED
#define _RS485_H_INCLUDED

#include <Arduino.h>

// #ifndef SERIAL_PORT_HARDWARE
// #define SERIAL_PORT_HARDWARE Serial
// #endif

// #ifdef PIN_SERIAL1_TX
// #define RS485_DEFAULT_TX_PIN PIN_SERIAL1_TX
// #else
// #define RS485_DEFAULT_TX_PIN 1
// #endif

#ifdef __AVR__
#define RS485_DEFAULT_DE_PIN 2
#define RS485_DEFAULT_RE_PIN NOT_A_PIN
#elif ARDUINO_NANO_RP2040_CONNECT
#define RS485_DEFAULT_DE_PIN A1
#define RS485_DEFAULT_RE_PIN A0
#else
#define RS485_DEFAULT_DE_PIN NOT_A_PIN
#define RS485_DEFAULT_RE_PIN NOT_A_PIN
#endif

#if defined(ESP8266)
#define RS485_SER_CONFIG_T SerialConfig
#elif defined(ESP32)
#define RS485_SER_CONFIG_T uint32_t
#else
#define RS485_SER_CONFIG_T uint16_t
#endif

#define RS485_DEFAULT_PRE_DELAY 50
#define RS485_DEFAULT_POST_DELAY 50

class RS485 : public Stream {
  public:
    RS485(HardwareSerial& hwSerial, int txPin, int dePin, int rePin);

    virtual void begin(unsigned long baudrate);
    virtual void begin(unsigned long baudrate, RS485_SER_CONFIG_T config);
    virtual void begin(unsigned long baudrate, int predelay, int postdelay);
    virtual void begin(unsigned long baudrate, RS485_SER_CONFIG_T config, int predelay, int postdelay);
    virtual void end();
    virtual int available();
    virtual int peek();
    virtual int read(void);
    virtual void flush();
    virtual size_t write(uint8_t b);
    using Print::write; // pull in write(str) and write(buf, size) from Print
    virtual operator bool();

    void beginTransmission();
    void endTransmission();

    void setDelays(int predelay, int postdelay);

  private:
    HardwareSerial* _serial;
    int _txPin;
    int _dePin;
    int _rePin;
    int _predelay = RS485_DEFAULT_PRE_DELAY;
    int _postdelay = RS485_DEFAULT_POST_DELAY;

    bool _transmisionBegun;
    unsigned long _baudrate;
    RS485_SER_CONFIG_T _config;
};

#endif
