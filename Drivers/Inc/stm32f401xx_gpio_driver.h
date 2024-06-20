#ifndef INC_STM32F401XX_GPIO_DRIVER_H_
#define INC_STM32F401XX_GPIO_DRIVER_H_

/* Include external headers */
#include "stm32f401xx.h"

typedef struct
{
	uint8_t u8GpioPinNum;
	uint8_t u8GpioPinMode;
	uint8_t u8GpioPinSpeed;
	uint8_t u8GpioPinPuPdControl;
	uint8_t u8GpioPinOPType;
	uint8_t u8GpioPinAltFunMode;
} TS_GPIO_CONFIG;

typedef struct
{
	TS_GPIO_REG_DEF *psGpioBaseAddr;					/* GPIO Port Base Address */
	TS_GPIO_CONFIG sGpioPinConfig;						/* GPIO Pin configuration settings */
} TS_GPIO_HANDLE;

/* === APIs supported by this driver === */

/* GPIO Peripheral Clock control function */

void vDoGpioPeriClockControl(TS_GPIO_REG_DEF *psGpioPort, bool bState);

/* GPIO Init/DeInit functions */

void vDoGpioIni(TS_GPIO_HANDLE *psGpioHandle);
void vDoGpioDeIni(TS_GPIO_REG_DEF *psGpioPort);

/* GPIO Read/Write functions */

bool bDoGpioReadPin(TS_GPIO_REG_DEF *psGpioPort, uint8_t u8GpioPin);
uint16_t u16DoGpioReadPort(TS_GPIO_REG_DEF *psGpioPort);
void vDoGpioWritePin(TS_GPIO_REG_DEF *psGpioPort, uint8_t u8GpioPin, bool bValue);
void vDoGpioWritePort(TS_GPIO_REG_DEF *psGpioPort, uint16_t u16Value);
void vDoGpioTogglePin(TS_GPIO_REG_DEF *psGpioPort, uint8_t u8GpioPin);

/* GPIO IRQ configuration and ISR handling functions */

void vDoGpioIrqConfig(uint8_t u8IrqNumber, uint8_t u8IrqPriority, bool bIqrState);
void vDoGpioIrqHandling(uint8_t u8GpioPin);

#endif /* INC_STM32F401XX_GPIO_DRIVER_H_ */
