#include <stdio.h>          // for printf()
#include <unistd.h>         // for sleep()
#include <time.h>

#include "KeLibTxtDl.h"     // TXT Lib
#include "FtShmem.h"        // TXT Transfer Area

// Common debugging stuff for RoboProLib
unsigned int DebugFlags;
FILE *DebugFile;

double now_s() {
	//SPDLOG_LOGGER_TRACE(spdlog::get("console"), "getnowtimestamp");
	struct timespec ts;
	timespec_get(&ts, TIME_UTC);
	struct timespec {
		time_t   tv_sec;        /* seconds */
		long     tv_nsec;       /* nanoseconds */
	};
	time_t epch = ts.tv_sec;
	double ms = ts.tv_nsec/1000000000.;
	//SPDLOG_LOGGER_DEBUG(spdlog::get("console"), "epch:{} ms:{}", epch, ms);
	return (double)epch+ms;
}

int main(void) 
{
	FISH_X1_TRANSFER    *pTArea;
	if (StartTxtDownloadProg() == KELIB_ERROR_NONE)
	{
		pTArea = GetKeLibTransferAreaMainAddress();
		if (pTArea)
		{
			printf("init1: %f\n", now_s());

			//Config Input S1
            pTArea->ftX1config.uni[0].mode = MODE_R; // Input 1 = Digital Switch with PullUp resistor
            pTArea->ftX1config.uni[0].digital = 1;
            pTArea->ftX1state.config_id++;
			usleep(1000);

			// Switch Motor M1 on
			pTArea->ftX1out.duty[0] = 512;
			pTArea->ftX1out.duty[1] = 0;
			usleep(1000);
			printf("motor start: %f\n", now_s());

			volatile double t1;

			//while (pTArea->ftX1in.motor_ex_cmd_id[0] < pTArea->ftX1out.motor_ex_cmd_id[0])
			while(true)
			{
				//printf("1:OutExCmd: %d  InExCmd: %d  Counter: %d  \n",
				//		pTArea->ftX1out.motor_ex_cmd_id[0], pTArea->ftX1in.motor_ex_cmd_id[0], pTArea->ftX1in.counter[0]);

				if (pTArea->ftX1in.uni[0]) {
					t1 = now_s();
					printf("\nref switch on: %f\n", t1);
					break;
				}
				usleep(1000);
			};

			//printf("2:OutExCmd: %d  InExCmd: %d  Counter: %d  \n",
			//		pTArea->ftX1out.motor_ex_cmd_id[0], pTArea->ftX1in.motor_ex_cmd_id[0], pTArea->ftX1in.counter[0]);

			//STOP
			pTArea->ftX1out.duty[0] = 0;
			pTArea->ftX1out.duty[1] = 0;
			usleep(1000);

			volatile double t2 = now_s();
			printf("motor stopped %f\n", t2);

			printf("diff %f s\n", (t2-t1));

			volatile double _t1 = now_s();
			printf("\ntest 1s start %f\n", _t1);
			sleep(1);
			volatile double _t2 = now_s();
			printf("test 1s end %f\n", _t2);
			printf("test 1s diff %f s\n", (_t2-_t1));
		}
		StopTxtDownloadProg();
	}
	return 0;
}
