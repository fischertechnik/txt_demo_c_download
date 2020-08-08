<!-- TOC depthFrom:1 depthTo:6 withLinks:1 updateOnSave:1 orderedList:0 -->

- [The fischertechnik transfer area (TA)](#the-fischertechnik-transfer-area-ta)
	- [Introduction](#introduction)
	- [Remarks](#remarks)
			- [Typical structure of a basic local program.](#typical-structure-of-a-basic-local-program)
			- [Typical structure of a local program which is using the `TransferAreaCallbackFunction` callback function. <br/>](#typical-structure-of-a-local-program-which-is-using-the-transferareacallbackfunction-callback-function-br)
	- [The TA main structure](#the-ta-main-structure)
		- [source of information](#source-of-information)
		- [The complete TA for a TXT controller](#the-complete-ta-for-a-txt-controller)
		- [ftX1config](#ftx1config)
			- [A template for a function to set the Motor configuration](#a-template-for-a-function-to-set-the-motor-configuration)
			- [A template for a  function to set the Universal Input configuration](#a-template-for-a-function-to-set-the-universal-input-configuration)
		- [ftX1output](#ftx1output)
			- [typical use for normal motors](#typical-use-for-normal-motors)
			- [template for a higher level motor function](#template-for-a-higher-level-motor-function)
			- [typical use for enhanced motors](#typical-use-for-enhanced-motors)
			- [typical use for enhanced motors, to inspect if the black box has ended](#typical-use-for-enhanced-motors-to-inspect-if-the-black-box-has-ended)
		- [ftX1input](#ftx1input)
			- [template for a read value for a certain Universal Input.](#template-for-a-read-value-for-a-certain-universal-input)
		- [_TXT_SPECIAL_OUTPUTS](#txtspecialoutputs)
			- [Typical templates for the sound method](#typical-templates-for-the-sound-method)
		- [_TXT_SPECIAL_INPUTS](#txtspecialinputs)
		- [_TXT_SPECIAL_INPUTS_2](#txtspecialinputs2)
			- [Typical templates for the microphone methods](#typical-templates-for-the-microphone-methods)
- [Document history](#document-history)

<!-- /TOC -->

# The fischertechnik transfer area (TA)
> Remark: document is under development.
   
## Introduction

Since the Robo-interface exist a description of the fischertechnik transfer area (TA). In fact it is a shared memory area which take care of the communication between the user program and the fischertechnik actuator/sensor logic. Because it is a collection of bytes, it could also be transmitted over a connection, like USB, BlueTooth or IP,  with another device. The structure of the TA has been extended with the arrivals of the fischertechnik TX-C and the TXT controller. However the principal is still the same.<br/>
In this document we will explain the basics of "How to use the TA?" at the program site.<br/>
Only the Motor/Output (actuators) and Universal Inputs (sensors) will be discussed. With this information the user would be able to understand the other parts like: sound, microphone, IR-controller device, Counter inputs.<br/>
The reader is expected to have reasonable knowledge of C and C ++. There is enough information on the internet about the possibilities and use of C11 ++ and C14 ++ and also to have very good knowledge of RoboPro elements level 4/5 and experience with it.

## Remarks
> The TXT is not using all the TA entries.

> The enhance Motor control is a black box which runs as part of the fischertechnik actuator/sensor logic.
  The user program can only send commands to this black box and wait until it is ready. This black box is using a Motor in combination with a Counter.
  
> A actuator output can be configurated as (full bridge device) Mx motor output or as two (half bridge) Ox*2, Ox*2+1 outputs. (See also RoboPro)   

#### Typical structure of a basic local program.   
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
				//You functional logic
			};
		}
		StopTxtDownloadProg();
	}
	return 0;
}
```

#### Typical structure of a local program which is using the `TransferAreaCallbackFunction` callback function. <br/>
See also the KeLibTxtDl.h.
  
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
        //Let the callback do his work, keep the main program active.
            while (u16CountInput < 10)
            {   // main Application 
                // No polling the inputs
                usleep(5000);
            }
        }
        StopTxtDownloadProg();
    }
	return 0;
}
// Callback Function. 
// This is called between receiving inputs and sending outputs to TXT the hardware
bool TransferAreaCallbackFunction(FISH_X1_TRANSFER *pTransArea, int i32NrAreas)
{   // ============================================================

    // Your program logic.
    
    return true;        // if you return FALSE, then the Hardware is stopped !!!
}

```

## The TA main structure

### source of information

- [See also for the online programming](https://github.com/fischertechnik/txt_demo_c_online/blob/master/SolutionTxtLib/include/FtShmemTxt.h)
- [See also for the local and SLI programming](https://github.com/fischertechnik/txt_demo_c_download/blob/master/FtTxtWorkspace/TxtDeps/Txt_Includes/FtShmem.h)
- [See also for the method examples](https://github.com/fischertechnik/txt_demo_c_online/blob/master/SolutionTxtApps/TestProj02/Main.cpp)

### The complete TA for a TXT controller
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
In the programming you can have access to this structure by:
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
 FTX1_CONFIG* MftX1config = & TransArea[ShmIfId_TXT::LOCAL_IO].ftX1config;
 FTX1_STATE*  MftX1state = & TransArea[ShmIfId_TXT::LOCAL_IO].ftX1state;
```

### ftX1config
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

#### A template for a function to set the Motor configuration
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
#### A template for a  function to set the Universal Input configuration
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

### ftX1output
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
#### typical use for normal motors
```C
//M1 CW
TransArea[ShmIfId_TXT::LOCAL_IO].ftX1out.duty[2 * Motor::M1] = 0;
TransArea[ShmIfId_TXT::LOCAL_IO].ftX1out.duty[2 * Motor::M1 + 1] = 512;//range 0..512
//M2 CCW
TransArea[ShmIfId_TXT::LOCAL_IO].ftX1out.duty[2 * Motor::M2] = 512;//range 0..512
TransArea[ShmIfId_TXT::LOCAL_IO].ftX1out.duty[2 * Motor::M2 + 1] =0 ;
```

#### template for a higher level motor function

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

#### typical use for enhanced motors
```C  
TransArea[ShmIfId_TXT::LOCAL_IO].ftX1out.duty[2 * Motor::M1] = 256;
TransArea[ShmIfId_TXT::LOCAL_IO].ftX1out.duty[2 * Motor::M1 + 1] = 0;

TransArea[ShmIfId_TXT::LOCAL_IO].ftX1out.duty[2 * Motor::M2]  = 0; 
TransArea[ShmIfId_TXT::LOCAL_IO].ftX1out.duty[2 * Motor::M2 + 1]  = 256;  //
MftX1outDut[2 * IdMotorB + 1] = 0;
TransArea[ShmIfId_TXT::LOCAL_IO].ftX1out.distance[Motor::M1] = 1000;//1000 steps  (C1)
TransArea[ShmIfId_TXT::LOCAL_IO].ftX1out.distance[Motor::M2] = 1000;//1000 steps  (C2)
TransArea[ShmIfId_TXT::LOCAL_IO].ftX1out.master[Motor::M2] = Motor::M1+1// , M2 is the slave, the master for M2 is M1
TransArea[ShmIfId_TXT::LOCAL_IO].ftX1out.master[Motor::M1] = 0//M1 is the master
//Start, 
TransArea[ShmIfId_TXT::LOCAL_IO].ftX1in.motor_ex_reached[Motor::M1] = false; //needs to be resetted by the user
TransArea[ShmIfId_TXT::LOCAL_IO].ftX1in.motor_ex_reached[Motor::M2] = false; //needs to be resetted by the user

TransArea[ShmIfId_TXT::LOCAL_IO].ftX1out.motor_ex_cmd_id[Motor::M1]++;
TransArea[ShmIfId_TXT::LOCAL_IO].ftX1out.motor_ex_cmd_id[Motor::M2]++;
``` 

#### typical use for enhanced motors, to inspect if the black box has ended
In fact motor_ex_reached means for example:
`TransArea[ShmIfId_TXT::LOCAL_IO].ftX1out.motor_ex_cmd_id[Motor::M1]==TransArea[ShmIfId_TXT::LOCAL_IO].ftX1in.motor_ex_cmd_id[Motor::M1]`

See ftX1input
```C
if (  
TransArea[ShmIfId_TXT::LOCAL_IO].ftX1in.motor_ex_reached[Motor::M1] &&
TransArea[ShmIfId_TXT::LOCAL_IO].ftX1in.motor_ex_reached[Motor::M2])
{
// Both motors has reached the end, in this case 1000 steps
}
``` 

### ftX1input
In this structure the program reads the values coming from the Universal Inputs and enhance Motor control (including fast Counters). <br/>

It also is used to notify the user that some asynchronous actions has been finished:<br/>
- `cnt_reset_cmd_id` the IoMotor-control informs the user which counter reset action has been finished.<br/> See also the `cnt_reset_cmd_id in` the ftX1out section.

- `motor_ex_cmd_id` the IoMotor-control informs the user which enhance motor action has been finished.<br/> See also the `motor_ex_cmd_id` in the  ftX1out section.
- The `uni` value depends on the `mode` and `digital` configuration of that particular Input.

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


```C


```
#### template for a read value for a certain Universal Input.

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
### _TXT_SPECIAL_OUTPUTS
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




### _TXT_SPECIAL_INPUTS

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

### _TXT_SPECIAL_INPUTS_2
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
- 2020-08-08 CvL 466.1.2 
  © 2020  ing. C. van Leeuwen Btw. (TesCaWeb.nl) Enschede Netherlands
- Original from: on-line training SLI-programming<br/>
  © 2020  ing. C. van Leeuwen Btw. (TesCaWeb.nl) Enschede Netherlands


