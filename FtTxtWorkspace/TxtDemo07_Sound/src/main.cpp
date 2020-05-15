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
			pTArea->sTxtOutputs.u16SoundCmdId = 0;

			int number = 1;
			printf("Starting sound #%d\n", number);
			pTArea->sTxtOutputs.u16SoundIndex = number;
			pTArea->sTxtOutputs.u16SoundRepeat = 0;
			pTArea->sTxtOutputs.u16SoundCmdId++;

			printf("CmdId %d\n",pTArea->sTxtInputs.u16SoundCmdId);
			while(pTArea->sTxtInputs.u16SoundCmdId == 0)
			{
				usleep(10000);
			}
			printf("CmdId %d\n",pTArea->sTxtInputs.u16SoundCmdId);


			//more info
			printf("Up:%dmV Uref:%d  Ub:%d\n",pTArea->sTxtInputs.u16TxtPower,pTArea->sTxtInputs.u16TxtRef,pTArea->sTxtInputs.u16TxtVB);
			printf("T:%d\n",pTArea->sTxtInputs.u16TxtTemp);

			printf("Done\n");
		}
		StopTxtDownloadProg();
	}
	return 0;
}
