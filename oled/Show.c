#include "Show.h"

void Oled_Show(void)
{
	// 欧拉角解算方式的显示
	if (Angle.Way == 1)
		OLED_ShowString(0, 0, "DMP");
	else if (Angle.Way == 2)
		OLED_ShowString(0, 0, "Kalman");
	else if (Angle.Way == 3)
		OLED_ShowString(0, 0, "C F");

	// 角度的显示
	OLED_ShowString(00, 10, "Pitch");
	if (Angle.Pitch < 0)
		OLED_ShowString(48, 10, "-");
	if (Angle.Pitch >= 0)
		OLED_ShowString(48, 10, "+");
	OLED_ShowNumber(56, 10, abs((int)Angle.Pitch), 3, 12);

	OLED_ShowString(0, 20, "Roll");
	if (MPU.gyroX < 0)
		OLED_ShowString(42, 20, "-");
	if (MPU.gyroX >= 0)
		OLED_ShowString(42, 20, "+");
	OLED_ShowNumber(50, 20, abs((int)Angle.Roll), 4, 12);
	
	OLED_ShowString(0, 30, "Yaw");
	if (MPU.gyroX < 0)
		OLED_ShowString(42, 30, "-");
	if (MPU.gyroX >= 0)
		OLED_ShowString(42, 30, "+");
	OLED_ShowNumber(50, 30, abs((int)Angle.Yaw), 4, 12);


	OLED_Refresh_Gram();
}
