#ifndef __ANGLE_H
#define __ANGLE_H

#include "sys.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "dmpKey.h"
#include "dmpmap.h"
#include "Filter.h"
#include "MPU6050.h"


typedef struct
{
	float accX;
	float accY;
	float accZ;
	float gyroX;
	float gyroY;
	float gyroZ;

	int Temperature;

} _St_MPU6050;

typedef struct
{
	float Pitch; // X
	float Roll;	 // Y
	float Yaw;	 // Z

	uint8_t Way; // 

} _St_Angle;




extern _St_MPU6050 MPU;				
extern _St_Angle Angle;	















void Get_Angle(uint8_t way);
void mpu_Init(void);

#endif
