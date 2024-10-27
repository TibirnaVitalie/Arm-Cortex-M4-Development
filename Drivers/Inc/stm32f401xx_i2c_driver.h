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

/* I2C Write / Read modes */

#define I2C_WRITE										0x00
#define I2C_READ										0x01

/* === I2Cs macros === */

/* I2C Status flags (I2C_SR1 Register) */

#define I2C_SB_FLAG										0x00
#define I2C_ADDR_FLAG									0x01
#define I2C_BTF_FLAG									0x02
#define I2C_ADD10_FLAG									0x03
#define I2C_STOPF_FLAG									0x04
#define I2C_RXNE_FLAG									0x06
#define I2C_TXE_FLAG									0x07
#define I2C_BERR_FLAG									0x08
#define I2C_ARLO_FLAG									0x09
#define I2C_AF_FLAG										0x0A
#define I2C_OVR_FLAG									0x0B
#define I2C_PECERR_FLAG									0x0C
#define I2C_TIMEOUT_FLAG								0x0E
#define I2C_SMBALERT_FLAG								0x0F

/* I2C Status flags (I2C_SR2 Register) */

#define I2C_MSL_FLAG									0x00
#define I2C_BUSY_FLAG									0x10
#define I2C_TRA_FLAG									0x20
#define I2C_GENCALL_FLAG								0x40
#define I2C_SMBDEFAULT_FLAG								0x50
#define I2C_SMBHOST_FLAG								0x60
#define I2C_DUALF_FLAG									0x70

/* === APIs supported by this driver === */

/* I2C Peripheral Clock control function */

void vDoI2CPeriClockControl(TS_I2C_REG_DEF *psI2C, bool bState);

/* I2C Init/DeInit functions */

void vDoI2CIni(TS_I2C_HANDLE *psI2CHandle);
void vDoI2CDeIni(TS_I2C_REG_DEF *psI2C);

/* I2C Master Data Send and Receive functions */

void vDoI2CMasterSendData(TS_I2C_HANDLE *psI2CHandle, uint8_t *pu8I2CTxBuff, uint32_t u32I2CDataLen, uint8_t u8SlaveAddr);
void vDoI2CMasterReceiveData(TS_I2C_HANDLE *psI2CHandle, uint8_t *pu8I2CRxBuff, uint32_t u32I2CDataLen, uint8_t u8SlaveAddr);

/* I2C Peripheral control */

void vDoI2CPeriControl(TS_I2C_REG_DEF *psI2C, bool bState);
bool bDoGetI2CFlag(TS_I2C_REG_DEF *psI2C, uint32_t u32I2CFlag);
void vDoI2CManageAcking(TS_I2C_REG_DEF *psI2C, bool bState);

#endif /* INC_STM32F401XX_I2C_DRIVER_H_ */
