/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <string.h>
#include "stm32f401xx.h"

void delay(void)
{
	for (int i = 0; i < 1000000; ++i) {
		;
	}
}

static inline void vDoI2CGpioConf(void);

static inline void vDoI2CGpioConf(void)
{
	TS_GPIO_CONFIG sGpioI2C1SclConf;
	sGpioI2C1SclConf.u8GpioPinNum = GPIO_PIN_NUM_8;
	sGpioI2C1SclConf.u8GpioPinMode = GPIO_MODE_ALT_FUNC;
	sGpioI2C1SclConf.u8GpioPinAltFunMode = GPIO_AF_NUM_4;
	sGpioI2C1SclConf.u8GpioPinOPType = GPIO_OUT_MODE_OD;
	sGpioI2C1SclConf.u8GpioPinPuPdControl = GPIO_PUPD_NU_ND;
	sGpioI2C1SclConf.u8GpioPinSpeed = GPIO_OUT_SPEED_VERY_HIGH;

	TS_GPIO_CONFIG sGpioI2C1SdaConf;
	sGpioI2C1SdaConf.u8GpioPinNum = GPIO_PIN_NUM_9;
	sGpioI2C1SdaConf.u8GpioPinMode = GPIO_MODE_ALT_FUNC;
	sGpioI2C1SclConf.u8GpioPinAltFunMode = GPIO_AF_NUM_4;
	sGpioI2C1SdaConf.u8GpioPinOPType = GPIO_OUT_MODE_OD;
	sGpioI2C1SdaConf.u8GpioPinPuPdControl = GPIO_PUPD_NU_ND;
	sGpioI2C1SdaConf.u8GpioPinSpeed = GPIO_OUT_SPEED_VERY_HIGH;

	TS_GPIO_HANDLE sGpioI2C1Scl;
	sGpioI2C1Scl.psGpioBaseAddr = GPIOB;
	sGpioI2C1Scl.sGpioPinConfig = &sGpioI2C1SclConf;

	TS_GPIO_HANDLE sGpioI2C1Sda;
	sGpioI2C1Sda.psGpioBaseAddr = GPIOB;
	sGpioI2C1Sda.sGpioPinConfig = &sGpioI2C1SdaConf;

	vDoGpioPeriClockControl(GPIOB, true);

	vDoGpioIni(&sGpioI2C1Scl);
	vDoGpioIni(&sGpioI2C1Sda);
}


int main(void)
{
	char user_data[] = "Hello world!!!";

	vDoI2CGpioConf();

	TS_I2C_CONFIG sI2CConf;
	sI2CConf.u328I2CSclSpeed = I2C_SCL_SPEED_SM;
	sI2CConf.u16I2CDeviceAddr = 0x77;
	sI2CConf.u8I2CAddrMode = I2C_ADDR_MODE_7;
	sI2CConf.u8I2CAckControl = I2C_ACK_CONTROL_ENABLE;
	sI2CConf.u8I2CFmDutyCycle = I2C_FM_DUTY_CYCLE_2;

	TS_I2C_HANDLE sI2CHandle;
	sI2CHandle.psI2CBaseAddr = I2C1;
	sI2CHandle.psI2CConfig = &sI2CConf;

	vDoI2CPeriClockControl(I2C1, true);

	vDoI2CIni(&sI2CHandle);

	while(1)
	{
		vDoI2CMasterSendData(&sI2CHandle, (uint8_t*) user_data, strlen(user_data), 0x44);
		delay();
	}
}
