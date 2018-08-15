# ft-TXT-download-examples

Introduction - TXT programming 
The fischertechnik TXT controller has an (embedded) Linux system that allows communication via WLAN, Bluetooth or USB interface. 
The network protocol is used for control by means of interfaces and the TXT can thus be directly activated via IP addresses. 

In the previous Robo interface, it was important to know whether the interface was connected to the computer via the serial interface or the USB interface and the programming varied accordingly.
In TXT, this differentiation has been done away with using the network protocol. Every interface of the TXT (USB, BT, WLAN) has a separate IP address. This makes the different programs more convenient and only the desired IP address must be used.

The sensors and actuators of the fischertechnik TXT controller can be controlled in two ways:

-	Online programming:
Here, a computer can control a controller via the USB cable, WLAN or Bluetooth (BT). The documentation can be found in 
TXT-C programming expert kit (English) on the fischertechnik website.

-	Download programming:
Here, a program is created in a Linux environment and transferred to the TXT, and it can be started there via the menu system. This documentation shows how a virtual machine can be installed on a Windows computer and how Linux can be used there to then cre-ate download programs for the TXT.
