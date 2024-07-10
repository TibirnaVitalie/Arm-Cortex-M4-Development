/* === Include external headers === */


/* === Include own header === */
#include "stm32f401xx_i2c_driver.h"

/* === Local Functions === */

static inline uint32_t u32vDoCalculatePclk1Value(void);
static inline uint32_t u32vDoCalculatePllOutputValue(void);

/* Peripheral clock 1 calculation function */

/* ===========================================================================
 * Function name: u32vDoCalculatePclk1Value()
 * Parameters   : void
 * Return       : uint32_t - Value of Pclk1
 * ===========================================================================
 */

static inline uint32_t u32vDoCalculatePclk1Value(void)
{
	uint8_t u8Apb1Presc = 0;
	uint16_t u16AhbPresc = 0;
	uint32_t u32RegVal, u32SysSource = 0;

	/* Read the system clock source */
	u32RegVal = ((RCC->CFGR >> 2U) & 0x03);

	switch (u32RegVal) {
		case 0x00:
			u32SysSource = 16000000U;
			break;

		case 0x01:
			u32SysSource = 25000000U;
			break;

		case 0x02:
			u32SysSource = u32vDoCalculatePllOutputValue();
			break;

		default:
			break;
	}

	/* Read the AHB prescaler */
	u32RegVal = ((RCC->CFGR >> 4U) & 0x0F);

	switch (u32RegVal) {
		case (uint32_t)0b1000:
			u16AhbPresc = 2U;
			break;

		case (uint32_t)0b1001:
			u16AhbPresc = 4U;
			break;

		case (uint32_t)0b1010:
			u16AhbPresc = 8U;
			break;

		case (uint32_t)0b1011:
			u16AhbPresc = 16U;
			break;

		case (uint32_t)0b1100:
			u16AhbPresc = 64U;
			break;

		case (uint32_t)0b1101:
			u16AhbPresc = 128U;
			break;

		case (uint32_t)0b1110:
			u16AhbPresc = (uint16_t)256U;
			break;

		case (uint32_t)0b1111:
			u16AhbPresc = (uint16_t)512U;
			break;

		default:
			u16AhbPresc = 1U;
			break;
	}

	/* Read the APB1 prescaler */
		u32RegVal = ((RCC->CFGR >> 10U) & 0x07);

		switch (u32RegVal) {
			case 0b0100:
				u8Apb1Presc = 2U;
				break;

			case 0b0101:
				u8Apb1Presc = 4U;
				break;

			case 0b0110:
				u8Apb1Presc = 8U;
				break;

			case 0b0111:
				u8Apb1Presc = 16U;
				break;

			default:
				u8Apb1Presc = 1U;
				break;
		}

	return ((u32SysSource / u16AhbPresc) / u8Apb1Presc);
}

/* PLL Output calculation function */

/* ===========================================================================
 * Function name: u32vDoCalculatePllOutputValue()
 * Parameters   : void
 * Return       : uint32_t - Value of PLL Output
 * ===========================================================================
 */

static inline uint32_t u32vDoCalculatePllOutputValue(void)
{
	return 0x01;
}

/* === Global Functions === */

/* I2C Peripheral Clock control function */

/* ===========================================================================
 * Function name: vDoI2CPeriClockControl()
 * Parameters   :
 * 					TS_I2C_REG_DEF *psI2C - I2C Base Address
 * 					boolean bState - State of I2C peripheral clock
 * Return       : void
 * ===========================================================================
 */

void vDoI2CPeriClockControl(TS_I2C_REG_DEF *psI2C, bool bState)
{
	if(bState)
	{
		if(psI2C == I2C1)
		{
			I2C1_PCKL_EN();
		}
		else if (psI2C == I2C2)
		{
			I2C2_PCKL_EN();
		}
		else if (psI2C == I2C3)
		{
			I2C3_PCKL_EN();
		}
	}
	else
	{
		if(psI2C == I2C1)
		{
			I2C1_PCKL_DI();
		}
		else if (psI2C == I2C2)
		{
			I2C2_PCKL_DI();
		}
		else if (psI2C == I2C3)
		{
			I2C3_PCKL_DI();
		}
	}
}

/* I2C Init/DeInit functions */

/* ===========================================================================
 * Function name: vDoI2CIni()
 * Parameters   :
 * 					TS_I2C_HANDLE *psI2CHandle - I2C Handle structure
 * Return       : void
 * ===========================================================================
 */
void vDoI2CIni(TS_I2C_HANDLE *psI2CHandle)
{
	uint16_t u16CcrValue = 0;
	uint8_t u32Pclk1 = u32vDoCalculatePclk1Value();
	uint8_t u8Pclk1Cr2 = ((u32Pclk1 / 1000000U) & 0x3F);
	uint8_t u8AddrMode = (psI2CHandle->psI2CConfig->u8I2CAddrMode & 0x01);

	/* Initialize Acknowledge feature */
	psI2CHandle->psI2CBaseAddr->CR1 &= ~(0x01 << 10U);
	psI2CHandle->psI2CBaseAddr->CR1 |= ((psI2CHandle->psI2CConfig->u8I2CAckControl & 0x01) << 10U);

	/* Initialize I2C Peripheral clock frequency */
	psI2CHandle->psI2CBaseAddr->CR2 &= ~(0x3F << 0U);
	psI2CHandle->psI2CBaseAddr->CR2 |= (((u8Pclk1Cr2 <= 0x01) ? 0x02 : u8Pclk1Cr2) << 0U);

	/* Initialize Addressing mode and Device Own Address */
	psI2CHandle->psI2CBaseAddr->OAR1 |= (0x01 << 14U);
	psI2CHandle->psI2CBaseAddr->OAR1 &= ~(0x01 << 15U);
	psI2CHandle->psI2CBaseAddr->OAR1 |= (u8AddrMode << 15U);

	switch (u8AddrMode) {
		case 0x00:
			psI2CHandle->psI2CBaseAddr->OAR1 |= ((psI2CHandle->psI2CConfig->u16I2CDeviceAddr & 0x7F) << 1U);
			break;

		case 0x01:
			psI2CHandle->psI2CBaseAddr->OAR1 |= ((psI2CHandle->psI2CConfig->u16I2CDeviceAddr & 0x03FF) << 0U);
			break;

		default:
			break;
	}

	/* CCR calculations */
	switch (psI2CHandle->psI2CConfig->u328I2CSclSpeed) {
		case I2C_SCL_SPEED_SM:
			/* Set I2C in slow mode */
			psI2CHandle->psI2CBaseAddr->CCR &= ~(0x01 << 15U);

			/* Calculate CCR for Slow Mode */
			u16CcrValue = (u32Pclk1 / (psI2CHandle->psI2CConfig->u328I2CSclSpeed * 2U)) ;
			break;

		case I2C_SCL_SPEED_FM_2K:
		case I2C_SCL_SPEED_FM_4K:
			/* Set I2C in fast mode */
			psI2CHandle->psI2CBaseAddr->CCR |= (0x01 << 15U);

			/* Initialize FM mode Duty Cycle */
			psI2CHandle->psI2CBaseAddr->CCR &= ~(0x01 << 14U);
			psI2CHandle->psI2CBaseAddr->CCR |= ((psI2CHandle->psI2CConfig->u8I2CFmDutyCycle & 0x01) << 14U);

			/* Calculate CCR for Slow Mode */
			u16CcrValue = (u32Pclk1 / (psI2CHandle->psI2CConfig->u328I2CSclSpeed * ((psI2CHandle->psI2CConfig->u328I2CSclSpeed == I2C_SCL_SPEED_FM_2K)? 3U : 25U)));
			break;

		default:
			break;
	}

	/* Set CCR Value */
	psI2CHandle->psI2CBaseAddr->CCR &= ~(0x0FFF << 0U);
	psI2CHandle->psI2CBaseAddr->CCR |= ((u16CcrValue & 0x0FFF) << 0U);

}

/* ===========================================================================
 * Function name: vDoI2CDeIni()
 * Parameters   :
 * 					TS_I2C_REG_DEF *psI2C - I2C Base Address
 * Return       : void
 * ===========================================================================
 */
void vDoI2CDeIni(TS_I2C_REG_DEF *psI2C)
{
	if(psI2C == I2C1)
	{
		I2C1_REG_RESET();
	}
	else if (psI2C == I2C2)
	{
		I2C2_REG_RESET();
	}
	else if (psI2C == I2C3)
	{
		I2C3_REG_RESET();
	}
}

/* I2C Peripheral control functions */

/* ===========================================================================
 * Function name: vDoI2CPeriControl()
 * Parameters   :
 * 					TS_I2C_REG_DEF *psI2C - I2C Base Address
 * 					boolean bState - State of I2C peripheral
 * Return       : void
 * ===========================================================================
 */

void vDoI2CPeriControl(TS_I2C_REG_DEF *psI2C, bool bState)
{
	if(bState)
	{
		psI2C->CR1 |= (0x01 << 0U);
	}
	else
	{
		psI2C->CR1 &= ~(0x01 << 0U);
	}
}

/* ===========================================================================
 * Function name: bDoGetI2CFlag()
 * Parameters   :
 * 					TS_I2C_REG_DEF *psI2C - I2C Base Address
 * 					uint32_t u32I2CFlag - I2C Flag
 * Return       : boolean - Status of flag
 * ===========================================================================
 */

bool bDoGetI2CFlag(TS_I2C_REG_DEF *psI2C, uint32_t u32I2CFlag)
{
	return ((psI2C->SR[(u32I2CFlag / 32)] & (0x01 << (u32I2CFlag % 32))) != 0x00);
}
