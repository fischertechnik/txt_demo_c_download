# Content
<!-- TOC depthFrom:1 depthTo:6 withLinks:1 updateOnSave:1 orderedList:0 -->

- [Content](#content)
- [What is a fischertechnik RoboPro SLI?](#what-is-a-fischertechnik-robopro-sli)
	- [Introduction](#introduction)
	- [The `Shared library Input` and the `Shared library Output` element.](#the-shared-library-input-and-the-shared-library-output-element)
		- [Where to find?](#where-to-find)
		- [What is the meaning of their properties?](#what-is-the-meaning-of-their-properties)
			- [General properties](#general-properties)
	- [How to trace/debug SLI's](#how-to-tracedebug-slis)
	- [Known issues<br/>](#known-issuesbr)
		- [Online use](#online-use)
		- [Blocking](#blocking)
		- [Stays in memory](#stays-in-memory)
		- [Errors after replacing a SLI shared library file.](#errors-after-replacing-a-sli-shared-library-file)
- [document history](#document-history)

<!-- /TOC -->
[Back to main content overview](/README.md#overview)
# What is a fischertechnik RoboPro SLI?
## Introduction
From the perspective of RoboPro an SLI is a functional unit. RoboPro can send data to a SLI and can get data back from the SLI. But RoboPro can also start and stop more complex activities in a SLI, for example dedicated websocket or MQTT based communication with the outside world, image processing, I2C drivers, more complex closed control loops, etc.<br/>
The fischertechnik TXT SLI makes it possible that C/C++ functions can be access via a RoboPro elements.
For this RoboPro knows 2 elements, the `Shared library Input` element and the `Shared library Output` element. 

The shared library `input/output element` allows to call functions and return/supply a value from/to shared library modules installed on the TXT controller. 
Such libraries are typically written in the C or C++ programming language. 
This allows interfacing ROBOPro with C / C++ programs, which is useful for accessing advanced sensors or for compute intensive tasks like image processing

For outputs the C functions should be declared like:<br/>
 `int setValueDouble(double v);int getValueDouble(double * v);`<br/> `int setValueShort(short v);int getValueShort(short * v); `

## The `Shared library Input` and the `Shared library Output` element.
Each input element allows to return only one numeric value. If parameters are required, the shared library output element can be used to first set parameters in the library. If multiple parameters or multiple return values are required, multiple input and/or output elements can be used. This means that it is typically required to write a small wrapper layer to interface ROBOPro to existing shared libraries. fischertechnik provides a library for the BME680 environmental sensor as example.

The input element can either retrieve a 16 bit signed short or a 64 bit double value from the shared library. Example C declarations for such functions are: `c int getValueDouble(double* t);` `int getValueShort(short* t);`

The function names should start with get and end with Short or Double to indicate the type, but arbitrary names can be used as well. A return value of 0 is interpreted as success, all other return values as error.

### Where to find?
These two element can be found in `Send, receive`:

![](./docs/sli/element(both).PNG)

### What is the meaning of their properties?
This are the two:

![](./docs/sli/element(set).png)  ![](./docs/sli/element(get).png)

#### General properties
1. Library name & Extend library name<br/>
   The name of the share library consists as of 3 parts. <br/>
   [`lib`] 'NAME` [`.so`], The `NAME` is showed in the RoboPro box. <br/>
2. Function name& & Extend library name & Data type<br/>
   Under Function name the C name of the function to be called is entered. If Extend Function Name is checked, the name is prepended with get and the selected data type, either Short or Double, is appended.<br/>
   The name of the interface function consists of 3 parts in C/C++ :<br/>
   [`set` | `get`] `NAME` [`Short`|`Double`], The `NAME` is showed in the RoboPro box. <br/>

   When there is a filter, the complete name will be visible in the RoboPro box.<br/>
   If the `Data type` is an integer, the RoboPro linker expect a function with shorts and
   if the `Data type` is a Float, the RoboPro linker expect a function with shorts.<br/>
   Hereby some examples:
   ```
   /*! Four functions from the library libExampleSLI.so, library NAME =ExampleSLI */

   /*! NAME=Value, data type= double, setter*/
   int setValueDouble(double v) {
   	value_d = v;
   	return 0;
   }

   /*! NAME=Value, data type= short, setter*/
   int setValueShort(short v) {
   	value_s = v;
   	return 0;
   }

   /*! NAME=Value, data type= double, getter*/
   int getValueDouble(double * v) {
   	*v = value_d;
   	return 0;
   }

    /*! NAME=Value, data type= short, getter*/
   int getValueShort(short * v) {
   	*v = value_s;
   	return 0;
   }
   ```
   The Data type of the value returned can be either a 16 bit signed integer or a floating point value. If the data type is floating point, the value is converted from C 64 bit double format to ROBOPro 48 bit float format. Please note that the range and precision of these types is different and conversion errors may occur, especially for out of range values. Please also note that for 16 bit integers values a value of -32768 is treated as undefined/error in ROBOPro and is usually displayed as '?'.

3. Error output<br/>
   Optional the function has the choice to continue with the normal workflow exit or with the error workflow exit.<br/>
   The error workflow exit will be follow when the function return a `int` value `not 0`. or when the RoboPro discover an error. This is visible in the trace info.<br/>
   ```
   /*! Example using */
   int setValueShort(short motorId) {
   	 if (!IsInit) return -1;
     if (motorId>4) return -2; if (motorId<1) return -3;//motorId out of range
   	/* user code */
   	return 0;
   }
   ```
   ![RoboPro](./docs/sli/element(error).png)<br/>
   The information in the trace on the screen.
   ```
   SharedLibraryInterface_ExecuteWriteINT16 libExampleSLI.so setValueShort 5
   SharedLibraryInterface_ExecuteReadINT16 lib 0xb3507898
   SharedLibraryInterface_ExecuteReadINT16 func 0xb1d809e9
   SharedLibraryInterface_ExecuteWriteINT16 libExampleSLI.so setValueShort RESULT -2 5

   ```
4. Lock Interface<br/>
    If Lock Interface is checked, the shared library IO is locked to the current ROBOPro thread. This allows safe combination of several shared library input and output elements without interruptions from other threads. The last element in a sequence must have this unchecked. Otherwise no other ROBOPro thread can use the shared library interface.

## How to trace/debug SLI's
  The fischertechnik RoboPro SLI run time writes enough data to the `stout` and `sterr`, in the SLI the developer can also add his own trace information or use SpdLog. In combination with a SSH-terminal (Putty), the log file from Putty and a editor like Notepad++ (search in the text) is this an important source during the development of the SLI.
## Known issues<br/>
### Online use
RoboPro will lost the connection with the SLI when a SLI is not used for more then 5 sec. This gives error without information in the trace.<br/> Workaround: Add a StayAwake function to the SLI an activate this function in the RoboPro program.
```
int setStayAwakeShort(short t) {
	if (!IsInit) {
		fprintf(stderr, "setStayAwakeShort: Not initialized!\n");
		return -1;
	}
	return 0;
}
```
 ![RoboPro](./docs/sli/element(5s).png)<br/>

### Blocking
When a function is in progress, the access to the other functions in the SLI are blocked. So don't at sleep function to a SLI function. The wait element in RoboPro is not blocking.
### Stays in memory
The library will be load by the RoboPro runtime into the memory at the first use. It stays in the memory after the termination of the RoboPro program. The global variable and objects will keep there last values too.<br/>
RoboPro does not signal the end of his program to the SLI. Sometimes it can be necessary to take care of a decent termination of the program.
###Errors after replacing a SLI shared library file.
The first time that a RoboPro program, which is using the SLI, has been restarted after renewing a SLI .so file., it will terminate with errors. The new SLI will be loaded after this failure. The next time the RoboPro program will start fine.<br/>
The SSH and SFTP connection are also last.<br/>
Workaround: Restart the TXT after replacing a SLI.


# document history
- 2020-05-19/22/26 CvL 466.1.1 new<br/>
  Some parts are copy from the original README.md
