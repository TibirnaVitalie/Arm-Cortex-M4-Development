#ifndef INC_STM32F401XX_I2C_DRIVER_H_
#define INC_STM32F401XX_I2C_DRIVER_H_

/* Include external headers */
#include "stm32f401xx.h"

typedef struct
{
	uint32_t u328I2CSclSpeed;							/* I2C Serial Clock Speed */
	uint16_t u16I2CDeviceAddr;							/* I2C Own Device Address */
	uint8_t u8I2CAddrMode;								/* I2C Device Addressing Mode */
	uint8_t u8I2CAckControl;							/* I2C Acknowledge Control */
	uint8_t u8I2CFmDutyCycle;							/* I2C FM Duty Cycle */
} TS_I2C_CONFIG;

typedef struct
{
	TS_I2C_REG_DEF *psI2CBaseAddr;						/* I2C Base Address */
	TS_I2C_CONFIG *psI2CConfig;							/* I2C configuration settings */
} TS_I2C_HANDLE;

/* === I2Cs possible modes === */

/* I2C possible Serial Clock Speeds */

#define I2C_SCL_SPEED_SM								100000U
#define I2C_SCL_SPEED_FM_2K								200000U
#define I2C_SCL_SPEED_FM_4K								400000U

/* I2C Addressing Modes (in Slave Mode) */

#define I2C_ADDR_MODE_7									0x00
#define I2C_ADDR_MODE_10								0x01

/* I2C Acknowledge Control Modes */

#define I2C_ACK_CONTROL_DISABLE							0x00
#define I2C_ACK_CONTROL_ENABLE							0x01

/* I2C Fast Mode Duty Cycle */

#define I2C_FM_DUTY_CYCLE_2								0x00
#define I2C_FM_DUTY_CYCLE_16_9							0x01

/* === APIs supported by this driver === */

/* I2C Peripheral Clock control function */

void vDoI2CPeriClockControl(TS_I2C_REG_DEF *psI2C, bool bState);

/* I2C Init/DeInit functions */

void vDoI2CIni(TS_I2C_HANDLE *psI2CHandle);
void vDoI2CDeIni(TS_I2C_REG_DEF *psI2C);

/* I2C Peripheral control */

void vDoI2CPeriControl(TS_I2C_REG_DEF *psI2C, bool bState);
bool bDoGetI2CFlag(TS_I2C_REG_DEF *psI2C, uint32_t u32I2CFlag);

#endif /* INC_STM32F401XX_I2C_DRIVER_H_ */
