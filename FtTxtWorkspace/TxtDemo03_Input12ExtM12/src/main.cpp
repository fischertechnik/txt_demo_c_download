/**********************************************************
 *  Compiler:   gcc / g++
 *
 *  Demonstration of working with the Transfer Area
 *  Connections
 *  I1: Switch
 *  I2: Ultrasonic Sensor
 *  (same on EXT-Module if present)
 *
 *  Demo_03:
 *  - Start Transfer with StartTxtDownloadProg()
 *  - Gets the Address from the Transfer Area with GetKeLibTransferAreaMainAddress()
 *  - Setup the Inputs-Config and save the new setting with incrementing the variable "config_id"
 *  - runs in a loop for 10 seconds:
 *    read Inputs I1 and I2, set Motor Output M1 and M2
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
    uint32_t            u32Timer;
    if (StartTxtDownloadProg() == KELIB_ERROR_NONE)
    {
        pTArea = GetKeLibTransferAreaMainAddress();
        if (pTArea)
        {   // It's a real pointer

            // first setup the inputs
            // I1 = Digital Switch
            // I2 = Ultrasonic
            pTArea->ftX1config.uni[0].mode = MODE_R;      // Input 1 = Digital Switch with PullUp resistor
            pTArea->ftX1config.uni[0].digital = 1;

            pTArea->ftX1config.uni[1].mode = MODE_ULTRASONIC;
            pTArea->ftX1config.uni[1].digital = 0;       // Input 2 = Ultrasonic Input and Analog Values
            pTArea->ftX1state.config_id ++;              // Save the new Setup


            // setup Extension Interface (no problem if not present)
            // note: "(pTArea + 1)" is the pointer to the EXT-1 Transfer Area
            (pTArea + 1)->ftX1config.uni[0].mode = MODE_R;      // Input 1 = Voltage and Digital Switch
            (pTArea + 1)->ftX1config.uni[0].digital = 1;

            (pTArea + 1)->ftX1config.uni[1].mode = MODE_ULTRASONIC;
            (pTArea + 1)->ftX1config.uni[1].digital = 0;       // Input 2 = Ultrasonic Input and Analog Values
            (pTArea + 1)->ftX1state.config_id ++;              // Save the new Setup

            // Loop for 10 seconds
            for (u32Timer = 0; pTArea->IFTimer.Timer10ms < 1000; u32Timer++)
            {   // Set output 0 (O1) depending on input 0 [I1]
                // Note: for setting M1 to reverse direction, O2 (ftX1out.duty[1]) must be set
                // Note: the range of the motor duty cycle values is 0..512

                if (pTArea->ftX1in.uni[0])
                {   // Input I1 on Master Interface is "1"
                    pTArea->ftX1out.duty[0] = 512;
                }
                else
                {   // Input I1 on Master Interface is "0"
                    pTArea->ftX1out.duty[0] = 0;
                }

                // The Speed of M2 depends on the Distance from Ultrasonic Sensor
                // in the Rage 0..102cm
                if (pTArea->ftX1in.uni[1] <= 102)
                {   // Distance <= 102cm
                    pTArea->ftX1out.duty[2] = pTArea->ftX1in.uni[1] * 5;    // 0..102cm with "*5" to speed 0..510
                }
                else
                {
                    pTArea->ftX1out.duty[2] = 512;
                }

                // same on Extension Interface (no problem if not present)
                // note: "(pTArea + 1)" ist the pointer to the EXT-1 Transfer Area
                if ((pTArea + 1)->ftX1in.uni[0])
                {   // Input I1 on Master Interface is "1"
                    (pTArea + 1)->ftX1out.duty[0] = 512;
                }
                else
                {   // Input I1 on Master Interface is "0"
                    (pTArea + 1)->ftX1out.duty[0] = 0;
                }

                // The Speed of M2 depends on the Distance from Ultrasonic Sensor
                // in the Rage 0..102cm
                if ((pTArea + 1)->ftX1in.uni[1] <= 102)
                {   // Distance <= 102cm
                    (pTArea + 1)->ftX1out.duty[2] = (pTArea + 1)->ftX1in.uni[1] * 5;    // 0..102cm with "*5" to speed 0..510
                }
                else
                {
                    (pTArea + 1)->ftX1out.duty[2] = 512;
                }
                usleep(10000);                  // wait 10 ms
            }
        }
        StopTxtDownloadProg();
    }
	return 0;
}
