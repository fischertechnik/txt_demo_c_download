

# Project TxtDemo05_DbcCallbackInput1M1 ReadMe

## Version

> Version for TXT firmware 4.6.6 or 4.7.0 pre-release
 
## TxtDemo05_DbcCallbackInput1M1
[See also the project Readme](./TxtDemo05_DbcCallbackInput1M1/README.md)

The demo program shows the use of CallBack routine. As long as this function is set up, it is called up during the data exchange with the hardware after the inputs are read in and the output information is output. 

The CallBack routine should not need a lot of time so that the timing is not affected. During the routine, the key - in order to show it as an example - is debounced and the motor is then switched depending on the input.

The program ends after the key is pressed 10 times at the I1 input.

- Master TXT:
> - Input I1	key

> - Output M1	Light or motor

## How to upload programs to the TXT controller
- [With the fischertechnik TXT web interface](../../HowToUseTxtWeb.md)

# document history
- 2020-05-26 CvL 466.1.1 new<br/>
  Parts are copy from the original README.md