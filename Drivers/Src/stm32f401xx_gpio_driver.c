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
	return false;
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
	return 0;
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

