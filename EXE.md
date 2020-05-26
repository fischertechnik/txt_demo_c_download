# Content
<!-- TOC depthFrom:1 depthTo:6 withLinks:1 updateOnSave:1 orderedList:0 -->

- [Content](#content)
- [What is a fischertechnik executable?](#what-is-a-fischertechnik-executable)
	- [Introduction](#introduction)
	- [TXT Programming](#txt-programming)
- [document history](#document-history)

<!-- /TOC -->
[Back to main content overview](/README.md#overview)

# What is a fischertechnik executable?
## Introduction
From the perspective of RoboPro an SLI is a functional unit. RoboPro can send data to a SLI and can get data back from the SLI. But RoboPro can also start and stop more complex activities in a SLI, for example dedicated websocket or MQTT based communication with the outside world, image processing, I2C drivers, more complex closed control loops, etc.<br/>
The fischertechnik TXT SLI makes it possible that C/C++ functions can be access via a RoboPro elements.
For this RoboPro knows 2 elements, the `Shared library Input` element and the `Shared library Output` element. 

The shared library `input/output element` allows to call functions and return/supply a value from/to shared library modules installed on the TXT controller. 
Such libraries are typically written in the C or C++ programming language. 
This allows interfacing ROBOPro with C / C++ programs, which is useful for accessing advanced sensors or for compute intensive tasks like image processing
## TXT Programming

The fischertechnik TXT controller has an (embedded) Linux system that allows communication via WLAN, Bluetooth or USB interface. 
The network protocol is used for control by means of interfaces and the TXT can thus be directly activated via IP addresses. 

In the previous Robo interface, it was important to know whether the interface was connected to the computer via the serial interface or the USB interface and the programming varied accordingly.
In TXT, this differentiation has been done away with using the network protocol. Every interface of the TXT (USB, BT, WLAN) has a separate IP address. This makes the different programs more convenient and only the desired IP address must be used.

The sensors and actuators of the fischertechnik TXT controller can be controlled in two ways:

- **Online programming**
Here, a computer can control a controller via the USB cable, WLAN or Bluetooth (BT). The documentation can be found in 
[txt_demo_c_online](https://github.com/fischertechnik/txt_demo_c_online).

- **Download programming**
Here, a program is created with a cross compiler and transferred to the TXT, and it can be started there via the menu system. This documentation shows how an Eclipse development environment can be used to create C download programs for the TXT. You can also use other IDE, e. g. Visual Studio or CodeLite.`




# document history
- 2020-05-26 CvL 466.1.1 new<br/>
  Parts are copy from the original README.md
