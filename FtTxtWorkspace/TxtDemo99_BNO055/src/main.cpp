/*!
 *  \copyright (c) 2019-2020 fischertechnik
 *  \version   1.1.1.1
 *  \file main.cpp
 *  \brief BNO055 basics
 *  @remark
 *  2020-05-27<br/>
 *  There was a sematic error `spdlog::stdout_color_st("console")`<br/>
 *  this had to do with the Indexer of Eclipse:<br/>
 *    Clean your project (Project -> Clean)<br/>
 *    Reindex files (Project -> C/C++ Index -> Rebuild)<br/>
 *    Rebuild your project (Project -> Build All<br/>
 *  [see also](https://stackoverflow.com/questions/13021594/eclipse-giving-me-invalid-arguments-candidates-are-void-memsetvoid-int)<br/>
 */
/*!
  \def SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
  Sets the compilation level of SPDLOG.
*/
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include <stdio.h>          // for printf()
#include "KeLibTxtDl.h"     // TXT Lib
#include "FtShmem.h"        // TXT Transfer Area see KeLib header
/*!
  \brief Includes for the spdlog
*/
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/async.h"


#include <stdio.h>          // for printf()
#include <string.h>         // for memset()
#include <cstring>
#include <unistd.h>         // for sleep()
#include <cmath>			// for pow()

#include <iostream>
#include <chrono>

using namespace std;

extern "C" {
#include "bno055.h"
}


unsigned int DebugFlags;
FILE *DebugFile;

FISH_X1_TRANSFER* pTArea = NULL;

// Callback Function.
// This is called between receiving inputs and sending outputs to the TXT hardware
bool TransferAreaCallbackFunction(FISH_X1_TRANSFER *pTransArea, int i32NrAreas)
{	//10 ms cycle
	//LEDs
	if (pTransArea) {
		//
	}
	usleep(5000);
    return true;        // if you return FALSE, then the hardware update is stopped !!!
}

void user_delay_ms(uint32_t period)
{
	//printf("user_delay_ms %d\n", period);
    usleep(1000*period); // wait ms
}

int8_t user_i2c_read(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint8_t len)
{
    int8_t rslt = 0; /* Return 0 for Success, non-zero for failure */
    //Adr, Anz Wr, Wr-Data, Anz Read, Rd-Data, Speed
    uint32_t u32RetValue = KeLibI2cTransfer(dev_id, 1, &reg_addr, len, reg_data, I2C_SPEED_400_KHZ);
	//printf("%x user_i2c_read %x %x %d %d\n", u32RetValue, dev_id, reg_addr, reg_data[0], len);
    rslt = (u32RetValue==0?0:-1); //0=success, -1 error
    return rslt;
}

int8_t user_i2c_write(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint8_t len)
{
    int8_t rslt = 0; /* Return 0 for Success, non-zero for failure */
    uint8_t u8WriteData[len+1];
    u8WriteData[0] = reg_addr;
    for(int i=0; i < len+1; i++) {
    	u8WriteData[i+1] = reg_data[i];
    }
    //Adr, Anz Wr, Wr-Data, Anz Read, Rd-Data, Speed
    uint32_t u32RetValue = KeLibI2cTransfer(dev_id, len+1, u8WriteData, 0, 0, I2C_SPEED_400_KHZ);
	//printf("%x user_i2c_write %x %x %d %d\n", u32RetValue, dev_id, reg_addr, reg_data[0], len);
    rslt = (u32RetValue==0?0:-1); //0=success, -1 error
    return rslt;
}

/*********read raw accel data***********/
struct bno055_accel_t accel_xyz;
/*********read raw mag data***********/
struct bno055_mag_t mag_xyz;
/***********read raw gyro data***********/
struct bno055_gyro_t gyro_xyz;
/*************read raw Euler data************/
struct bno055_euler_t euler_hrp;
/************read raw quaternion data**************/
struct bno055_quaternion_t quaternion_wxyz;
/************read raw linear acceleration data***********/
struct bno055_linear_accel_t linear_acce_xyz;
/*****************read raw gravity sensor data****************/
struct bno055_gravity_t gravity_xyz;
/*************read accel converted data***************/
struct bno055_accel_double_t d_accel_xyz;
/******************read mag converted data********************/
struct bno055_mag_double_t d_mag_xyz;
/*****************read gyro converted data************************/
struct bno055_gyro_double_t d_gyro_xyz;
/*******************read euler converted data*******************/
struct bno055_euler_double_t d_euler_hpr;
/*********read linear acceleration converted data**********/
struct bno055_linear_accel_double_t d_linear_accel_xyz;
/********************Gravity converted data**********************/
struct bno055_gravity_double_t d_gravity_xyz;

/*** temp ***/
s8 temp_s8;
double temp_celcius;


void bno055_raw_data_print(void)
{
	/*********read raw accel data***********/
	std::cout << "raw accel data: " << accel_xyz.x
			<< " " << accel_xyz.y
			<< " " << accel_xyz.z
			<< std::endl;
	/*********read raw mag data***********/
	std::cout << "raw mag data: " << mag_xyz.x
			<< " " << mag_xyz.y
			<< " " << mag_xyz.z
			<< std::endl;
	/***********read raw gyro data***********/
	std::cout << "raw gyro data: " << gyro_xyz.x
			<< " " << gyro_xyz.y
			<< " " << gyro_xyz.z
			<< std::endl;
	/*************read raw Euler data************/
	std::cout << "raw Euler data: " << euler_hrp.h
			<< " " << euler_hrp.r
			<< " " << euler_hrp.p
			<< std::endl;
	/************read raw quaternion data**************/
	std::cout << "raw quaternion data: " << quaternion_wxyz.w
			<< " " << quaternion_wxyz.x
			<< " " << quaternion_wxyz.y
			<< " " << quaternion_wxyz.z
			<< std::endl;
	/************read raw linear acceleration data***********/
	std::cout << "raw linear acceleration data: " << linear_acce_xyz.x
			<< " " << linear_acce_xyz.y
			<< " " << linear_acce_xyz.z
			<< std::endl;
	/*****************read raw gravity sensor data****************/
	std::cout << "raw gravity sensor data: " << gravity_xyz.x
			<< " " << gravity_xyz.y
			<< " " << gravity_xyz.z
			<< std::endl;
	/*** raw temp ***/
	std::cout << "raw temp: " << (int)temp_s8
			<< std::endl;
}

void bno055_data_print(void)
{
	/*************read accel converted data***************/
	std::cout << "accel converted data: " << d_accel_xyz.x
			<< " " << d_accel_xyz.y
			<< " " << d_accel_xyz.z
			<< std::endl;
	/******************read mag converted data********************/
	std::cout << "mag converted data: " << d_mag_xyz.x
			<< " " << d_mag_xyz.y
			<< " " << d_mag_xyz.z
			<< std::endl;
	/*****************read gyro converted data************************/
	std::cout << "gyro converted data: " << d_gyro_xyz.x
			<< " " << d_gyro_xyz.y
			<< " " << d_gyro_xyz.z
			<< std::endl;
	/*******************read euler converted data*******************/
	std::cout << "euler converted data: " << d_euler_hpr.h
			<< " " << d_euler_hpr.p
			<< " " << d_euler_hpr.r
			<< std::endl;
	/*********read linear acceleration converted data**********/
	std::cout << "linear acceleration converted data: " << d_linear_accel_xyz.x
			<< " " << d_linear_accel_xyz.y
			<< " " << d_linear_accel_xyz.z
			<< std::endl;
	/********************Gravity converted data**********************/
	std::cout << "Gravity converted data: " << d_gravity_xyz.x
			<< " " << d_gravity_xyz.y
			<< " " << d_gravity_xyz.z
			<< std::endl;
	/*** temp celcius ***/
	std::cout << "temp celcius: " << temp_celcius
			<< std::endl;
}

s32 bno055_raw_data_readout(void)
{
	s32 comres = BNO055_ERROR;
/************************* START READ RAW SENSOR DATA****************/

/*	Raw accel X, Y and Z data can read from the register
	page - page 0
	register - 0x08 to 0x0D*/
	comres += bno055_read_accel_xyz(&accel_xyz);
/*	Raw mag X, Y and Z data can read from the register
	page - page 0
	register - 0x0E to 0x13*/
	comres += bno055_read_mag_xyz(&mag_xyz);
/*	Raw gyro X, Y and Z data can read from the register
	page - page 0
	register - 0x14 to 0x19*/
	comres += bno055_read_gyro_xyz(&gyro_xyz);

/************************* END READ RAW SENSOR DATA****************/

	comres += bno055_read_temp_data(&temp_s8);
	return comres;
}

s32 bno055_data_readout(void)
{
	s32 comres = BNO055_ERROR;
/************************* START READ RAW FUSION DATA ********
/*	Raw Euler H, R and P data can read from the register
	page - page 0
	register - 0x1A to 0x1E */
	comres += bno055_read_euler_hrp(&euler_hrp);
/*	Raw Quaternion W, X, Y and Z data can read from the register
	page - page 0
	register - 0x20 to 0x27 */
	comres += bno055_read_quaternion_wxyz(&quaternion_wxyz);
/*	Raw Linear accel X, Y and Z data can read from the register
	page - page 0
	register - 0x28 to 0x2D */
	comres += bno055_read_linear_accel_xyz(&linear_acce_xyz);
/*	Raw Gravity sensor X, Y and Z data can read from the register
	page - page 0
	register - 0x2E to 0x33 */
	comres += bno055_read_gravity_xyz(&gravity_xyz);
/************************* END READ RAW FUSION DATA  ************/

/******************START READ CONVERTED SENSOR DATA****************/
/*	API used to read accel data output as double  - m/s2 and mg
	float functions also available in the BNO055 API */
	comres += bno055_convert_double_accel_xyz_msq(&d_accel_xyz);
	//comres += bno055_convert_double_accel_xyz_mg(&d_accel_xyz);

/*	API used to read mag data output as double  - uT(micro Tesla)
	float functions also available in the BNO055 API */
	comres += bno055_convert_double_mag_xyz_uT(&d_mag_xyz);

/*	API used to read gyro data output as double  - dps and rps
	float functions also available in the BNO055 API */
	comres += bno055_convert_double_gyro_xyz_dps(&d_gyro_xyz);
	//comres += bno055_convert_double_gyro_xyz_rps(&d_gyro_xyz);

/*	API used to read Euler data output as double  - degree and radians
	float functions also available in the BNO055 API */
	comres += bno055_convert_double_euler_hpr_deg(&d_euler_hpr);
	//comres += bno055_convert_double_euler_hpr_rad(&d_euler_hpr);

/*	API used to read Linear acceleration data output as m/s2
	float functions also available in the BNO055 API */
	comres += bno055_convert_double_linear_accel_xyz_msq(&d_linear_accel_xyz);

/*	API used to read Gravity sensor data output as m/s2
	float functions also available in the BNO055 API */
	comres += bno055_convert_double_gravity_xyz_msq(&d_gravity_xyz);

	comres += bno055_convert_double_temp_celsius(&temp_celcius);
	return comres;
}



int main(void) 
{
	// Console logger with color

	auto console = spdlog::stdout_color_st("console");
	//spdlog::set_formatter();
	spdlog::set_pattern("[%t][%Y-%m-%d %T.%e][%L] %v");
	spdlog::set_level(spdlog::level::trace);

    if (StartTxtDownloadProg() == KELIB_ERROR_NONE)
    {
        pTArea = GetKeLibTransferAreaMainAddress();

        if (pTArea)
        {
            // Start using Callback Function
            SetTransferAreaCompleteCallback(TransferAreaCallbackFunction);

            uint32_t u32RetValue = InitI2C();
            if(u32RetValue != 0) {
                printf("exit InitI2C");
        		return 1;
            }

        	struct bno055_t bno;
            bno.bus_read = &user_i2c_read;
            bno.bus_write = &user_i2c_write;
            bno.delay_msec = &user_delay_ms;
            bno.dev_addr = BNO055_I2C_ADDR1;

            //printf("bno055_init... ");
            int8_t ret = bno055_init(&bno);
            //printf("%i\n", ret);
        	if (ret != BNO055_SUCCESS) {
                printf("exit bno055_init");
        		return 1;
        	}

        	/*	Using BNO055 sensor we can read the following sensor data and
        		virtual sensor data
        		Sensor data:
        			Accel
        			Mag
        			Gyro
        		Virtual sensor data
        			Euler
        			Quaternion
        			Linear acceleration
        			Gravity sensor */

#ifdef RAWDATA
        	/*  For reading sensor raw data it is required to set the
        		operation modes of the sensor
        		operation mode can set from the register
        		page - page0
        		register - 0x3D
        		bit - 0 to 3
        		for sensor data read following operation mode have to set
        		 * SENSOR MODE
        			*0x01 - BNO055_OPERATION_MODE_ACCONLY
        			*0x02 - BNO055_OPERATION_MODE_MAGONLY
        			*0x03 - BNO055_OPERATION_MODE_GYRONLY
        			*0x04 - BNO055_OPERATION_MODE_ACCMAG
        			*0x05 - BNO055_OPERATION_MODE_ACCGYRO
        			*0x06 - BNO055_OPERATION_MODE_MAGGYRO
        			*0x07 - BNO055_OPERATION_MODE_AMG
        			based on the user need configure the operation mode*/
        	ret = bno055_set_operation_mode(BNO055_OPERATION_MODE_AMG);
#else
        	/* For reading fusion data it is required to set the
        	operation modes of the sensor
        	operation mode can set from the register
        	page - page0
        	register - 0x3D
        	bit - 0 to 3
        	for sensor data read following operation mode have to set
        	*FUSION MODE
        		*0x08 - BNO055_OPERATION_MODE_IMUPLUS
        		*0x09 - BNO055_OPERATION_MODE_COMPASS
        		*0x0A - BNO055_OPERATION_MODE_M4G
        		*0x0B - BNO055_OPERATION_MODE_NDOF_FMC_OFF
        		*0x0C - BNO055_OPERATION_MODE_NDOF
        		based on the user need configure the operation mode*/
        	ret = bno055_set_operation_mode(BNO055_OPERATION_MODE_NDOF);
#endif
            while(1)
            {
				/*bno055_euler_float_t eulerData;
	            //printf("bno055_convert_float_euler_hpr_deg... ");
				ret = bno055_convert_float_euler_hpr_deg(&eulerData);
	            //printf("%i\n", ret);
				std::cout << "eulerData(deg): "
						<< eulerData.h << " "
						<< eulerData.p << " "
						<< eulerData.r;*/
#ifdef RAWDATA
				bno055_raw_data_readout();
				bno055_raw_data_print();
#else
				bno055_data_readout();
				bno055_data_print();
#endif
				/*uint8_t accel_calib_status = 0;
				uint8_t gyro_calib_status = 0;
				uint8_t mag_calib_status = 0;
				uint8_t sys_calib_status = 0;
				ret = bno055_get_accel_calib_stat(&accel_calib_status);
				ret = bno055_get_gyro_calib_stat(&gyro_calib_status);
				ret = bno055_get_mag_calib_stat(&mag_calib_status);
				ret = bno055_get_sys_calib_stat(&sys_calib_status);
				std::cout << " stat: "
						<< accel_calib_status << " "
						<< gyro_calib_status << " "
						<< mag_calib_status << " "
						<< sys_calib_status;*/

				std::cout << std::endl;
				usleep(1000); //1ms
            }
        }
        StopTxtDownloadProg();
    }
	return 0;
}
