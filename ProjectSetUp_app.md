# How can I setup a new SLI project from scratch
version: 2020-05-16
!!!!!Under development


## Introduction
### Step 1 Preparation 
> If you have already a workspace with the TxtDeps ready then you can  [skip this step](#skip1).

- To start with a new SLI-project, you need to have a workspace, for example `H:\workspace\FtTxtWorkspace` .  
`FtTxtWorkspace` is here your Eclipse workspace name.
- In this workspace you place the `TxtDeps-project` (if it is not their already). This `TxtDeps`-project contains all the information about the includes and libraries which are available on the TXT.
- Now you can start Eclipse. Eclipse will ask for the workspace directory.  
![directory workspace](./docs/ProjectSetup/SetUO00.PNG)

- There is one important preference setting for the workspace to realize. The directory to your Linaro toolchain.  
In this example the toolchain `gcc-linaro-7.2.1-2017.11-i686-mingw32_arm-linux-gnueabihf` has been installed in `H:\TXT\toolchain\`
  - Go in the Eclipse top menu to the item `Windows` and select the `preferences`.  
![Preferences toolchain](./docs/toolchain/Toolchain(EcEnv1).PNG)

  - Select in the preferences the item `Build` and then `Enviroment`.  
![Preferences toolchain](./docs/toolchain/Toolchain(EcEnv2).PNG)   
Fill in as <strong>Variable</strong>  `LinaroMap`. (Take care of the capital and small.)    
And press `Apply and Close`
- How to add the library TxtDeps to Eclipse?
  - Go in the Eclipse top menu to the item `Files` and select the `Import`.  
  ![Preferences toolchain](./docs/import/Import01.PNG)  
  Select `Existing Projects into Workspace` and press `Next`.

  - Select the workspace root `H:\workspace\FtTxtWorkspace` and the project `TxtDeps` appears.  
    ![Preferences toolchain](./docs/import/Import02.PNG)   
  Select this project and press on `Finish`.

###<a id="skip1"></a> Now is your workspace to add new or import existing projects.

There are a couple of ways to start a new project within Eclipse:
1. [Create a new project from scratch with the Eclipse File-menu.](#scratch).
1. Add/Import the TxtNewProj to your workspace and rename it.
  You need to check the project settings of the new project.
1. Copy the project in the Eclipse Project Explorer and Paste it there too.
   Eclipse will ask you for a new name for the project.
   You need to check the project settings of the new project.
   Remove what your not need.



## <a id="scratch"></a> From scratch
### Step 1
Go the the top menu `File` and select `New C/C++ Project`.

![Image add lib](./docs/ProjectSetup/SetUO01.PNG)

Select `C++ Managed Build` and press `Next`.

### Step 2 Ste the type of the project and the name
Add a name for your project.  
![Image add lib](./docs/ProjectSetup/SetUO02.PNG)  
Choose `Shared Library` for a SLI  or `Exacutable` for a stand alone local program.  
And select the `Cross GCC` option and press `Next`.

### Step 3 Select Configuration

For the moment we don't use the Debug configuration so only the release

![Image add lib](./docs/ProjectSetup/SetUO03.PNG)

press `Advanced settings...`.

#### Step 3A Advanced settings: Set -fPIC flag
Set the `-fPIC` position independent code generation   
![Image add lib](./docs/ProjectSetup/SetUO05.PNG)  
Set the compiler option. This is important for dynamic linking.
If forgotten the compiler will generate an error.
Press `Apply`
#### Step 3B Advanced settings: Set the dialect ISO C11/C++11
C/C++ knows a lot of dialects.

![Image add lib](./docs/ProjectSetup/SetUO06.PNG)
![Image add lib](./docs/ProjectSetup/SetUO07.PNG)  
Press `Apply`

#### Step 3C Advanced settings: Set the reference to the Include in the TxtDeps.
![Image add lib](./docs/ProjectSetup/SetUO08.PNG)
Press `Apply`

#### Step 3D Advanced settings: Set the reference to the Library Paths of the TxtDeps
Add both the Txt_libs`` and `Txt_Libs_deps` to `Library`.
![Image add lib](./docs/ProjectSetup/SetUO09.PNG)
Press `Apply`

#### Step 3E Advanced settings: Updating the Libraries list
For Updating the long dynamic library link list we are going to use a little tric.
The .cproject file will edit directly.

#### Step 3E Advanced settings: Preparation
A small preparation:   
Add a dummy so you can find back the library section in the .cproject later.

![Image add lib](./docs/ProjectSetup/SetUO11.PNG)
Press `Apply and Close`.

#### Step 3F To the next step
You are ready with step 3 so press (3) `Next` for the next step.  
![Image add lib](./docs/ProjectSetup/SetUO03.PNG)

### Step 10 Cross GCC Commands
Now the reference to the tool chain needs to be fill in and we are going to use our workspace environment variable `LinaroMap` in the form `${LinaroMap}`  
The cross compiler prefix = **arm-linux-gnueabihf-**  
The cross compiler path =**${LinaroMap}\gcc-linaro-7.2.1-2017.11-i686-mingw32_arm-linux-gnueabihf\bin**  
So after browsing you will need to replace the directory part with `${LinaroMap}`.

![Image add lib](./docs/ProjectSetup/SetUO12.PNG)

And press `Finish` and the base for your project is ready.

#### Step 14 + 15
Add two maps to the project:
1. src: for the source files
2. inlcudes: for the header files
3. you can add more if you need for the organization of your project.



![Image add lib](./docs/ProjectSetup/SetUO15.PNG)

#### Step 16 + 17
Add the include and src to the project properties.

![Image add lib](./docs/ProjectSetup/SetUO16.PNG)

![Image add lib](./docs/ProjectSetup/SetUO17.PNG)

#### Step 18
Check The Environments settings.
![Image add lib](./docs/ProjectSetup/SetUO18.PNG)

#### Step 19
Set the build engine to the internal one. Otherwise the compiler will generate an error at the beginning of a build of your project.

![Image add lib](./docs/ProjectSetup/SetUO19.PNG)


#### Step 13 Updating the Library list (continue)
Close your new project.
![Image add lib](./docs/ProjectSetup/SetUO13.PNG)
![Image add lib](./docs/ProjectSetup/SetUO14.PNG)
#### Step 20
1. Close the project.
2. Open the .cproject in Notepad++
3. Search for the DummyXXX project
4. Copy the XML list with library names from the README.md in the TxtLibrary project
5. Drop this list here.
6. Don't forget to remove the XML entry with the dummy.
7. Open the project again in Eclipse and inspect the library list in the project properties.

![Image add lib](./docs/ProjectSetup/SetUO20.PNG)

(c) 2020 C van Leeuwen Enschede Nehterlands
