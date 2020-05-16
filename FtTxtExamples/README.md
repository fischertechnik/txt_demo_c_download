# Examples for the end user
Here you will find pre-compiled examples.
## What are the maps about?
### For a SLI:
- lib map: The shared library in the
- RoboPro map: One or more RoboPro programs, which shows how to use this SLI
- root: Documentation about the functionality of this SLI
### For the local executable
- C-Program map: The executable
- root: Documentation about the functionality of this executable.

## How to install?
The installation of the SLI's and executable can be done with the TXT web interface.  
The TXT interface enables also the maintenance of the public maps on the TXT, including connected USB-memory and SD-card (formatted as FAT32)
- The TXT web server needs to be activated.
- Use your web browser to access the web page  
URL= http://<ip-addres of the TXT>
- ID=TXT, pasword= the actual number of the TXT
- upload the SLI library to the libs map.
- upload the executable to the C-Program map
## Overview example projects
![blocks](docs/blocks.png)

> You need TXT firmware version >=4.4.3

> see ROBOPro help in section 8.2.9 and 8.2.10

## Overview examples

All examples are Eclipse projects.
### TxtSharedLibraryInterface
    SLI basics.
### TxtSharedLibraryInterfaceDemo01
    SLI show the use of the Joystick
    A control element for a two wheels FT-bot (TXT discovery kit)
### TxtSharedLibraryInterfaceDemo02 (not yet available)
    SLI show the use of the Extended Motor control
    
### TxtDeps
    Contains the include and library fiels for the Eclipse projec (is also a project)

# document history
- 2020-05-16 v 466.1.1 new
