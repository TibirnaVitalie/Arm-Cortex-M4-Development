/* === Include external headers === */


/* === Include own header === */
#include "stm32f401xx_gpio_driver.h"

/* === Local Functions === */

static inline uint8_t u8GetGpioPortCode(TS_GPIO_REG_DEF *psGpioPort);
static inline void vDoGpioIrqIni(TS_GPIO_HANDLE *psGpioHandle);

/* Get GPIO Port code by GPIO Port base address function */

/* ===========================================================================
 * Function name: u8GetGpioPortCode()
 * Parameters   :
 * 					TS_GPIO_REG_DEF *psGpioPort - GPIO Port Base Address
 * Return       : uint8_t - GPIO Port code
 * ===========================================================================
 */
static inline uint8_t u8GetGpioPortCode(TS_GPIO_REG_DEF *psGpioPort)
{
	uint8_t u8GpioPortCode = 0;

	if(psGpioPort == GPIOA)
	{
		u8GpioPortCode = 0x00;
	}
	else if (psGpioPort == GPIOB)
	{
		u8GpioPortCode = 0x01;
	}
	else if (psGpioPort == GPIOC)
	{
		u8GpioPortCode = 0x02;
	}
	else if (psGpioPort == GPIOD)
	{
		u8GpioPortCode = 0x03;
	}
	else if (psGpioPort == GPIOE)
	{
		u8GpioPortCode = 0x04;
	}
	else if (psGpioPort == GPIOH)
	{
		u8GpioPortCode = 0x07;
	}

	return u8GpioPortCode;
}

/* Configure IRQ for PGIOs */

/* ===========================================================================
 * Function name: vDoGpioIrqIni()
 * Parameters   :
 * 					TS_GPIO_HANDLE *psGpioHandle - GPIO Handle structure
 * Return       : void
 * ===========================================================================
 */

static inline void vDoGpioIrqIni(TS_GPIO_HANDLE *psGpioHandle)
{
	uint8_t u8GpioPin = (psGpioHandle->sGpioPinConfig->u8GpioPinNum & 0x0F);

	SYSCFG_PCKL_EN();
	SYSCFG->EXTICR[(u8GpioPin / 4)] |= ((u8GetGpioPortCode(psGpioHandle->psGpioBaseAddr) & 0x0F) << ((u8GpioPin * 4U) % 16U));

	EXTI->IMR |= (1 << u8GpioPin);
}

/* === Global Functions === */

/* GPIO Peripheral Clock control function */

/* ===========================================================================
 * Function name: vDoGpioPeriClockControl()
 * Parameters   :
 * 					TS_GPIO_REG_DEF *psGpioPort - GPIO Port Base Address
 * 					boolean bState - State of GPIO peripheral clock
 * Return       : void
 * ===========================================================================
 */
void vDoGpioPeriClockControl(TS_GPIO_REG_DEF *psGpioPort, bool bState)
{
	if(bState)
	{
		if(psGpioPort == GPIOA)
		{
			GPIOA_PCKL_EN();
		}
		else if (psGpioPort == GPIOB)
		{
			GPIOB_PCKL_EN();
		}
		else if (psGpioPort == GPIOC)
		{
			GPIOC_PCKL_EN();
		}
		else if (psGpioPort == GPIOD)
		{
			GPIOD_PCKL_EN();
		}
		else if (psGpioPort == GPIOE)
		{
			GPIOE_PCKL_EN();
		}
		else if (psGpioPort == GPIOH)
		{
			GPIOH_PCKL_EN();
		}
	}
	else
	{
		if(psGpioPort == GPIOA)
		{
			GPIOA_PCKL_DI();
		}
		else if (psGpioPort == GPIOB)
		{
			GPIOB_PCKL_DI();
		}
		else if (psGpioPort == GPIOC)
		{
			GPIOC_PCKL_DI();
		}
		else if (psGpioPort == GPIOD)
		{
			GPIOD_PCKL_DI();
		}
		else if (psGpioPort == GPIOE)
		{
			GPIOE_PCKL_DI();
		}
		else if (psGpioPort == GPIOH)
		{
			GPIOH_PCKL_DI();
		}
	}
}

/* GPIO Init/DeInit functions */

/* ===========================================================================
 * Function name: vDoGpioIni()
 * Parameters   :
 * 					TS_GPIO_HANDLE *psGpioHandle - GPIO Handle structure
 * Return       : void
 * ===========================================================================
 */
void vDoGpioIni(TS_GPIO_HANDLE *psGpioHandle)
{
	uint8_t u8GpioPin = (psGpioHandle->sGpioPinConfig->u8GpioPinNum & 0x0F);
	uint8_t u8GpioPinMode = (psGpioHandle->sGpioPinConfig->u8GpioPinMode & 0x07);

	/* Initialize GPIO Pin Mode */
	switch (u8GpioPinMode) {
		case GPIO_MODE_IN:
		case GPIO_MODE_OUT:
		case GPIO_MODE_ALT_FUNC:
		case GPIO_MODE_ANALOG:
			psGpioHandle->psGpioBaseAddr->MODER &= ~( 0x03 << (u8GpioPin * 2U));
			psGpioHandle->psGpioBaseAddr->MODER |= (u8GpioPinMode << (u8GpioPin * 2U));
			break;

		case GPIO_MODE_IT_RE:
			EXTI->RTSR |= (1 << u8GpioPin);
			EXTI->FTSR &= ~(1 << u8GpioPin);

			vDoGpioIrqIni(psGpioHandle);
			break;

		case GPIO_MODE_IT_FE:
			EXTI->FTSR |= (1 << u8GpioPin);
			EXTI->RTSR &= ~(1 << u8GpioPin);

			vDoGpioIrqIni(psGpioHandle);
			break;

		case GPIO_MODE_IT_RFE:
			EXTI->RTSR |= (1 << u8GpioPin);
			EXTI->FTSR |= (1 << u8GpioPin);

			vDoGpioIrqIni(psGpioHandle);
			break;

		default:
			break;
	}

	/* Initialize GPIO Pin Speed */
	psGpioHandle->psGpioBaseAddr->OSPEEDR &= ~( 0x03 << (u8GpioPin * 2U));
	psGpioHandle->psGpioBaseAddr->OSPEEDR |= ((psGpioHandle->sGpioPinConfig->u8GpioPinSpeed & 0x03) << (u8GpioPin * 2U));

	/* Initialize GPIO Pin Pull-Up/Pull-Down mode */
	psGpioHandle->psGpioBaseAddr->PUPDR &= ~( 0x03 << (u8GpioPin * 2U));
	psGpioHandle->psGpioBaseAddr->PUPDR |= ((psGpioHandle->sGpioPinConfig->u8GpioPinPuPdControl & 0x03) << (u8GpioPin * 2U));

	/* Initialize GPIO Pin Output type */
	psGpioHandle->psGpioBaseAddr->OTYPER &= ~( 0x01 << (u8GpioPin * 2U));
	psGpioHandle->psGpioBaseAddr->OTYPER |= ((psGpioHandle->sGpioPinConfig->u8GpioPinOPType & 0x01) << u8GpioPin);

	/* Initialize GPIO Pin Alternate functions mode */
	if(psGpioHandle->sGpioPinConfig->u8GpioPinMode == (uint8_t)GPIO_MODE_ALT_FUNC)
	{
		psGpioHandle->psGpioBaseAddr->AFR[(u8GpioPin / 8U)] &= ~(( 0x0F << (u8GpioPin * 4U) % 32U));
		psGpioHandle->psGpioBaseAddr->AFR[(u8GpioPin / 8U)] |= ((psGpioHandle->sGpioPinConfig->u8GpioPinAltFunMode & 0x0F) << ((u8GpioPin * 4U) % 32U));
	}
}

/* ===========================================================================
 * Function name: vDoGpioDeIni()
 * Parameters   :
 * 					TS_GPIO_REG_DEF *psGpioPort - GPIO Pin number
 * Return       : void
 * ===========================================================================
 */
void vDoGpioDeIni(TS_GPIO_REG_DEF *psGpioPort)
{
	if(psGpioPort == GPIOA)
	{
		GPIOA_REG_RESET();
	}
	else if (psGpioPort == GPIOB)
	{
		GPIOB_REG_RESET();
	}
	else if (psGpioPort == GPIOC)
	{
		GPIOC_REG_RESET();
	}
	else if (psGpioPort == GPIOD)
	{
		GPIOD_REG_RESET();
	}
	else if (psGpioPort == GPIOE)
	{
		GPIOE_REG_RESET();
	}
	else if (psGpioPort == GPIOH)
	{
		GPIOH_REG_RESET();
	}
}

/* GPIO Read/Write functions */

/* ===========================================================================
 * Function name: bDoGpioReadPin()
 * Parameters   :
 * 					TS_GPIO_REG_DEF *psGpioPort - GPIO Port Base Address
 * 					uint8_t u8GpioPin - GPIO Pin
 * Return       : boolean - state on GPIO Pin
 * ===========================================================================
 */
bool bDoGpioReadPin(TS_GPIO_REG_DEF *psGpioPort, uint8_t u8GpioPin)
{
	return (((psGpioPort->IDR >> (u8GpioPin & 0x0F)) & 0x01) == 0x01);
}

/* ===========================================================================
 * Function name: u16DoGpioReadPort()
 * Parameters   :
 * 					TS_GPIO_REG_DEF *psGpioPort - GPIO Port Base Address
 * Return       : uint16_t - GPIO Port value
 * ===========================================================================
 */
uint16_t u16DoGpioReadPort(TS_GPIO_REG_DEF *psGpioPort)
{
	return (uint16_t)(psGpioPort->IDR & 0x0000FFFF);
}

/* ===========================================================================
 * Function name: vDoGpioWritePin()
 * Parameters   :
 * 					TS_GPIO_REG_DEF *psGpioPort - GPIO Port Base Address
 * 					uint8_t u8GpioPin - GPIO Pin to be read
 * 					boolean bValue - State of the GPIO Pin
 * Return       : void
 * ===========================================================================
 */
void vDoGpioWritePin(TS_GPIO_REG_DEF *psGpioPort, uint8_t u8GpioPin, bool bValue)
{
	if(bValue)
	{
		psGpioPort->ODR |= (1 << (u8GpioPin & 0x0F));
	}
	else
	{
		psGpioPort->ODR &= ~(1 << (u8GpioPin & 0x0F));
	}
}

/* ===========================================================================
 * Function name: vDoGpioWritePort()
 * Parameters   :
 * 					TS_GPIO_REG_DEF *psGpioPort - GPIO Port Base Address
 * 					uint16_t u16Value - GPIO Port value
 * Return       : void
 * ===========================================================================
 */
void vDoGpioWritePort(TS_GPIO_REG_DEF *psGpioPort, uint16_t u16Value)
{
	psGpioPort->ODR &= ~(0xFFFF);
	psGpioPort->ODR |= (uint32_t)u16Value;
}

/* ===========================================================================
 * Function name: vDoGpioTogglePin()
 * Parameters   :
 * 					TS_GPIO_REG_DEF *psGpioPort - GPIO Port Base Address
 * 					uint8_t u8GpioPin - Toggled GPIO Pin
 * Return       : void
 * ===========================================================================
 */
void vDoGpioTogglePin(TS_GPIO_REG_DEF *psGpioPort, uint8_t u8GpioPin)
{
	psGpioPort->ODR ^= (1 << (u8GpioPin & 0x0F));
}


/* GPIO IRQ configuration and ISR handling functions */

/* ===========================================================================
 * Function name: vDoGpioIrqConfig()
 * Parameters   :
 * 					TS_NVIC_REG_DEF *psNvic - NIVC definition
 * 					uint8_t u8IqrNumber - IQR Number
 * 					uint8_t u8IqrPriority - IQR Priority
 * 					boolean bIqrState - State of IQR
 * Return       : void
 * ===========================================================================
 */
void vDoGpioIrqConfig(TS_NVIC_REG_DEF *psNvic, uint8_t u8IrqNumber, uint8_t u8IrqPriority, bool bIqrState)
{
	if(bIqrState)
	{
		psNvic->ISER[(u8IrqNumber / 32U)] |= (1 << u8IrqNumber % 32U);
	}
	else
	{
		psNvic->ISER[(u8IrqNumber / 32U)] &= ~(1 << u8IrqNumber % 32U);
	}

	psNvic->IPR[u8IrqNumber / 4U] |= (u8IrqPriority << ((u8IrqNumber % 4U) * 4)) ;
}

/* ===========================================================================
 * Function name: vDoGpioIrqHandling()
 * Parameters   :
 * 					TS_EXTI_REG_DEF *psExti - EXTI definition
 * 					uint8_t u8GpioPin - GPIO Pin to be handled
 * Return       : void
 * ===========================================================================
 */
void vDoGpioIrqHandling(TS_EXTI_REG_DEF *psExti, uint8_t u8GpioPin)
{
	if(psExti->PR & (1 << u8GpioPin))
	{
		psExti->PR |= (1 << u8GpioPin);
	}
}

