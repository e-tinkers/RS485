# RS485 library for Arduino framework

The RS485 library enables you to send and receive data using the RS-485 standard with any RS485 - UART communication module or Arduino&reg; RS485 Shields.

This library supports the [MAX13487E](https://datasheets.maximintegrated.com/en/ds/MAX13487E-MAX13488E.pdf), [MAX3485](https://datasheets.maximintegrated.com/en/ds/MAX3483-MAX3491.pdf), MAX3157 and equivalent chipsets.

## ArduinoRS485 versus this RS485 Library
This library is based on the [ArduinoRS485](https://github.com/arduino-libraries/ArduinoRS485), the ArduinoRS485 was originally developed for Arduino RS485 Shields and Arudino SA. MKR series of Arduino boards. It is therefoere doesn't works for MCUs like ESP8266 and ESP32 and likely other non-AVR MCUs. This version of RS485:
- Adds supports for ESP8266/ESP32.
- Add a Class construction and several `begin()` overloaded function for providing the flexibility in supporting other MCUs and configuration requirements.
- Made corrections on some minor mistakes in the ArduinoRS485.
- Remove a couple of useless methods from the RS485 Class.

I decided to setup this library instead of submitting the changes as a pull request to the original ArduinoRS485 because it seems that it take quite long (no release since Aug 2021) for Arduino SA. to roll out a minor release.

## Library API

To be provided later.
