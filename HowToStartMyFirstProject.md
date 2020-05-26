# Content
<!-- TOC depthFrom:1 depthTo:6 withLinks:1 updateOnSave:1 orderedList:0 -->

- [Content](#content)
- [How to start with my first fischertechnik SLI project?](#how-to-start-with-my-first-fischertechnik-sli-project)
	- [`TxtSharedLibraryInterface`](#txtsharedlibraryinterface)
		- [`TxtSharedLibraryInterface`](#txtsharedlibraryinterface)
		- [`TxtSharedLibraryInterface2`](#txtsharedlibraryinterface2)
		- [`TxtSharedLibraryInterfaceDemo01`](#txtsharedlibraryinterfacedemo01)
		- [`TxtSharedLibraryInterfaceDemo02`](#txtsharedlibraryinterfacedemo02)
		- [`TxtMyProject`](#txtmyproject)
	- [Adding projects to this `FtTxtWorkspace`](#adding-projects-to-this-fttxtworkspace)
- [document history](#document-history)

<!-- /TOC -->
[Back to main content overview](./README.md#overview)

# How to start with my first fischertechnik SLI project?

We saw in [How to setup my Eclipse workspace](./HowToStartWithFtTxtWorkspace.md)   how we were able to prepare eclipse for the real thing: creating, compiling and testing of programs for the TXT.<br/>
Now we are going to compile and run some example SLI and then it is time to setup our first new SLI.
We will also see how to track and analyze the progress of an ongoing RoboPro program using an SLI with Putty and Notepad ++

The support this SLI introduction you will find a set of projects with the name `TxtSharedLibraryInterface`in the `FtTxtWorkspace`. 
[The FtTxtWorkspace README](./FtTxtWorkspace/README.md)

## `TxtSharedLibraryInterface`
`TxtSharedLibraryInterface` is about the basics:
- compiling
- installing
- using in a RoboPro programming
- tracing with Putty and consultation of the trace log with Notepad++, [See also](.//README.md#howtracelog)
- tracing with SPDlog.

The 'TxtDeps` root contains a `README.me` about the instruction of how to make use of these libraries and includes in your projects

Each root  of the following projects contains a `README.md` with the detail, description  and instructions for that project
### `TxtSharedLibraryInterface`

`TxtSharedLibraryInterface` is about the basics.

### `TxtSharedLibraryInterface2`

`TxtSharedLibraryInterface2` is about the on-line 5 sec problem and a the blocking problem.

### `TxtSharedLibraryInterfaceDemo01`

 `TxtSharedLibraryInterfaceDemo01`is about the use of the TA (`transfer area`)
 
### `TxtSharedLibraryInterfaceDemo02`

 `TxtSharedLibraryInterfaceDemo02` is about the use of an encoder motor
### `TxtMyProject`

`TxtMyProject` is about creating the start code for your first project.

## Adding projects to this `FtTxtWorkspace`
Later you can add more new projects or projects from others into this `FtTxtWorkspace`.
It is also possible to have both SLI and executable projects in this `FtTxtWorkspace`. Both are using the same `FtxDeps`project and `LinaroMap` Environment variable. Only the 'asset' different.
- Add an existing Eclipse TXT project to this workspace.
  Copy that relevant project into the `FtTxtWorkspace` and use the Eclipse menu `File|Import` to add this project to the workspace. **Check if the project properties are fine!** 
  
- Create a new project by copying an existing one.
  Select the project, which you prefer to copy, in the`FtTxtWorkspace`.<br/>
  Go with the right mouse button to the properties and select `Copy`.<br/>
  Go with the right mouse button to the properties and select `Past`.<br/>
  You will see a popup-box with the question for a new name. Fill the name for your project in. Press the `Copy` button.<br/>
  Check the project properties of the `C/C++ General`| `Paths and Symbols`  for the includes are fine. Probably you will need to change some paths.<br/>
  Clean the `src` file and start with coding. 
- How the create a new SLI project from scratch has been describe in:   [Project setup from scratch](./ProjectSetUp(so).md) 

That is all folks, have fun and success with your proper SLI's and/or executables.

<a id="history"></a>

# document history 
- 2020-05-24,26 CvL 466.1.1 new<br/>
- Original from: on-line training SLI-programming<br/>
  © 2020-04 ing. C. van Leeuwen Btw. Enschede Netherlands
