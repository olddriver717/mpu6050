#include "Angle.h"

_St_MPU6050 MPU;				// mpu相关结构体
_St_Angle Angle;				// 角度相关结构体

#define PI 3.14159265

void mpu_Init(void)
{
	MPU6050_Initialize();				// MPU6050初始化
	DMP_Init();							// 初始化DMP
	
}


void Get_Angle(uint8_t way)
{
	float Accel_Y, Accel_Z, Accel_X, Gyro_X, Gyro_Z, Gyro_Y, Accel_Angle_x, Accel_Angle_y,Accel_Angle_z;

	MPU.Temperature = Read_Temperature(); // 读取MPU6050内置温度传感器数据，近似表示主板温度。
	if (way == 1)
	{
		Read_DMP();			 // 使用DMP四元数计算数据
		Angle.Pitch = Pitch; // X轴角度
		Angle.Roll = Roll;	 // Y轴角度
		Angle.Yaw = Yaw;
		MPU.gyroX = gyro[0]; // X轴角速度
		MPU.gyroY = gyro[1]; // Y轴角速度
		MPU.gyroZ = gyro[2]; // Z轴角速度
		MPU.accX = accel[0]; // X轴加速度
		MPU.accY = accel[1]; // Y轴加速度
		MPU.accZ = accel[2]; // Z轴加速度
	}
	else
	{
		// MPU六轴数据的读取
		Gyro_X = (short)(I2C_ReadOneByte(devAddr, MPU6050_RA_GYRO_XOUT_H) << 8) + I2C_ReadOneByte(devAddr, MPU6050_RA_GYRO_XOUT_L);	   // 读取X轴陀螺仪
		Gyro_Y = (short)(I2C_ReadOneByte(devAddr, MPU6050_RA_GYRO_YOUT_H) << 8) + I2C_ReadOneByte(devAddr, MPU6050_RA_GYRO_YOUT_L);	   // 读取Y轴陀螺仪
		Gyro_Z = (short)(I2C_ReadOneByte(devAddr, MPU6050_RA_GYRO_ZOUT_H) << 8) + I2C_ReadOneByte(devAddr, MPU6050_RA_GYRO_ZOUT_L);	   // 读取Z轴陀螺仪
		Accel_X = (short)(I2C_ReadOneByte(devAddr, MPU6050_RA_ACCEL_XOUT_H) << 8) + I2C_ReadOneByte(devAddr, MPU6050_RA_ACCEL_XOUT_L); // 读取X轴加速度计
		Accel_Y = (short)(I2C_ReadOneByte(devAddr, MPU6050_RA_ACCEL_YOUT_H) << 8) + I2C_ReadOneByte(devAddr, MPU6050_RA_ACCEL_YOUT_L); // 读取X轴加速度计
		Accel_Z = (short)(I2C_ReadOneByte(devAddr, MPU6050_RA_ACCEL_ZOUT_H) << 8) + I2C_ReadOneByte(devAddr, MPU6050_RA_ACCEL_ZOUT_L); // 读取Z轴加速度计
		MPU.gyroX = -Gyro_X;
		MPU.gyroY = Gyro_Y;
		MPU.gyroZ = Gyro_Z;
		MPU.accX = -Accel_X;
		MPU.accY = Accel_Y;
		MPU.accZ = Accel_Z;
		// 欧拉角的计算
		Accel_Angle_x = atan2(Accel_Y, Accel_Z) * 180 / PI; // 计算倾角，转换单位为度
		Accel_Angle_y = atan2(Accel_X, Accel_Z) * 180 / PI; // 计算倾角，转换单位为度
		Accel_Angle_z = atan2(Accel_X, Accel_Y) * 180 / PI; // 计算倾角，转换单位为度
		Gyro_X = Gyro_X / 16.4;								
		Gyro_Y = Gyro_Y / 16.4;			
		Gyro_Z = Gyro_Z / 16.4;	
		if (Angle.Way == 2)									// 卡尔曼滤波
		{
			Angle.Pitch = -Kalman_Filter_x(Accel_Angle_x, Gyro_X);
			Angle.Roll = -Kalman_Filter_y(Accel_Angle_y, Gyro_Y);
			Angle.Yaw = -Kalman_Filter_z(Accel_Angle_z, Gyro_Z);
		}
		else if (Angle.Way == 3) // 互补滤波
		{
			Angle.Pitch = -Complementary_Filter_x(Accel_Angle_x, Gyro_X);
			Angle.Roll = -Complementary_Filter_y(Accel_Angle_y, Gyro_Y);
		}
	}
}
