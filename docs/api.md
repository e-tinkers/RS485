# Arduino RS485 library

## Methods

### `begin()`

Initializes the RS485 object communication speed.

#### Syntax

```
RS485.begin(baudrate)
```

#### Parameters

* _baudrate_: communication speed in bits per second (baud).

#### Returns

None.


### `end()`

Disables RS485 communication.

#### Syntax

```
RS485.end()
```

#### Parameters

None.

#### Returns

None.


### `available()`

Get the number of bytes (characters) available for reading from the RS485 port. This is data that already arrived and is stored in the serial receive buffer.

#### Syntax

```
RS485.available()
```

#### Parameters

None.

#### Returns

The number of bytes available to read.


### `peek()`

Returns the next byte (character) of the incoming serial data without removing it from the internal serial buffer. That is, successive calls to peek() will return the same character, as will the next call to read().

#### Syntax

```
RS485.peek()
```

#### Parameters

None.

#### Returns

The first byte of incoming serial data available or -1 if no data is available.

#### See also


### `read()`

Reads incoming serial data.

#### Syntax

```
RS485.read()
```

#### Parameters

None.

#### Returns

The first byte of incoming serial data available or -1 if no data is available.

#### See also


### `write()`

Writes binary data to the serial port. This data is sent as a byte or series of bytes.

#### Syntax

```
RS485.write(uint8_t b)
```

#### Parameters

* _b_: unsigned char.

#### Returns

The number of bytes written.

#### See also


### `flush()`

Waits for the transmission of outgoing serial data to complete.

#### Syntax

```
RS485.flush()
```

#### Parameters

None.

#### Returns

None.

#### See also


### `beginTransmission()`

Enables RS-485 transmission.

#### Syntax

```
RS485.beginTransmission()
```

#### Parameters

None.

#### Returns

None.

#### Example

```
#include <ArduinoRS485.h>

int counter = 0;

void setup() {
  RS485.begin(9600);
}

void loop() {
  RS485.beginTransmission();
  RS485.print("Counter: ");
  RS485.println(counter);
  RS485.endTransmission();

  counter++;

  delay(1000);
}
```


### `endTransmission()`

Disables RS-485 transmission.

#### Syntax

```
RS485.endTransmission()
```

#### Parameters

None.

#### Returns

None.

#### Example

```
#include <ArduinoRS485.h>

int counter = 0;

void setup() {
  RS485.begin(9600);
}

void loop() {
  RS485.beginTransmission();
  RS485.print("Counter: ");
  RS485.println(counter);
  RS485.endTransmission();

  counter++;

  delay(1000);
}
```
