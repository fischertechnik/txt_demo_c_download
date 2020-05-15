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
		{
			for(int i = 0; i < 10; i++)
			{
				pTArea->ftX1out.duty[0] = 512;                      // Switch Motor 1 ( O1 [0] ) on with PWM Value 512 (= max speed)
				sleep(1);
				pTArea->ftX1out.duty[0] = 0;                      // Switch Motor 1 ( O1 [0] ) on with PWM Value 512 (= max speed)
				sleep(1);
			}
		}
		StopTxtDownloadProg();
	}
	return 0;
}
