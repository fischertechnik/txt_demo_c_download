# Index
<!-- TOC depthFrom:1 depthTo:6 withLinks:1 updateOnSave:1 orderedList:0 -->

- [Index](#index)
- [The <font  color="#e2001a">fischer</font><font  color="#006ab2">technik</font> transfer area (TA)](#the-font-colore2001afischerfontfont-color006ab2technikfont-transfer-area-ta)
	- [Reservation](#reservation)
	- [Introduction](#introduction)
	- [Remarks](#remarks)
		- [Typical structure of a basic local program.](#typical-structure-of-a-basic-local-program)
		- [Typical structure of a local program with `TransferAreaCallbackFunction`.](#typical-structure-of-a-local-program-with-transferareacallbackfunction)
	- [The TA main structure](#the-ta-main-structure)
		- [source of information](#source-of-information)
		- [TA00  The complete TA for a TXT controller](#ta00-the-complete-ta-for-a-txt-controller)
		- [TA01 `ftX1config`](#ta01-ftx1config)
			- [Template for a function to set the Motor configuration](#template-for-a-function-to-set-the-motor-configuration)
			- [Template for a  function to set the Universal Input configuration](#template-for-a-function-to-set-the-universal-input-configuration)
		- [TA02 `ftX1output`](#ta02-ftx1output)
			- [Typical use for normal motors](#typical-use-for-normal-motors)
			- [Template for a higher level motor function](#template-for-a-higher-level-motor-function)
			- [Typical use for enhance motors](#typical-use-for-enhance-motors)
			- [Typical use for enhanced motors, to inspect if the black box has ended](#typical-use-for-enhanced-motors-to-inspect-if-the-black-box-has-ended)
		- [TA03 ftX1input](#ta03-ftx1input)
			- [Template for a read value for a certain Universal Input.](#template-for-a-read-value-for-a-certain-universal-input)
		- [About counters C1..C4,](#about-counters-c1c4)
			- [Typical templates for read counter value](#typical-templates-for-read-counter-value)
			- [Typical templates for start reset](#typical-templates-for-start-reset)
			- [Typical templates for is reset ready](#typical-templates-for-is-reset-ready)
		- [TA04 `_TXT_SPECIAL_OUTPUTS`](#ta04-txtspecialoutputs)
			- [Typical templates for the sound method](#typical-templates-for-the-sound-method)
		- [TA05 `_TXT_SPECIAL_INPUTS`](#ta05-txtspecialinputs)
		- [TA06 `_TXT_SPECIAL_INPUTS_2`](#ta06-txtspecialinputs2)
			- [Typical templates for the microphone methods](#typical-templates-for-the-microphone-methods)
- [Document history](#document-history)

<!-- /TOC -->

# The <font  color="#e2001a">fischer</font><font  color="#006ab2">technik</font> transfer area (TA)
> Remark: document is under development.

## Reservation
The technical documentation on the TA and the MotorIoLib functionality is limited to what is in the source header files (FtShmem.h and KeLibTxtDl.h). This document tries to combine that information with knowledge gained in practice, and from working with Robo-interface and TX-C. No rights can be derived from the functionalities mentioned.

## Introduction

  A description of the <font  color="#e2001a">fischer</font><font  color="#006ab2">technik</font> transfer area (TA) exist since the <font  color="#e2001a">fischer</font><font  color="#006ab2">technik</font> Robo-interface. In fact the TA is a shared memory area which take care of the communication between the user program and the fischertechnik actuator/sensor logic (On the TXT this has been called the `MotorIOLib`). Because the TA is a collection of bytes, it could also be transmitted over a connection, like USB, BlueTooth or IP,  to another device. The structure of the TA has been extended with the arrivals of the <font  color="#e2001a">fischer</font><font  color="#006ab2">technik</font> TX-Controller and the <font  color="#e2001a">fischer</font><font  color="#006ab2">technik</font> TXT controller. However the basic principals are still the same.<br/>
In this document we will explain the basics of "How to use the TA?" from the point of view of the application.<br/>
Only the Motor/Output (actuators) and Universal Inputs (sensors) will be discussed. With this information the user would be able to understand the other parts like: sound, microphone, IR-controller device, Counter inputs.<br/>
The reader is expected to have reasonable knowledge of C and C ++. There is enough information on the internet about the possibilities and use of C11++ and C14++. The reader should also have good knowledge and experience with RoboPro level 4/5 elements.

## Remarks
> The <font  color="#e2001a">fischer</font><font  color="#006ab2">technik</font> TXT does not use all parts (entries) of the TA.

> The enhance Motor control is a black box which runs as part of the <font  color="#e2001a">fischer</font><font  color="#006ab2">technik</font> actuator/sensor logic (`MotorIOLib`).
  The user program can only send commands to this black box and wait until it is ready. This black box is using a Motor in combination with a Counter. See also the description of the enhance motor control in the RoboPro help.
  
> A actuator output can be configurated as (full bridge device) Mx motor output or as two (half bridge) Ox*2, Ox*2+1 outputs. (See also RoboPro) 
  
### Typical structure of a basic local program.
> In the local mode, the actuator/sensor logic updates the TA every +/- 1 msec. 

> In the remote (online) mode, a program that runs as user program transmit/receive parts of the TA over IP to/from the user device. which parts are used can be found in [`ftProInterface2013TransferAreaCom.cpp`: `DoTransferSimple()` and `DoTransferCompressed()`](https://github.com/fischertechnik/txt_demo_c_online/blob/master/SolutionOnLineSamples/Common/ftProInterface2013TransferAreaCom.cpp). 

> A local program needs to ask the `MotorIO` thread if it is possible to access the TA. This is done with calling  `StartTxtDownloadProg`.   `GetKeLibTransferAreaMainAddress` gives the address (pointer to) the  TA structure.<br/>See also the [`KeLibTxtDl.h` for these functions](https://github.com/fischertechnik/txt_demo_c_download/blob/master/FtTxtWorkspace/TxtDeps/Txt_Includes/KeLibTxtDl.h).

> asynchronous updating of the TA.
   

```C
int main(void) 
{
	FISH_X1_TRANSFER    *pTArea;
	if (StartTxtDownloadProg() == KELIB_ERROR_NONE)
	{
		pTArea = GetKeLibTransferAreaMainAddress();
		if (pTArea)
		{   // It's a real pointer
// your configuration and start up logic

			while (/*condition for keeping the program running*/)
			{
				//Your functional logic
			};
		}
		StopTxtDownloadProg();
	}
	return 0;
}
```

### Typical structure of a local program with `TransferAreaCallbackFunction`. 
> The `TransferAreaCallbackFunction` callback function will called by the `MotorIO` logic after update of the TA structure. The repetition time has not been documented but could be determined by experiment.
This time could be of the order of 1 msec.<br/>

> See also the [`KeLibTxtDl.h` ](https://github.com/fischertechnik/txt_demo_c_download/blob/master/FtTxtWorkspace/TxtDeps/Txt_Includes/KeLibTxtDl.h) for this function.

> Attention: 
  - This callback is called between receiving inputs and sending outputs to TXT the hardware. So based on the Input's (sensor data) the values for the actuators can be calculated.
  - The callback function runs synchronous in the MotorIO thread. So time consuming logic will slow down the refresh of the TA.  
  
```C

int main(void) 
{
    FISH_X1_TRANSFER    *pTArea;
    if (StartTxtDownloadProg() == KELIB_ERROR_NONE)
    {
        pTArea = GetKeLibTransferAreaMainAddress();
        if (pTArea)
        {   
            // Start using Callback Function
            SetTransferAreaCompleteCallback(TransferAreaCallbackFunction);
        //Main loop. 
				//Let the callback do his work, keep the main program active.
            while ( ! stopCondition)
            {   
					     	std::this_thread::sleep_for(std::chrono::milliseconds(500));//sleep 500 msec
            }
			   //stop the callback activity			
				 SetTransferAreaCompleteCallback(nullptr);		
        }
        StopTxtDownloadProg();
    }
	return 0;
}
```
And the callback for the functionality
```C
// Callback Function. 
// This is called between receiving inputs and sending outputs to TXT the hardware
bool TransferAreaCallbackFunction(FISH_X1_TRANSFER *pTransArea, int i32NrAreas)
{   // ============================================================

    //Your functional logic
    //Update  stopCondition for main loop
    return true;        // if you return FALSE, then the Hardware is stopped !!!
}

```

## The TA main structure

### source of information
See also for
- [the online programming`](https://github.com/fischertechnik/txt_demo_c_online/blob/master/SolutionTxtLib/include/FtShmemTxt.h)
- [the local and SLI programming](https://github.com/fischertechnik/txt_demo_c_download/blob/master/FtTxtWorkspace/TxtDeps/Txt_Includes/FtShmem.h)
- [more examples about the use of the TA](https://github.com/fischertechnik/txt_demo_c_online/blob/master/SolutionTxtApps/TestProj02/Main.cpp)

### TA00  The complete TA for a TXT controller
The overall structure. The details will be discussed.
```C
typedef struct shm_if_s
{
	FTX1_SHMIFINFO      ftX1info;       // info structure
	FTX1_STATE          ftX1state;      // state structure
	FTX1_CONFIG         ftX1config;     // config structure   
	FTX1_INPUT          ftX1in;         // input structure
	FTX1_OUTPUT         ftX1out;        // output structure
	FTX1_DISPLAY        ftX1display;    // display structure

	TRANSFER_STATUS     IFStatus;
	CHANGE_STATE        IFChange;       // change state of Input, Counter, Timer
	RP_TIMER            IFTimer;        // 16-Bit timer variables
	MOTOR               IFMotor;        // motors control
	INPUT_SIM           IFInputSim;     // input simulation
	HOOK_TABLE          IFHookTable;    // hook table with functions pointers

	TXT_SPECIAL_INPUTS  sTxtInputs;     // TXT Special Inputs (Power, Temp, IR...)  
	TXT_SPECIAL_OUTPUTS sTxtOutputs;    // TXT Special Outputs (sound, LED)  
	TXT_SPECIAL_INPUTS_2 sTxtInputs2;     // TXT Special Inputs (Power, Temp, IR...)

	char                reserved[RESERVE_SIZE];
} FISH_X1_TRANSFER


```
In case of a master and a slave there is an area of two of these structures. `FISH_X1_TRANSFER*` is pointer to this area
In the programming you can have access to this structure by for example:
```C
enum ShmIfId_TXT
{
	LOCAL_IO = 0,           //Id for Local I/O
	REMOTE_IO_1,            //Id for Remote I/O Slave #1/TXT can have only 1 slave
	SHM_IF_CNT              //For counting only
};

FISH_X1_TRANSFER* TransArea = GetTransferAreasArrayAddr();
//examples of abbreviations:
 FTX1_INPUT* MftX1in = & TransArea[ShmIfId_TXT::LOCAL_IO].ftX1in;
 FTX1_OUTPUT* MftX1out = &TransArea[ShmIfId_TXT::LOCAL_IO].ftX1out;
 FTX1_INPUT* SftX1in = & TransArea[ShmIfId_TXT::REMOTE_IO_1].ftX1in;
 FTX1_OUTPUT* SftX1out = &TransArea[ShmIfId_TXT::REMOTE_IO_1].ftX1out;
 FTX1_CONFIG* MftX1config = & TransArea[ShmIfId_TXT::LOCAL_IO].ftX1config;
 FTX1_STATE*  MftX1state = & TransArea[ShmIfId_TXT::LOCAL_IO].ftX1state;
```

### TA01 `ftX1config`
First step in a programming is the configuration of the Inputs and Outputs, this needs to be done at the start of the program before starting with the control logic itself:
```C
/// <summary>
/// The Universal Input modes
/// </summary>
enum InputMode
{
  MODE_U = 0,   //Voltage 10V
  MODE_R = 1,       //Resistance 10kOhm
  MODE_ULTRASONIC = 3, //Distance sensor
  MODE_INVALID = 4
};

typedef struct uni_inp_config
{
	UINT8           mode;        // enum InputMode  mode
	BOOL8           digital;     // true is digital, false = analogue
	char            dummy[2];
} UNI_CONFIG;

typedef struct cnt_inp_config
{
	UINT8           mode;       //1= count on rising edge, 0= count on faling edge
	char            dummy[3];
} CNT_CONFIG;

typedef struct ftX1config
{
	UINT8           pgm_state_req;        //Not in use on the TXT
	BOOL8           old_FtTransfer;       //Not in use on the TXT
	char            dummy[2];             //Not in use on the TXT
	BOOL8           motor[IZ_MOTOR];     // 0=single output O/O, 1=motor output M (default)
	UNI_CONFIG      uni[IZ_UNI_INPUT];   // Default mode = 0, digital 1
	CNT_CONFIG      cnt[IZ_COUNTER];     // Default mode= 1
	INT16           motor_config[IZ_MOTOR][4];  //Not in use on the TXT
} FTX1_CONFIG;
```
typical use:
```C
enum  Input :uint8_t
{
  I1 = 0, I2, I3, I4, I5, I6, I7, I8
};
enum Motor :uint8_t
			{
				M1 = 0, M2 = 1, M3 = 2, M4 = 3
			};
FTX1_CONFIG* MftX1config = & TransArea[ShmIfId_TXT::LOCAL_IO].ftX1config;
MftX1config->uni[Input::I1].mode = InputMode::MODE_R;//type switch
MftX1config->uni[Input::I1].digital = true;
// trail sensor on I2/I3
MftX1config->uni[Input::I2].mode = InputMode::MODE_U;//type switch
MftX1config->uni[Input::I2].digital = true;
MftX1config->uni[Input::I3].mode = InputMode::MODE_U;//type switch
MftX1config->uni[Input::I3].digital = true;
//Distance sensor on I6
MftX1config->uni[Input::I6].mode = InputMode::MODE_ULTRASONIC;//type
MftX1config->uni[Input::I6].digital = false;
//Motors on M1 and M2
MftX1config->motor[Motor::M1].mode = 1; //As full bridge (M functionality) (default)
MftX1config->motor[Motor::M2].mode = 1; //As full bridge (M functionality)(default)
//Led/lamp magneet on O5 and O6
MftX1config->motor[Motor::M3].mode = 0; //As two half  bridges (O functionality)
//Inform the IoMotor-controller to update the configuration.
FishX1Transfer[shmId]->ftX1state.config_id += 1;

```

#### Template for a function to set the Motor configuration
```C
void SetConfigMotor(int shmId, int idx, bool status) {
    if ( idx < 0 || idx >= IZ_MOTOR ) {
        Log(LOGERR, "Invalid motor index (%d) ignored !", idx);
        return;
    }
    //  set motor active
    FishX1Transfer[shmId]->ftX1config.motor[idx] = (BOOL8) status;
    //  config change, increment config_id
    FishX1Transfer[shmId]->ftX1state.config_id += 1;
}
```
#### Template for a  function to set the Universal Input configuration
```C
void SetConfigUni(int shmId, int idx, int mode, bool digital) {

    if ( idx < 0 || idx >= IZ_UNI_INPUT )
        return;
    FISH_X1_TRANSFER *pTA = FishX1Transfer[shmId];
    //  set mode (U/R), analog/digital for uni io's in config structure
    pTA->ftX1config.uni[idx].mode = (UINT8) mode;
    pTA->ftX1config.uni[idx].digital = (BOOL8) digital;
    //  clean uni value in order not to get overrun at the very first moment after mode change
    pTA->ftX1in.uni[idx] = 0;
    //  config change, increment config_id
    pTA->ftX1state.config_id += 1;
}

```

### TA02 `ftX1output`
In this structure the program write values to control the behavior of the actuators (M or O) and the enhance Motor control (including fast Counters).

```C
typedef struct ftX1output
{
	// Counter reset requests (increment each time by one)
	UINT16          cnt_reset_cmd_id[IZ_COUNTER];
	// If not 0, synchronize this channel with the given channel (1:channel 0, ..)
	UINT8           master[IZ_MOTOR];
	// User program selected motor PWM values
	INT16           duty[IZ_PWM_CHAN];
	// Selected distane (counter value) at which motor shall stop
	UINT16          distance[IZ_MOTOR];
	// Increment by one each time motor_ex settings change
	UINT16          motor_ex_cmd_id[IZ_MOTOR];
} FTX1_OUTPUT;

```
#### Typical use for normal motors
```C
//M1 CW
TransArea[ShmIfId_TXT::LOCAL_IO].ftX1out.duty[2 * Motor::M1] = 0;
TransArea[ShmIfId_TXT::LOCAL_IO].ftX1out.duty[2 * Motor::M1 + 1] = 512;//range 0..512
//M2 CCW
TransArea[ShmIfId_TXT::LOCAL_IO].ftX1out.duty[2 * Motor::M2] = 512;//range 0..512
TransArea[ShmIfId_TXT::LOCAL_IO].ftX1out.duty[2 * Motor::M2 + 1] =0 ;
```

#### Template for a higher level motor function

```C
enum Direction :int8_t {
    CCW = -1, Halt = 0, CW = 1
  };
  
FtErrors SetOutMotorValues(ShmIfId_TXT shmId, Motor motorId, int duty, Direction direction) {
	FISH_X1_TRANSFER* pX1 = &FishX1Transfer[shmId];

	if (pX1->ftX1config.motor[motorId] != 1) {
		return FTLIB_ERR_INVALID_PARAM;
	}

	if (duty > 512 || duty < 0) {
		return FTLIB_ERR_INVALID_PARAM;
	}

	//  fill motor attributes in fish.X1 output structure
	switch (direction)
	{
	case Direction::CW:
		pX1->ftX1out.duty[motorId * 2] = duty;
		pX1->ftX1out.duty[motorId * 2 + 1] = 0;
		break;
	case Direction::CCW:
		pX1->ftX1out.duty[motorId * 2] = 0;
		pX1->ftX1out.duty[motorId * 2 + 1] = duty;

		break;
	case Direction::Halt:
		pX1->ftX1out.duty[motorId * 2] = 0;
		pX1->ftX1out.duty[motorId * 2 + 1] = 0;
		break;
	default:
		return FTLIB_ERR_FAILED;
		break;
	}
	return FTLIB_ERR_SUCCESS;
};
```

#### Typical use for enhance motors
> Setting distance to >0 will activate the enhance motor control.<br/>

> To return to normal motor use and stop the enhance mode, the `distance` and `master` need  all set to `0`.

> The value of `motor_ex_cmd_id` will be given back in the `ftX1in` after the enhance Motor controller had finished this command.
  
> Attention: The index 'master'  is Motor1 =1, Motor2=2, Motor3=3 or Motor4=4.<br/> 
  `0` means here no master. 	 

```C 
//Set duty for both motors 
TransArea[ShmIfId_TXT::LOCAL_IO].ftX1out.duty[2 * Motor::M1] = 256;
TransArea[ShmIfId_TXT::LOCAL_IO].ftX1out.duty[2 * Motor::M1 + 1] = 0;
TransArea[ShmIfId_TXT::LOCAL_IO].ftX1out.duty[2 * Motor::M2]  = 0; 
TransArea[ShmIfId_TXT::LOCAL_IO].ftX1out.duty[2 * Motor::M2 + 1]  = 256;  //
//Set distance
TransArea[ShmIfId_TXT::LOCAL_IO].ftX1out.distance[Motor::M1] = 1000;//1000 steps  (C1)
TransArea[ShmIfId_TXT::LOCAL_IO].ftX1out.distance[Motor::M2] = 1000;//1000 steps  (C2)
//Set the the master for the slave
TransArea[ShmIfId_TXT::LOCAL_IO].ftX1out.master[Motor::M2] = Motor::M1+1// , M2 is the slave, the master for M2 is M1
TransArea[ShmIfId_TXT::LOCAL_IO].ftX1out.master[Motor::M1] = 0//M1 is the master
//reset the  motor_ex_reached
TransArea[ShmIfId_TXT::LOCAL_IO].ftX1in.motor_ex_reached[Motor::M1] = false; //needs to be resetted by the user
TransArea[ShmIfId_TXT::LOCAL_IO].ftX1in.motor_ex_reached[Motor::M2] = false; //needs to be resetted by the user
//Start command, 
TransArea[ShmIfId_TXT::LOCAL_IO].ftX1out.motor_ex_cmd_id[Motor::M1]++;
TransArea[ShmIfId_TXT::LOCAL_IO].ftX1out.motor_ex_cmd_id[Motor::M2]++;
``` 

#### Typical use for enhanced motors, to inspect if the black box has ended
> In fact `motor_ex_reached[Motor::M1]` means for example:
`TransArea[ShmIfId_TXT::LOCAL_IO].ftX1out.motor_ex_cmd_id[Motor::M1]==TransArea[ShmIfId_TXT::LOCAL_IO].ftX1in.motor_ex_cmd_id[Motor::M1]`

> `motor_ex_reached` is in the remote (on-line) mode calculated at the remote site.

See ftX1input
```C
if (  
TransArea[ShmIfId_TXT::LOCAL_IO].ftX1in.motor_ex_reached[Motor::M1] &&
TransArea[ShmIfId_TXT::LOCAL_IO].ftX1in.motor_ex_reached[Motor::M2])
{
// Both motors has reached the end, in this case 1000 steps
}
``` 
or
```C
if (  
 (TransArea[ShmIfId_TXT::LOCAL_IO].ftX1out.motor_ex_cmd_id[Motor::M1]==TransArea[ShmIfId_TXT::LOCAL_IO].ftX1in.motor_ex_cmd_id[Motor::M1])
 &&
 TransArea[ShmIfId_TXT::LOCAL_IO].ftX1out.motor_ex_cmd_id[Motor::M2]==TransArea[ShmIfId_TXT::LOCAL_IO].ftX1in.motor_ex_cmd_id[Motor::M2])
 )
{
// Both motors has reached the end, in this case 1000 steps
}

``` 
### TA03 ftX1input
In this structure the program reads the values coming from the Universal Inputs and enhance Motor control (including fast Counters). <br/>

It also is used to notify the user that some asynchronous actions has been finished:<br/>
- `cnt_reset_cmd_id` the IoMotor-control informs the user which counter reset action has been finished.<br/> See also the `cnt_reset_cmd_id in` the ftX1out section.

- `motor_ex_cmd_id` the IoMotor-control informs the user which enhance motor action has been finished.<br/> See also the `motor_ex_cmd_id` in the  ftX1out section.

- The `uni` value depends on the `mode` and `digital` configuration of that particular Input.

- From the control engineering theory we know that:
  The highest frequency for counting depends on the quality of the pulse. A symmetrical pulse, high-time is the same as the low-time gives the best result. A a-symmetrical pulse will lower the max counting frequency.<br/> The shortest part of the pulse needs to be the same the low-time (or high-time) from the symmetrical pulse. <br/>
	So a the fischertechnik switch in combination with a pulse wheel needs to be adjust very well to approach 
  a symmetrical pulse. Most of the case it is better to lower the max count speed to 75% for an acceptable and stable control system.
```C
typedef struct ftX1input
{
	INT16           uni[IZ_UNI_INPUT];      /// Universal Input value 
	INT16           cnt_in[IZ_COUNTER];     /// Logic state Counter Input
	INT16           counter[IZ_COUNTER];    /// Counter values
	INT16           display_button_left;    // TX-C only
	INT16           display_button_right;   // TX-C only
	// Set to 1 when last requested counter reset was fulfilled, user needs to set this to 0 after using.
	BOOL16          cnt_resetted[IZ_COUNTER];
	// Set to 1 by motor control if target position is reached, user needs to set this to 0 after using.
	BOOL16          motor_ex_reached[IZ_MOTOR];
	// Counter reset command id of the last fulfilled counter reset
	UINT16          cnt_reset_cmd_id[IZ_COUNTER];
	// Motor extended command id of the last fulfilled motor_ex command
	UINT16          motor_ex_cmd_id[IZ_MOTOR];
} FTX1_INPUT;
```



#### Template for a read value for a certain Universal Input.

> Some definitions for the sensors.

```C
	// 5 kOhm Range
	#define R_MIN               10          // [Ohm]
	#define R_MAX               4999        // [Ohm]
	#define R_OVR               5000        // [Ohm]

	// 10V Range
	#define U_MAX               9999        // [mV]
	#define U_OVR               10000       // [mV]

	// Ultrasonic Sensor Range
	#define ULTRASONIC_MIN      2           // [cm]
	#define ULTRASONIC_MAX      1023        // [cm]
	#define ULTRASONIC_OVR      1024        // [cm]
	#define NO_ULTRASONIC       4096        // not present

```

> `overrun` indicates if the `value` is valid.

```C
FtErrors GetInput(ShmIfId_TXT shmId, Input idx, INT16& ftValue, bool& overrun) {
	if (idx < 0 || idx >= IZ_UNI_INPUT) {
		return FTLIB_ERR_INVALID_PARAM;
	}
	FISH_X1_TRANSFER* pX1 = &FishX1Transfer[shmId];
	//  get universal IO value from input structure
	ftValue = pX1->ftX1in.uni[idx];
	switch (pX1->ftX1config.uni[idx].mode)
	{
	case MODE_R: overrun = (pX1->ftX1in.uni[idx] == R_OVR);      break;
	case MODE_U: overrun = (pX1->ftX1in.uni[idx] == U_OVR);      break;
	case MODE_ULTRASONIC: overrun = (pX1->ftX1in.uni[idx] == ULTRASONIC_OVR); break;
	default: overrun = 0; break;
	}
	return FTLIB_ERR_SUCCESS;
}
```

### About counters C1..C4,

These counters are sometimes call "fast counters", why? These counter inputs can be used in different ways.

-   As normal digital sensors input, like the Universal Inputs with a switch. The refresh rate is 10 msec in the online mode => maximum frequency with a symmetrical pulse < +/-100hz.
-   As local counter. This counter could count with a maximum frequency with a symmetrical pulse < +/-1000hz.  
    However in the online mode, the value and state of the counter is only accurate when the counter has stop counting or when the maximum frequency with a symmetrical pulse is < +/-100hz. The value of the counter can be resetted with the request:  `ftX1output cnt_reset_cmd_id`. The responds after the "reset" is ready, will be given with  `ftX1input cnt_reset_cmd_id`  and  `ftX1input cnt_reset_cmd_id`
-   The counter is also been used in the so called enhance mode in combination with a motor. In that case will the motor stop when a number of pulses are reached and this is signaled to the program with 'ftX1input motor_ex_reached'. The value (`count`) of the counter is resetted at the start of the enhance control action .

#### [](https://github.com/fischertechnik/txt_demo_c_download/blob/master/TransferArea.md#typical-templates-for-read-counter-value)Typical templates for read counter value


```C



///

///General get the count and state of a C-input [shmId:idx]
////// Master or slave TXT controller
/// Which counter
/// numeric value
/// logical value, state
/// error
FtErrors ftIF2013TransferAreaComHandlerEx2::GetInCounterValue(ShmIfId_TXT shmId, Counter idx, INT16& count, bool& state) {
	if (idx < 0 || idx >= ftIF2013_nCounters)
	{
		return FTLIB_ERR_INVALID_PARAM;
	}
	FISH_X1_TRANSFER* pX1 = &FishX1Transfer[shmId]; // get counter values from input 			structure
	count = pX1->ftX1in.counter[idx]; state = (pX1->ftX1in.cnt_in[idx] == 0) ? false : true; return FTLIB_ERR_SUCCESS;
}
```
or

```C
///

/// Get only the numeric value of the counter as return value of a C-input [shmId:idx]
////// Master or slave TXT controller
/// Which counter
/// counter value
UINT16 GetInCntCount(ShmIfId_TXT shmId, Counter idx)
{
	if (idx < 0 || idx >= ftIF2013_nCounters)
	{
		ftLog::Log(LOGERR, "GetInCntCount, Invalid C index (%d:%d) ", shmId, idx);
	}
	FISH_X1_TRANSFER* pX1 = &FishX1Transfer[shmId]; // get counter values from input structure
	return (UINT16)pX1->ftX1in.counter[idx];
} 
```
or
```C
///

/// Get the logical state as return value of a C-input [shmId:idx]
////// Master or slave TXT controller
/// Which counter
/// Logical value,state
bool ftIF2013TransferAreaComHandlerEx2::GetInCntState(ShmIfId_TXT shmId, Counter idx)
{
	if (idx < 0 || idx >= ftIF2013_nCounters)
	{
		ftLog::Log(LOGERR, "GetInCntState, Invalid C index (%d:%d) ", shmId, idx);
		return 0;
	}
	FISH_X1_TRANSFER* pX1 = &FishX1Transfer[shmId]; // get counter values from input structure
	return (pX1->ftX1in.cnt_in[idx] == 0) ? false : true;
}
```

#### [](https://github.com/fischertechnik/txt_demo_c_download/blob/master/TransferArea.md#typical-templates-for-start-reset)Typical templates for start reset

```
Set 'cnt_reset_cmd_id' in output structure
```
```C
///

/// Start the reset action for the counter of a C-input [shmId:idx]
////// Master or slave TXT controller
/// Which counter
/// Succes or Error
FtErrors StartCounterReset(ShmIfId_TXT shmId, Counter idx)
{
	if (idx < 0 || idx >= ftIF2013_nCounters)
		return FTLIB_ERR_INVALID_PARAM;
	FTX1_INPUT* pIn = &FishX1Transfer[shmId].ftX1in;
	FTX1_OUTPUT* pOut = &FishX1Transfer[shmId].ftX1out;
	pOut->cnt_reset_cmd_id[idx]++;
	pIn->cnt_resetted[cntId] = 0; //user need to reset this one
	return FTLIB_ERR_SUCCESS;
}
```

#### [](https://github.com/fischertechnik/txt_demo_c_download/blob/master/TransferArea.md#typical-templates-for-is-reset-ready)Typical templates for is reset ready

```C	
/// <summary>
/// Has the counter of a C-input [shmId:idx] been resetted?
/// </summary>
/// <param name="shmId">Master or slave TXT controller</param>
/// <param name="idx">Which counter</param>
/// <returns>Reset is ready</returns>
bool IsCntResetReady(ShmIfId_TXT shmId, Counter idx)
{	
	FTX1_INPUT* pIn = &FishX1Transfer[shmId].ftX1in;
	FTX1_OUTPUT* pOut = &FishX1Transfer[shmId].ftX1out;
	if (idx < 0 || idx >= ftIF2013_nCounters) {
		ftLog::Log(LOGERR, "IsCntResetReady error, Invalid C index (%d:%d) ", shmId, idx);
		return false;
	}
	bool CntReady1 = pIn->cnt_resetted[cntIdx] == 1;
	return CntReady1;
}

```

or
```C
...
bool CntReady1 = pIn->cnt_reset_cmd_id[idx]==pOut->cnt_reset_cmd_id[idx]);
```
### TA04 `_TXT_SPECIAL_OUTPUTS`
TXT output functionality like the sound interface and the LED.
 
```C
//new firmware 4.1.6
typedef struct _TXT_SPECIAL_OUTPUTS
{
	// Id of sound command - incremented whenever a new command is sent
	UINT16  u16SoundCmdId;
	// Index of the sound to play - 0 means stop sound
	UINT16  u16SoundIndex;
	// Repeat count for playing sound
	UINT16  u16SoundRepeat;

	// LED color (start button)
	UINT8 u8LEDColorR;  //? Is not active in the remote mode (on-line)
	UINT8 u8LEDColorG;  //?Is not active in the remote mode (on-line)
	UINT8 u8LEDColorB; //?Is not active in the remote mode (on-line)
} TXT_SPECIAL_OUTPUTS;
```

#### Typical templates for the sound method
```C
/// <summary>
/// activate the sound
/// </summary>
/// <param name="shmId">Master or slave TXT controller</param>
/// <param name="index">Index of the sound file </param>
/// <param name="repeat"></param>
/// <returns></returns>
FtErrors SetSound(ShmIfId_TXT shmId, UINT16 index, UINT16 repeat) {
	FTX1_INPUT* pIn = &FishX1Transfer[shmId].ftX1in;
	TXT_SPECIAL_OUTPUTS* pOut = &FishX1Transfer[shmId].sTxtOutputs;
	//  set 'cnt_reset_cmd_id' in output structure
	pOut->u16SoundIndex=index;
	pOut->u16SoundRepeat = repeat;
	pOut->u16SoundCmdId++ ;
	return FTLIB_ERR_SUCCESS;
}


/// <summary>
/// Check if the activated sound has finished
/// </summary>
/// <param name="shmId">Master or slave TXT controller</param>
/// <returns></returns>
bool IsSoundReady(ShmIfId_TXT shmId) {
	TXT_SPECIAL_INPUTS * pIn = &FishX1Transfer[shmId].sTxtInputs;
	TXT_SPECIAL_OUTPUTS* pOut = &FishX1Transfer[shmId].sTxtOutputs;
	bool res = pOut->u16SoundCmdId == pIn->u16SoundCmdId;
	
	return res;
}
```




### TA05 `_TXT_SPECIAL_INPUTS`

```C
//new firmware 4.1.6
typedef struct _TXT_SPECIAL_INPUTS
{
	// Supply voltage
	UINT16  u16TxtPower;    //not available in the online use
	// Processor temperature
	UINT16  u16TxtTemp;      //not available in the online use
	// Reference voltage
	UINT16  u16TxtRef;      //not available in the online use
	// ??
	UINT16  u16TxtVB;      //not available in the online use

	// Data from the IR-Inputs
	// [IR_RECEIVER_IDX_ALL_DATA]:IR Data for all receivers
	// [IR_RECEIVER_IDX_OFF_OFF]: IR Data for receivers with SW1=0  SW2=0
	// [IR_RECEIVER_IDX_OFF_ON]:  IR Data for receivers with SW1=0  SW2=1
	// [IR_RECEIVER_IDX_ON_OFF]:  IR Data for receivers with SW1=1  SW2=0
	// [IR_RECEIVER_IDX_ON_ON]:   IR Data for receivers with SW1=1  SW2=1 
	KE_IR_INPUT_V01     sIrInput[IZ_IR_RECEIVER + 1];

	// Id of sound command - set to sTxtInputs.u16SoundCmdId if firmware finished processing the command
	UINT16  u16SoundCmdId;

	// Date & Time,  the online use this is not the TXT values but the local OS values
	UINT16  u16Sec;
	UINT16  u16Min;
	UINT16  u16Hour24;
	UINT16  u16Hour12;
	UINT16  u16PmFlag;          // 1 = PM Time
	UINT16  u16MDay;            // Day of Month (Range 1..31)
	UINT16  u16Month;
	UINT16  u16Year;
	UINT16  u16WDay;            // Week Day (Range 0..6 or 1..7 ???)

} TXT_SPECIAL_INPUTS;
```

The structure of the IR controller data.
```C
typedef struct  _IR_DATA
{
	INT16   i16JoyLeftX;                // Value of left Joystick X-Axis  [0=middle -15..0..+15]
	UINT16  u16JoyLeftXtoLeft;          // unsigned-Int Value of left Joystick X-Axis from middle to left maximum [0..15]. 
	UINT16  u16JoyLeftXtoRight;         // unsigned-Int Value of left Joystick X-Axis from middle to right maximum [0..15].

	INT16   i16JoyLeftY;                // Value of left Joystick Y-Axis  (0=middle -15..0..+15)
	UINT16  u16JoyLeftYtoForward;       // unsigned-Int Value of left Joystick Y-Axis from middle to forward  maximum [0..15].
	UINT16  u16JoyLeftYtoBackwards;     // unsigned-Int Value of left Joystick Y-Axis from middle to backwards  maximum [0..15].

	INT16   i16JoyRightX;               // Value of right Joystick X-Axis  (0=middle -15..0..+15)
	UINT16  u16JoyRightXtoLeft;         // unsigned-Int Value of right Joystick X-Axis from middle to left  maximum [0..15].
	UINT16  u16JoyRightXtoRight;        // unsigned-Int Value of right Joystick X-Axis from middle to right  maximum [0..15].

	INT16   i16JoyRightY;               // Value of right Joystick Y-Axis  (0=middle -15..0..+15)
	UINT16  u16JoyRightYtoForward;      // unsigned-Int Value of right Joystick Y-Axis from middle to forward  maximum [0..15].
	UINT16  u16JoyRightYtoBackwards;    // unsigned-Int Value of right Joystick Y-Axis from middle to backwards  maximum [0..15].

	UINT16  u16ButtonOn;                // ON-Switch: 1=pressed
	UINT16  u16ButtonOff;               // OFF-Switch: 1=pressed

	UINT16  u16DipSwitch1;              // 1: Switch ON, 0: Switch OFF
	UINT16  u16DipSwitch2;              // 1: Switch ON, 0: Switch OFF
} KE_IR_INPUT_V01;
```

### TA06 `_TXT_SPECIAL_INPUTS_2`
Remarks:
  >  In the remote (on-line)  use, the microphone data is only available in the Compressed Transfer mode.
  
  >  Online mode is the sample rate 10 msec or more.

```C
//new firmware 4.2.4 and 4.4.3
typedef struct _TXT_SPECIAL_INPUTS_2
{
	// Microphone
	INT16  u16MicLin; //the actual value of the microphone, as part of the USB camera (if connected)
	INT16  u16MicLog; //the actual value of the microphone, as part of the USB camera (if connected)
} TXT_SPECIAL_INPUTS_2;
```
#### Typical templates for the microphone methods
```C
/// <summary>
/// Get microphone data
/// </summary>
/// <param name="shmId">Master or slave TXT controller</param>
/// <returns></returns>
UINT16 GetMicLin(ShmIfId_TXT shmId) {
	TXT_SPECIAL_INPUTS_2 * pIn = &FishX1Transfer[shmId].sTxtInputs2;
	UINT16 res = pIn->u16MicLin ;
	return res;

}

/// <summary>
/// Get microphone data compressed(logarithmic
/// </summary>
/// <param name="shmId">master or slave controller</param>
/// <returns></returns>
UINT16 GetMicLog(ShmIfId_TXT shmId) {
	
	TXT_SPECIAL_INPUTS_2* pIn = &FishX1Transfer[shmId].sTxtInputs2;
	UINT16 res = pIn->u16MicLog;
	return res;
}
```

# Document history 
- 2020-08-14 CvL 466.1.7 
 Add templates about the C-inputs
- 2020-08-08 CvL 466.1.6 
- © 2020  ing. C. van Leeuwen Btw. (TesCaWeb.nl) Enschede Netherlands
- Original from: on-line training SLI-programming by C .van Leeuwen<br/>



