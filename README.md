
<!-- TOC depthFrom:1 depthTo:6 withLinks:1 updateOnSave:1 orderedList:0 -->

- [Extended C/C++ programming for the fischertechnik TXT](#extended-cc-programming-for-the-fischertechnik-txt)
	- [Introduction](#introduction)
	- [The organization of this GitHub repository](#the-organization-of-this-github-repository)
	- [Documentation](#documentation)
		- [For the developer:](#for-the-developer)
		- [For the end-user:](#for-the-end-user)
		- [General](#general)
- [document history <a id="history"></a>](#document-history-a-idhistorya)

<!-- /TOC -->

#  Extended C/C++ programming for the fischertechnik TXT

## Introduction
This is all about creating and/or using local programs on the fischertechnik TXT and RoboPro extensions.

There are several possibilities to use C/C++ programs localy on the TXT:
- As TXT Shared Library Interface (SLI) for ROBOPro<br/>
A SLI extends the basic set of RoboPro elements with new one's.
It enables also for the user to add functionality to RoboPro.

SLI's are very interesting because they can add functionality to RoboPro for the end-users.<br/>
SLI can also be beneficial in educational learning projects. Designers of educational material can use SLI to hide  irrelevant parts so that there is more focus on the main learning objectives.
- As TXT local programs<br/>
A local program instead of a local RoboPro program.<br/>
This is faster because of the leak of overhead from the RoboPro. In combination with technologies like Civetweb, or Mosquitto MQTT this offers a possibility to create functional units which can be part of a bigger system. Also interesting for the end-user and the educational world.


>  A **developer** is someone with at least basic software engineering's skills. He/she will find information about how to create new SLI's or modify existing SLI's suggestions for thetoolbox needed, setting up a development environment on MS-Windows. How to use this environment to create documents, and how to use your custom SLI's or an executable.

> An **end-user** is somebody with the focus on RoboPro and a user of the functionality offered by the SLI's. He/she will find here information and examples about how to use an SLI, the results of what has been developed.


Besides the local use, there are also possibilities to incorporate the TXT remotely in programs which are running on other systems.
- The TXT works with Berkeley sockets and so called transfer area (TA) for communication.
- The TXT is using a socket with port 65000 for the TA, 65001 for the video and 65002 for the I2C.
- [Here](https://github.com/fischertechnik/txt_demo_c_online) you will find how to create a remote program with the .NET Visual Studio (2017, 2019) environment.
- It is also possible to use Python with the [FtRoboPy](https://github.com/ftrobopy/ftrobopy) (pre-installed on the TXT). A Python program can run remotely and local.<br/>
- However, FtPythonPy is using a connection over the sockets, and in fact, it is a remote program that when it runs locally, it runs with the IP-address (localhost) 127.0.0.1.
- Remote programs can be programmed in a lot of languages, if they support Berkeley sockets.


However this C/C++ part covers only programs that will run directly on the TXT.

## The organization of this GitHub repository
- The map `FtTxtExamples` is aiming at the end user<br/>
The map contains usable examples. [See also](./FtTxtExamples/README.md)
- The map `FtTxtWorkspace` is aiming on the developer<br/>
The root contains Eclipse example projects and the supporting TXT libraries. [See also](./FtTxtWorkspace/README.md)
- In the root you will find a descriptions of "How to ... ? and overviews"

Both the `FtTxtExamples` and `FtTxtWorkspace` maps will be available under "release" as separate zip files.

## Documentation
Overview <a id="overview"></a>

### For the developer:
- this Document
- [What is an SLI?](SLI.md).
- [What is in my toolbox? My program development environment](WhichToolsYouNeed.md)
- [How to setup my fischertechnik SLI workspace in Eclipse?](HowToStartWithFtTxtWorkspace.md)
- [How to start with my first fischertechnik SLI project?](HowToStartMyFirstProject.md)
- [How to start a new Fischertechnik SLI project](./ProjectSetUp(so).md)
- [Notes](./Notes.md).
- [Introduction and overview SLI project for the developer](./FtTxtWorkspace/README.md).
- 
### For the end-user:
- [Introduction and overview SLI projects for the end user](./FtTxtExamples/README.md).
- 
### General
- [How to use the TXT web server interface](./HowToUseTxtWeb.md)
- 
# document history <a id="history"></a>
- 2020-05-16/18/24 CvL 466.1.1 new
