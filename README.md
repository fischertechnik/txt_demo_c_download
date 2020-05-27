# Content
<!-- TOC depthFrom:1 depthTo:6 withLinks:1 updateOnSave:1 orderedList:0 -->

- [Content](#content)
- [C/C++ programming for the fischertechnik TXT controller](#cc-programming-for-the-fischertechnik-txt-controller)
	- [Target groups for this information.](#target-groups-for-this-information)
	- [Introduction](#introduction)
	- [About the terms: TXT C/C++ application,  download and uploading?](#about-the-terms-txt-cc-application-download-and-uploading)
	- [The organization of this GitHub repository](#the-organization-of-this-github-repository)
	- [Documentation](#documentation)
		- [For the end-user:](#for-the-end-user)
		- [For the developer:](#for-the-developer)
		- [General](#general)
		- [References](#references)
- [Document history](#document-history)

<!-- /TOC -->
# C/C++ programming for the fischertechnik TXT controller

## Target groups for this information.
This information is aiming for two groups of users, the end-user and software developer:<br/>
>  A **developer** is someone with at least basic software engineering's skills. He/she will find information about how to create new or modify existing SLI's or applications, suggestions for the toolbox needed, setting up a development environment on MS-Windows. How to use this environment to create documents, and how to use your custom SLI's or applications.

> An **end-user** is somebody with the focus on the TXT and RoboPro and a user of the functionality offered by the SLI's or the applications. He/she will find here information and examples about how to use an SLI or application. The end-user don't need to setup a complete development system, maybe only Putty and Notepad++.

## Introduction
This is all about creating and/or using local applications and RoboPro extensions on the fischertechnik TXT .
There are several possibilities to use C/C++ programs locally on the TXT:

- As TXT local C/C++ application<br/>
A local C/C++ application instead of a local RoboPro program.<br/>
This is faster because of the leak of overhead from the RoboPro. The fischertechnik TXT C/C++ interface offers direct access to the TXT actuators outputs, sensors inputs, the I2C interface and the camera device.
There is for example also access to the file system, disk memory, USB memory and SD-card, the internet interface.
 In combination with technologies like Civetweb, or Mosquitto MQTT this offers a possibility to create functional units which can be part of a bigger system. Also interesting for the end-user and the educational world.

- As TXT Shared Library Interface (SLI) for ROBOPro<br/>
A SLI extends the basic set of RoboPro elements with new one's.
It enables also for the developer user to add functionality to RoboPro. Functionality that can be used by the end-users (RoboPro) later.
The possibilities are the same as for the C/C++ applications but with some restrictions.<br/>
SLI's are very interesting because they can add elements (functionality) to RoboPro for the end-users.<br/>
	[For further information see txt_demo_ROBOPro_SLI.](https://github.com/fischertechnik/txt_demo_ROBOPro_SLI) 

Besides this local use, there are also possibilities to incorporate the TXT remotely in programs which are running on other systems.
- The TXT works with Berkeley sockets and so called transfer area (TA) for communication.
- The TXT is using a socket with port 65000 for the TA, 65001 for the video and 65002 for the I2C.
- [Here](https://github.com/fischertechnik/txt_demo_c_online) you will find how to create a remote program with the .NET Visual Studio (2017, 2019) environment.
- Remote programs can be programmed in a lot of languages, if they support Berkeley sockets. 
- It is also possible to use Python with the [FtRoboPy](https://github.com/ftrobopy/ftrobopy) (pre-installed on the TXT). A Python program can run remotely and local.<br/>
 However, FtPythonPy is using a connection over the sockets, and in fact, it's behavior is like a remote application that when it runs locally on the TXT, it runs with the IP-address (localhost) 127.0.0.1.

## About the terms: TXT C/C++ application,  download and uploading?
In my opinion the name C/C++ download program must be TXT C/C++ application. I will explain "why".<br/>
The dictionary said that iIt is "downloading from" and "uploading to". The application (a compiled program) or SLI is going from the remote system to the TXT and that is uploading. That is also the terminology used by [the fischertechnik TXT web interfacing](./HowToUseTxtWeb.md).<br/>
For that reason I will use the term (TXT C/C++) application , upload to the TXT and downloading from the TXT.<br/>

This repository covers only C/C++ applications and SLI's that will run directly on the TXT. However these applications and SLI's will be develop remotely with a the add of a cross-compiler.

## The organization of this GitHub repository
- The map `FtTxtExamples` is aiming for the end user.
   The applications and/or SLI's are pre-compiled and ready to use. You don't need to have a development environment.<br/>
  This map contains usable examples. [See also](./FtTxtExamples/README.md)
- The map `FtTxtWorkspace` is aiming for the developer<br/>
The  `FtTxtWorkspace` root contains Eclipse example projects and the supporting TXT libraries. [See also the FtTxtWorkspace readme.](./FtTxtWorkspace/README.md)
- In this root you will find a descriptions of "How to ... ? and overviews"

Both the `FtTxtExamples` and `FtTxtWorkspace` maps will be available under "release" as separate zip files. So you can use them without knowledge of the GitHub (or Git) system. 

## Documentation
Overview <a id="overview"></a>

### For the end-user:
- [Introduction and overview executable projects for the end user](./FtTxtExamples/README.md)

### For the developer:
- this Document
- [What is an executable?](app.md).
- [What is in my toolbox? ](WhichToolsYouNeed.md) My program development environment.<br/>
  Same for both application and SLI development.
- [How to setup my fischertechnik workspace in Eclipse?](HowToStartWithFtTxtWorkspace.md)<br/>
  Same for both application and SLI development)
- [How to start with my first fischertechnik project?](HowToStartMyFirstProject_app.md)<br/>
  Almost the same for both application and SLI development.
- [How to start a new Fischertechnik C/C++ application project](./ProjectSetUp_app.md)
- [Notes about TXT executable](./notes_app.md).
- [Introduction and overview local executable projects for the developer](./FtTxtWorkspace/README.md).
 
### General
- [How to use the TXT web server interface for the management of the TXT public file system](./HowToUseTxtWeb.md)

### References
- [Mosquitto MQTT](https://mosquitto.org/)
- [Civetweb](https://github.com/civetweb/civetweb)

# Document history 
- 2020-05-26,27 CvL 466.1.2 app, new
