

#  Extended C/C++ programming for the fischertechnik TXT

## Introduction
This is all about creating and/or using local programs on the fischertechnik TXT and RoboPro extensions.

There are several possibilities to use C/C++ programs locally on the TXT:
- As TXT Shared Library Interface (SLI) for ROBOPro<br/>
A SLI extends the basic set of RoboPro elements with new one's.
It enables also for the user to add functionality to RoboPro.<br/>
SLI's are very interesting because they can add elements (functionality) to RoboPro for the end-users.<br/>
	[For further information see txt_demo_ROBOPro_SLI.](https://github.com/fischertechnik/txt_demo_ROBOPro_SLI) 

- As TXT local programs<br/>
A local program instead of a local RoboPro program.<br/>
This is faster because of the leak of overhead from the RoboPro. In combination with technologies like Civetweb, or Mosquitto MQTT this offers a possibility to create functional units which can be part of a bigger system. Also interesting for the end-user and the educational world.

- As TXT Shared Library Interface (SLI) for ROBOPro<br/>
A SLI extends the basic set of RoboPro elements with new one's.
It enables also for the user to add functionality to RoboPro.<br/>
SLI's are very interesting because they can add elements (functionality) to RoboPro for the end-users.<br/>
	[For further information see txt_demo_ROBOPro_SLI.](https://github.com/fischertechnik/txt_demo_ROBOPro_SLI) 

Besides this local use, there are also possibilities to incorporate the TXT remotely in programs which are running on other systems.
- The TXT works with Berkeley sockets and so called transfer area (TA) for communication.
- The TXT is using a socket with port 65000 for the TA, 65001 for the video and 65002 for the I2C.
- [Here](https://github.com/fischertechnik/txt_demo_c_online) you will find how to create a remote program with the .NET Visual Studio (2017, 2019) environment.
- Remote programs can be programmed in a lot of languages, if they support Berkeley sockets. 
- It is also possible to use Python with the [FtRoboPy](https://github.com/ftrobopy/ftrobopy) (pre-installed on the TXT). A Python program can run remotely and local.<br/>
 However, FtPythonPy is using a connection over the sockets, and in fact, it is a remote program that when it runs locally, it runs with the IP-address (localhost) 127.0.0.1.


This C/C++ repository covers only programs that will run directly on the TXT.

## The organization of this GitHub repository
- The map `FtTxtWorkspace` is aiming for the developer<br/>
The  `FtTxtWorkspace` root contains Eclipse example projects and the supporting TXT libraries. [See also the FtTxtWorkspace readme.](./FtTxtWorkspace/README.md)
- The map `FtTxtExamples` is aiming for the end user<br/>
The map contains usable examples. [See also](./FtTxtExamples/README.md)
- In this root you will find a descriptions of "How to ... ? and overviews"

Both the `FtTxtExamples` and `FtTxtWorkspace` maps will be available under "release" as separate zip files.

## Documentation
Overview <a id="overview"></a>

### For the developer:
- this Document
- [What is an executable?](EXE.md).
- [What is in my toolbox? My program development environment](WhichToolsYouNeed.md)
- [How to setup my fischertechnik workspace in Eclipse?](HowToStartWithFtTxtWorkspace.md)
- [How to start with my first fischertechnik project?](HowToStartMyFirstProject.md)
- [How to start a new Fischertechnik local executable project](./ProjectSetUp(exe).md)
- [Notes](./Notes.md).
- [Introduction and overview local executable projects for the developer](./FtTxtWorkspace/README.md).
- 
### For the end-user:
- [Introduction and overview executable projects for the end user](./FtTxtExamples/README.md).
- 
### General
- [How to use the TXT web server interface for uploading](./HowToUseTxtWeb.md)

# document history <a id="history"></a>
- 2020-05-24 CvL 466.1.1 new
