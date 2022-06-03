# RS485 library for Arduino framework

The RS485 library enables you to send and receive data using the RS-485 standard with any RS485 - UART communication module or Arduino&reg; RS485 Shields.

This library supports the [MAX13487E](https://datasheets.maximintegrated.com/en/ds/MAX13487E-MAX13488E.pdf), [MAX3485](https://datasheets.maximintegrated.com/en/ds/MAX3483-MAX3491.pdf), [MAX3157](https://datasheets.maximintegrated.com/en/ds/MAX3157.pdf) and equivalent chipsets.

## ArduinoRS485 versus this RS485 Library
This library is based on the [ArduinoRS485](https://github.com/arduino-libraries/ArduinoRS485), the ArduinoRS485 was originally developed for Arduino RS485 Shields and Arudino SA. MKR series of Arduino boards. It is therefoere doesn't works for MCUs like ESP8266 and ESP32 and likely other non-AVR MCUs. This version of RS485:
- Adds supports for ESP8266/ESP32.
- Add a Class construction and several `begin()` overloaded function for providing the flexibility in supporting other MCUs and configuration requirements.
- Made corrections on some minor mistakes in the ArduinoRS485.
- Remove a couple of useless methods from the RS485 Class.

I decided to setup this library instead of submitting the changes as a pull request to the original ArduinoRS485 because it seems that it take quite long (no release since Aug 2021) for Arduino SA. to roll out a minor release.

## Library API

**RS485**(HardwareSerial& hwSerial, int txPin, int rxPin, int dePin, int rePin)

void **begin**(unsigned long baudrate)

Initializes the RS485 instance's communication speed. For those chips or modules that provide DE(Driver Enable) and RE(Receiver Enable) pins, both pins will be set as `OUTPUT` pin, and DE is set to `LOW`, and RE is set to `HIGH`. That is, the RS485 is set to transmission mode.

void **begin**(unsigned long baudrate, RS485_SER_CONFIG_T config)

In addition to intializes the RS485 instance with specified speed, it allows to pass in a configuration parameter such as `SERIAL_8N1` or `SERIAL_8E1`, etc. The `RS485_SER_CONFIG_T` is an Arduino Core-dependent data type, as various Arduino Core defined the configuration parameter data type differently.

void **begin**(unsigned long baudrate, int predelay, int postdelay)

For those chips or modules that provide DE pin, the `predelay` value define the microsecond delay _after_ the DE pin is set from LOW to HIGH prior data transmission begin. The `postdelay` value refer to the delay in microseconds _before_ the DE pin is reset to LOW at the end of transmission.

By default, both the `predelay` and `postdelay` is set to a constant defined by `RS485_DEFAULT_PRE_DELAY` and `RS485_DEFAULT_POST_DELAY`, both are set to 50 microseconds.

void **begin**(unsigned long baudrate, RS485_SER_CONFIG_T config, int predelay, int postdelay)

All `begin()` overloaded functions call this function one way or another, for example, `begin(baud_rate)` will be calling this function with the default paramters as `begin(baud_rate, SERIAL_8N1, RS485_DEFAULT_PRE_DELAY, RS485_DEFAULT_POST_DELAY )`.

void **end**()

Disables RS485 communication. For those chips/modules with DE and RE pins, both pins will be set to `LOW` and as `INPUT` (i.e. tri-state to allows other RS845 devices in the bus to be able to communicate).

int **available**()

This function is inherited from [Stream](https://www.arduino.cc/reference/en/language/functions/communication/stream/streamavailable/) object. The `available()` return the number of bytes received so far in the serial receive buffer upon to the call of this function.


int **peek**()

Refer to the [`Stream.peek()`](https://www.arduino.cc/reference/en/language/functions/communication/stream/streampeek/) for the description.

int **read**(void)

Refer to the [`Stream.read()`](https://www.arduino.cc/reference/en/language/functions/communication/stream/streamread/) for the description.

void **flush**()

Refer to the [`Stream.flush()`](https://www.arduino.cc/reference/en/language/functions/communication/stream/streamflush/) for the description.

size_t **write**(uint8_t b)

size_t **write**(const char* str)

size_t **write**(const uint8_t* buf, size_t size)

Writes data byte to the RS485 port. All the `write()` are inheritated from Arduino Print class.

void **beginTransmission**()

Signify the begin of a data transmission. The DE pin will be set to `HIGH` with the appropriate delay according to the `predelay` value (see `void begin(unsigned long baudrate, int predelay, int postdelay)`).

void **endTransmission**()

Signify the end of a data transmission session. The DE pin will be reset to `LOW` after a `postdelay` in microseconds.

void **sendBreak**(unsigned int duration)

This function will end the eixsting RS485 communication (after flushing out of the data), it then genearate a BREAk condition by pulling down the `txPin` for a few milliseconds based on the `duration` value, it then re-establish an RS485 communication by calling the `begin(baud_rate, config)`.

void **sendBreakMicroseconds**(unsigned int duration)

This function does the same as `sendBreak()` function, except the `duration` is in microseconds instead of milliseconds.
