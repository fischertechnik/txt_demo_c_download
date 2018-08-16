/**********************************************************
 *  Compiler:   gcc / g++
 * 
 *  Demonstration of working with the Transfer Area
 *  Connections
 *  M1: Encoder Motor with Signal to Clock C1 Inputs
 * 
 *  Demo_02:
 *  - Start Transfer with StartTxtDownloadProg()
 *  - Gets the Address from the Transfer Area with GetKeLibTransferAreaMainAddress()
 *  - Switch Encoder Motor on M1 for 2 turns on and drive back
 **********************************************************/
#include <stdio.h>          // for printf()
#include <unistd.h>         // for sleep()

#include "KeLibTxtDl.h"     // TXT Lib
#include "FtShmem.h"        // TXT Transfer Area

// Common debugging stuff for RoboProLib
unsigned int DebugFlags;
FILE *DebugFile;


int main(void) 
{
	FISH_X1_TRANSFER    *pTArea;
	if (StartTxtDownloadProg() == KELIB_ERROR_NONE)
	{
		pTArea = GetKeLibTransferAreaMainAddress();
		if (pTArea)
		{   // It's a real pointer

			// Switch M1 - Encoder Motor on for 2 turns
			// Note: the range of the motor duty cycle values is 0..512

			// Step 1: Switch Motor on (with a distance from 127 Clocks for 2 turns)
			pTArea->ftX1out.distance[0] = 127;                  // Distance to drive Motor 1 [0]
			pTArea->ftX1out.motor_ex_cmd_id[0]++;               // Set new Distance Value for Motor 1 [0]
			pTArea->ftX1out.duty[0] = 512;                      // Switch Motor 1 ( O1 [0] ) on with PWM Value 512 (= max speed)
			pTArea->ftX1out.duty[1] = 0;                        // Switch Motor 1 ( O2 [1] ) with minus

			while (pTArea->ftX1in.motor_ex_cmd_id[0] < pTArea->ftX1out.motor_ex_cmd_id[0])
			{
				printf("1:OutExCmd: %d  InExCmd: %d  Counter: %d  \n",
						pTArea->ftX1out.motor_ex_cmd_id[0], pTArea->ftX1in.motor_ex_cmd_id[0], pTArea->ftX1in.counter[0]);
			};

			printf("2:OutExCmd: %d  InExCmd: %d  Counter: %d  \n",
					pTArea->ftX1out.motor_ex_cmd_id[0], pTArea->ftX1in.motor_ex_cmd_id[0], pTArea->ftX1in.counter[0]);
			sleep(1);

			// Step 3: Run back to zero
			pTArea->ftX1out.distance[0] = pTArea->ftX1in.counter[0];    // Distance to go back
			pTArea->ftX1out.motor_ex_cmd_id[0]++;                       // Set new Distance Value for Motor 1 [0]
			pTArea->ftX1out.duty[0] = 0;                                // Switch Motor 1 ( O1 [0] ) with minus
			pTArea->ftX1out.duty[1] = 512;                              // Switch Motor 1 ( O2 [1] ) on with PWM Value 512 (= max speed)

			while (pTArea->ftX1in.motor_ex_cmd_id[0] < pTArea->ftX1out.motor_ex_cmd_id[0])
			{
				printf("3:OutExCmd: %d  InExCmd: %d  Counter: %d  \n",
						pTArea->ftX1out.motor_ex_cmd_id[0], pTArea->ftX1in.motor_ex_cmd_id[0], pTArea->ftX1in.counter[0]);
			};

			printf("4:OutExCmd: %d  InExCmd: %d  Counter: %d  \n",
					pTArea->ftX1out.motor_ex_cmd_id[0], pTArea->ftX1in.motor_ex_cmd_id[0], pTArea->ftX1in.counter[0]);
		}
		StopTxtDownloadProg();
	}
	return 0;
}
