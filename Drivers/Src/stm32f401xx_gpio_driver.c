/* === Include external headers === */


/* === Include own header === */
#include "stm32f401xx_gpio_driver.h"

/* === Local Functions === */



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

	/* Initialize GPIO Pin Mode */
	psGpioHandle->psGpioBaseAddr->MODER &= ~( 0x03 << (u8GpioPin * 2U));
	psGpioHandle->psGpioBaseAddr->MODER |= ((psGpioHandle->sGpioPinConfig->u8GpioPinMode & 0x03) << (u8GpioPin * 2U));

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
		psGpioHandle->psGpioBaseAddr->AFR[(u8GpioPin / 32U)] &= ~(( 0x0F << (u8GpioPin * 4U) % 32U));
		psGpioHandle->psGpioBaseAddr->AFR[(u8GpioPin / 32U)] |= ((psGpioHandle->sGpioPinConfig->u8GpioPinAltFunMode & 0x0F) << ((u8GpioPin * 4U) % 32U));
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
	return (((psGpioPort->IDR >> (u8GpioPin & 0x0F)) & 0x00000001) == 0x00000001);
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
 * 					uint8_t u8IqrNumber - IQR Number
 * 					uint8_t u8IqrPriority - IQR Priority
 * 					boolean bIqrState - State of IQR
 * Return       : void
 * ===========================================================================
 */
void vDoGpioIrqConfig(uint8_t u8IrqNumber, uint8_t u8IrqPriority, bool bIqrState)
{

}

/* ===========================================================================
 * Function name: vDoGpioIrqHandling()
 * Parameters   :
 * 					uint8_t u8GpioPin - GPIO Pin to be handled
 * Return       : void
 * ===========================================================================
 */
void vDoGpioIrqHandling(uint8_t u8GpioPin)
{

}

