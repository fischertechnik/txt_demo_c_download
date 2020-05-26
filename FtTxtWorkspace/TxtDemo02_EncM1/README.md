

# Project ReadMe

## Version

> Version for TXT firmware 4.6.6 4.7.0 pre-release
 
### TxtDemo00_HelloWorld

The demo program prints "TXT: Hello World!" to cout.

<!---
### TxtDemo01_Input1Print
The demo program prints analog value to cout.
> Master TXT:
> - Input I1: Voltage or color sensor

### TxtDemo02_EncM1
[See also the project Readme](./TxtDemo02_EncM1/README.md)

The demo program shows the distance operation of the encoder motor. It is recommended that you plug a rest gear wheel 137677 to the axle and highlight a wheel. The program switches the motor for 2 rotations, then waits for a second and carries out the same number of rotations in the opposite direction. Then the program ends.
> Master TXT:
> - Output M1	Encoder motor
> - Input C1	Counter signal of the encoder motor

### TxtDemo03_Input12ExtM12
[See also the project Readme](./TxtDemo03_Input12ExtM12/README.md)

The demo program shows the initialisation of the universal inputs and then requests them for 10 seconds. If the key is pressed, the M1 motor is switched on. The measured distance value of the ultrasonic sensor controls the M2 motor in the 0..100 cm area with a proportional speed. The program automatically ends after 10 seconds.

> Master TXT:
> - Input I1	key
> - Input I2	Ultrasonic sensor (if present)
> - Output M1	Light or motor
> - Output M2	Light or motor

> Extension TXT (Connect Extension only if a second TXT is present.):
> - Input I1	key
> - Input I2	Ultrasonic sensor (if present)
> - Output M1	Light or motor
> - Output M2	Light or motor

### TxtDemo04_DbcCallback_I2C
[See also the project Readme](./TxtDemo04_DbcCallback_I2C/README.md)

This example shows the data output at the I2C bus.
The I2C unit must first be initialised, and the I2C function can then be used to write the desired number of bytes and then read in the response.

> Master TXT:
> - I1: Switch
> - I2C: PCF8574 with LED's on the Outputs

### TxtDemo05_DbcCallbackInput1M1
[See also the project Readme](./TxtDemo05_DbcCallbackInput1M1/README.md)

The demo program shows the use of CallBack routine. As long as this function is set up, it is called up during the data exchange with the hardware after the inputs are read in and the output information is output. 

The CallBack routine should not need a lot of time so that the timing is not affected. During the routine, the key - in order to show it as an example - is debounced and the motor is then switched depending on the input.

The program ends after the key is pressed 10 times at the I1 input.

> Master TXT:
> - Input I1	key
> - Output M1	Light or motor

### TxtDemo06_O1_Blink
[See also the project Readme](./TxtDemo06_O1_Blink/README.md)

### TxtDemo07_Sound
[See also the project Readme](./TxtDemo07_Sound/README.md)

###TxtDemo08_MoveRef
[See also the project Readme](./TxtDemo08_MoveRef/README.md)

### TxtDemo99_BNO055
[See also the project Readme](./TxtDemo99_BNO055/README.md)
-->

## Setting up my developers tools
 [Setting up my developments environment]( ../../WhichToolsYouNeed.md)

## How to upload programs to the TXT controller
- [With the fischertechnik TXT web interface](../../HowToUseTxtWeb.md)
- [With SFTP tool, for example FIleZilla](../../HowToUseTxtWeb.md) 

# document history
- 2020-05-26 CvL 466.1.1 new<br/>
  Parts are copy from the original README.md