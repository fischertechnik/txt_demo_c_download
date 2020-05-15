/**********************************************************
 *  Compiler:   gcc / g++
 * 
 *  Demonstration of working with the Transfer Area
 *
 *  Connections:
 *  I1: Color sensor
 * 
 *  Demo_01:
 *  - Start Transfer with StartTxtDownloadProg()
 *  - Gets the Address from the Transfer Area with GetKeLibTransferAreaMainAddress()
 *  - printf Input1 MODE_U
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
			while(true) {
				pTArea->ftX1config.uni[0].mode = MODE_U;
				pTArea->ftX1config.uni[0].digital = 0;
				pTArea->ftX1state.config_id ++;

				usleep(50000);

				printf("%d\n", pTArea->ftX1in.uni[0]);
			}
		}
		StopTxtDownloadProg();
	}
	return 0;
}
