#ifndef INC_STM32F401XX_GPIO_DRIVER_H_
#define INC_STM32F401XX_GPIO_DRIVER_H_

/* Include external headers */
#include "stm32f401xx.h"

typedef struct
{
	uint8_t u8GpioPinNum;								/* GPIO Pin number */
	uint8_t u8GpioPinMode;								/* GPIO Pin mode */
	uint8_t u8GpioPinSpeed;								/* GPIO Pin speed */
	uint8_t u8GpioPinPuPdControl;						/* GPIO Pin Pull-up/Pull-down control */
	uint8_t u8GpioPinOPType;							/* GPIO Pin Output type */
	uint8_t u8GpioPinAltFunMode;						/* GPIO Pin Alternate function */
} TS_GPIO_CONFIG;

typedef struct
{
	TS_GPIO_REG_DEF *psGpioBaseAddr;					/* GPIO Port Base Address */
	TS_GPIO_CONFIG *sGpioPinConfig;						/* GPIO Pin configuration settings */
} TS_GPIO_HANDLE;

/* === GPIOs possible modes === */

/* GPIO Pin possible numbers */

#define GPIO_PIN_NUM_0									0x00
#define GPIO_PIN_NUM_1									0x01
#define GPIO_PIN_NUM_2									0x02
#define GPIO_PIN_NUM_3									0x03
#define GPIO_PIN_NUM_4									0x04
#define GPIO_PIN_NUM_5									0x05
#define GPIO_PIN_NUM_6									0x06
#define GPIO_PIN_NUM_7									0x07
#define GPIO_PIN_NUM_8									0x08
#define GPIO_PIN_NUM_9									0x09
#define GPIO_PIN_NUM_10									0x0A
#define GPIO_PIN_NUM_11									0x0B
#define GPIO_PIN_NUM_12									0x0C
#define GPIO_PIN_NUM_13									0x0D
#define GPIO_PIN_NUM_14									0x0E
#define GPIO_PIN_NUM_15									0x0F

/* GPIO Pin possible modes */

#define GPIO_MODE_IN									0x00
#define GPIO_MODE_OUT									0x01
#define GPIO_MODE_ALT_FUNC								0x02
#define GPIO_MODE_ANALOG								0x03
#define GPIO_MODE_IT_RE									0x04
#define GPIO_MODE_IT_FE									0x05
#define GPIO_MODE_IT_RFE								0x06

/* GPIO Pin possible Output types */

#define GPIO_OUT_MODE_PP								0x00
#define GPIO_OUT_MODE_OD								0x01

/* GPIO Pin possible Output speed */

#define GPIO_OUT_SPEED_LOW								0x00
#define GPIO_OUT_SPEED_MED								0x01
#define GPIO_OUT_SPEED_HIGH								0x02
#define GPIO_OUT_SPEED_VERY_HIGH						0x03

/* GPIO Pin possible Output speed */

#define GPIO_PUPD_NU_ND									0x00
#define GPIO_PUPD_PU									0x01
#define GPIO_PUPD_PD									0x02

/* GPIO Alternate Functions possible numbers */

#define GPIO_AF_NUM_0									0x00
#define GPIO_AF_NUM_1									0x01
#define GPIO_AF_NUM_2									0x02
#define GPIO_AF_NUM_3									0x03
#define GPIO_AF_NUM_4									0x04
#define GPIO_AF_NUM_5									0x05
#define GPIO_AF_NUM_6									0x06
#define GPIO_AF_NUM_7									0x07
#define GPIO_AF_NUM_8									0x08
#define GPIO_AF_NUM_9									0x09
#define GPIO_AF_NUM_10									0x0A
#define GPIO_AF_NUM_11									0x0B
#define GPIO_AF_NUM_12									0x0C
#define GPIO_AF_NUM_13									0x0D
#define GPIO_AF_NUM_14									0x0E
#define GPIO_AF_NUM_15									0x0F

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

void vDoGpioIrqConfig(TS_NVIC_REG_DEF *psNvic, uint8_t u8IrqNumber, uint8_t u8IrqPriority, bool bIqrState);
void vDoGpioIrqHandling(TS_EXTI_REG_DEF *psExti, uint8_t u8GpioPin);

#endif /* INC_STM32F401XX_GPIO_DRIVER_H_ */
