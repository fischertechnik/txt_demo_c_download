/**********************************************************
 *  Compiler:   gcc / g++
 * 
 *  Demonstration of working with the Transfer Area: using CallBack-Function when Transfer-Area is updated
 *  Connections
 *  I1: Switch
 *  M1: Motor
 * 
 *  Demo_05 - using Callback-Function
 *  - Start Transfer with StartTxtDownloadProg()
 *  - Gets the Address from the Transfer Area with GetKeLibTransferAreaMainAddress()
 *  - Setup the Inputs-Config and save the new setting with incrementing the variable "config_id"
 *  - waits for 10 Keystrokes an Input 1 / using Callback Function - No polling the Inputs
 **********************************************************/
#include <stdio.h>          // for printf()
#include <unistd.h>         // for sleep()
  
#include "KeLibTxtDl.h"     // TXT Lib
#include "FtShmem.h"        // TXT Transfer Area

// Common debugging stuff for RoboProLib
unsigned int DebugFlags;
FILE *DebugFile;

bool TransferAreaCallbackFunction(struct shm_if_s *pTransArea, int i32NrAreas);


uint16_t    u16LastState;
uint16_t    u16CountState;
uint32_t    u16CountInput;

 
int main(void) 
{
    FISH_X1_TRANSFER    *pTArea;
    if (StartTxtDownloadProg() == KELIB_ERROR_NONE)
    {
        pTArea = GetKeLibTransferAreaMainAddress();
        if (pTArea)
        {   
            u16LastState = pTArea->ftX1in.uni[0];
            u16CountState = 0;
            u16CountInput = 0;

            // Start using Callback Function
            SetTransferAreaCompleteCallback(TransferAreaCallbackFunction);
        
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
//unsigned int DebugFlags;
//FILE *DebugFile;
    // debouncing input I1 and count 
    if (pTransArea->ftX1in.uni[0] == u16LastState)
    { 
        u16CountState++;
        if (u16CountState == 10)
        {   
            if (u16LastState)
            {
                u16CountInput++;
            }
        }
    }
    else
    {   // new State
        u16LastState = pTransArea->ftX1in.uni[0];
        u16CountState = 0;
    }
    
    
    // set the Motor M1 Output
    if (pTransArea->ftX1in.uni[0])
    {   // Input I1 on Master Interface is "1"
        pTransArea->ftX1out.duty[0] = 512;
    }
    else
    {   // Input I1 on Master Interface is "0"
        pTransArea->ftX1out.duty[0] = 0;
    }
    
    return true;        // if you return FALSE, then the Hardware is stopped !!!
}
