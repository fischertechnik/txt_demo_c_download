

# Project TxtDemo03_Input12ExtM12 ReadMe

## Version

> Version for TXT firmware 4.6.6 4.7.0 pre-release
 

## TxtDemo03_Input12ExtM12
[See also the project Readme](./TxtDemo03_Input12ExtM12/README.md)

The demo program shows the initialization of the universal inputs and then requests them for 10 seconds. If the key is pressed, the M1 motor is switched on. The measured distance value of the ultrasonic sensor controls the M2 motor in the 0..100 cm area with a proportional speed. The program automatically ends after 10 seconds.

- Master TXT:
> - Input I1	key
> - Input I2	Ultrasonic sensor (if present)
> - Output M1	Light or motor
> - Output M2	Light or motor

- Extension TXT (Connect Extension only if a second TXT is present.):
> - Input I1	key
> - Input I2	Ultrasonic sensor (if present)
> - Output M1	Light or motor
> - Output M2	Light or motor


## Setting up my developers tools
 [Setting up my developments environment]( ../../WhichToolsYouNeed.md)

## How to upload programs to the TXT controller
- [With the fischertechnik TXT web interface](../../HowToUseTxtWeb.md)
- [With SFTP tool, for example FileZilla](../../HowToUseTxtWeb.md) 

# document history
- 2020-05-26 CvL 466.1.1 new<br/>
  Parts are copy from the original README.md