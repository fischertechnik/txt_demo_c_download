/**********************************************************
 *  Compiler:   gcc / g++
 * 
 *  Demonstration of working with I2C
 *  Connections
 *  I1: Switch
 *  I2C: PCF8574 with LED's on the Outputs
 * 
 *  Demo_04 - testing I2C
 *  - Start Transfer with StartTxtDownloadProg()
 *  - Gets the Address from the Transfer Area with GetKeLibTransferAreaMainAddress()
 *  - Send on every switch Stroke on I1 a Databyte to the I2C Bus
 **********************************************************/
#include <stdio.h>          // for printf()
#include <string.h>         // for memset()
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
bool        bNewKeystroke;
    
 
int main(void) 
{
    FISH_X1_TRANSFER    *pTArea;
    uint8_t     u8WriteData[128];
    uint8_t     u8ReadData[128];
    uint16_t    u16Adr,
                u16AnzWr;
    uint32_t    u32RetValue;
    uint8_t     u8Data;

    if (StartTxtDownloadProg() == KELIB_ERROR_NONE)
    {
        pTArea = GetKeLibTransferAreaMainAddress();
        if (pTArea)
        {   
            u16LastState = pTArea->ftX1in.uni[0];
            u16CountState = 0;
            u16CountInput = 0;
            u8Data = 0x00;

            // Start using Callback Function
            SetTransferAreaCompleteCallback(TransferAreaCallbackFunction);
            
            InitI2C();
            
            bNewKeystroke = false;
        
            while (u16CountInput < 10)
            {   // main Application
            
                if (bNewKeystroke)
                {
                    bNewKeystroke = false;
            
                    memset(u8WriteData, 0, sizeof(u8WriteData));
                    memset(u8ReadData, 0, sizeof(u8ReadData));
                    
                    u16Adr = 0x20;
                    u8WriteData[0] = u8Data++;      // Data for output
                    u16AnzWr = 1;
                    
                    // Write
                    //                                Adr    Anz Wr      Wr-Data   Anz Read   Rd-Data   Speed
                    u32RetValue = KeLibI2cTransfer(u16Adr, u16AnzWr, u8WriteData,         0,        0,  I2C_SPEED_100_KHZ);          
                }
                
                usleep(5000);
            }
        }
        StopTxtDownloadProg();
    }
	return 0;
}


// Callback Function. 
// This is called between receiving inputs and sending outputs to the TXT hardware
bool TransferAreaCallbackFunction(FISH_X1_TRANSFER *pTransArea, int i32NrAreas)
{   
    // debouncing input I1 and count 
    if (pTransArea->ftX1in.uni[0] == u16LastState)
    { 
        u16CountState++;
        if (u16CountState == 10)
        {   
            if (u16LastState)
            {
                u16CountInput++;
                bNewKeystroke = true;
            }
        }
    }
    else
    {   // new State
        u16LastState = pTransArea->ftX1in.uni[0];
        u16CountState = 0;
    }
    
    return true;        // if you return FALSE, then the hardware update is stopped !!!
}
