/* === Include external headers === */


/* === Include own header === */
#include "stm32f401xx_spi_driver.h"

/* === Local Functions === */

bool bDoGetSpiFlag(TS_SPI_REG_DEF *psSpi, uint32_t u32SpiFlag);

/* SPI Flag return function */

/* ===========================================================================
 * Function name: bDoGetSpiFlag()
 * Parameters   :
 * 					TS_SPI_REG_DEF *psSpi - SPI Base Address
 * 					uint32_t u32SpiFlag - SPI Flag
 * Return       : boolean - Status of flag
 * ===========================================================================
 */

bool bDoGetSpiFlag(TS_SPI_REG_DEF *psSpi, uint32_t u32SpiFlag)
{
	return ((psSpi->SR & (0x01 << u32SpiFlag)) != 0x00);
}

/* === Global Functions === */

/* SPI Peripheral Clock control function */

/* ===========================================================================
 * Function name: vDoSpiPeriClockControl()
 * Parameters   :
 * 					TS_SPI_REG_DEF *psSpi - SPI Base Address
 * 					boolean bState - State of SPI peripheral clock
 * Return       : void
 * ===========================================================================
 */
void vDoSpiPeriClockControl(TS_SPI_REG_DEF *psSpi, bool bState)
{
	if(bState)
	{
		if(psSpi == SPI1)
		{
			SPI1_PCKL_EN();
		}
		else if (psSpi == SPI2)
		{
			SPI2_PCKL_EN();
		}
		else if (psSpi == SPI3)
		{
			SPI3_PCKL_EN();
		}
		else if (psSpi == SPI4)
		{
			SPI4_PCKL_EN();
		}
	}
	else
	{
		if(psSpi == SPI1)
		{
			SPI1_PCKL_DI();
		}
		else if (psSpi == SPI2)
		{
			SPI2_PCKL_DI();
		}
		else if (psSpi == SPI3)
		{
			SPI3_PCKL_DI();
		}
		else if (psSpi == SPI4)
		{
			SPI4_PCKL_DI();
		}
	}
}

/* SPI Init/DeInit functions */

/* ===========================================================================
 * Function name: vDoSpiIni()
 * Parameters   :
 * 					TS_SPI_HANDLE *psSpiHandle - SPI Handle structure
 * Return       : void
 * ===========================================================================
 */
void vDoSpiIni(TS_SPI_HANDLE *psSpiHandle)
{
	uint8_t u8SpiBusMode = (psSpiHandle->sSpiConfig->u8SpiBusConfig & 0x03);

	/* Initialize SPI Device Mode */
	psSpiHandle->psSpiBaseAddr->CR1 &= ~(0x01 << 2U);
	psSpiHandle->psSpiBaseAddr->CR1 |= ((psSpiHandle->sSpiConfig->u8SpiDeviceMode & 0x01) << 2U);

	/* Initialize SPI Bus Mode */
		switch (u8SpiBusMode) {
			case SPI_BUS_CONFIG_FD:
				psSpiHandle->psSpiBaseAddr->CR1 &= ~((0x01 << 15U) | (0x01 << 10U));
				break;

			case SPI_BUS_CONFIG_HD:
				psSpiHandle->psSpiBaseAddr->CR1 |= (0x01 << 15U);
				psSpiHandle->psSpiBaseAddr->CR1 &= ~(0x01 << 10U);
				break;

			case SPI_BUS_CONFIG_SIMPLEX_RXONLY:
				psSpiHandle->psSpiBaseAddr->CR1 |= (0x01 << 10U);
				psSpiHandle->psSpiBaseAddr->CR1 &= ~(0x01 << 15U);
				break;

			default:
				break;
		}

	/* Initialize SPI Baud Rate */
	psSpiHandle->psSpiBaseAddr->CR1 &= ~(0x07 << 3U);
	psSpiHandle->psSpiBaseAddr->CR1 |= ((psSpiHandle->sSpiConfig->u8SpiSclkSpeed & 0x07) << 3U);

	/* Initialize SPI Data Frame Format */
	psSpiHandle->psSpiBaseAddr->CR1 &= ~(0x01 << 11U);
	psSpiHandle->psSpiBaseAddr->CR1 |= ((psSpiHandle->sSpiConfig->u8SpiDff & 0x01) << 11U);

	/* Initialize SPI Clock Polarity */
	psSpiHandle->psSpiBaseAddr->CR1 &= ~(0x01 << 1U);
	psSpiHandle->psSpiBaseAddr->CR1 |= ((psSpiHandle->sSpiConfig->u8SpiCpol & 0x01) << 1U);

	/* Initialize SPI Clock Phase */
	psSpiHandle->psSpiBaseAddr->CR1 &= ~(0x01 << 0U);
	psSpiHandle->psSpiBaseAddr->CR1 |= ((psSpiHandle->sSpiConfig->u8SpiCpha & 0x01) << 0U);

	/* Initialize SPI Slave Management */
	psSpiHandle->psSpiBaseAddr->CR1 &= ~(0x01 << 9U);
	psSpiHandle->psSpiBaseAddr->CR1 |= ((psSpiHandle->sSpiConfig->u8SpiSsm & 0x01) << 9U);
}

/* ===========================================================================
 * Function name: vDoSpiDeIni()
 * Parameters   :
 * 					TS_SPI_REG_DEF *psSpi - SPI Definition
 * Return       : void
 * ===========================================================================
 */
void vDoSpiDeIni(TS_SPI_REG_DEF *psSpi)
{
	if(psSpi == SPI1)
	{
		SPI1_REG_RESET();
	}
	else if (psSpi == SPI2)
	{
		SPI2_REG_RESET();
	}
	else if (psSpi == SPI3)
	{
		SPI3_REG_RESET();
	}
	else if (psSpi == SPI4)
	{
		SPI4_REG_RESET();
	}
}

/* SPI Data Send and Receive functions */

/* ===========================================================================
 * Function name: vDoSpiSendData()
 * Parameters   :
 * 					TS_SPI_REG_DEF *psSpi - SPI Definition
 * 					uint8_t *pu8SpiTxBuff - Address of TX Buffer
 * 					uint32_t u32SpiDataLen - SPI TX Buffer length
 * Return       : void
 * ===========================================================================
 */

void vDoSpiSendData(TS_SPI_REG_DEF *psSpi, uint8_t *pu8SpiTxBuff, uint32_t u32SpiDataLen)
{
	static uint32_t u32SpiLen ;

	for(u32SpiLen = 0; u32SpiLen < u32SpiDataLen ; ++u32SpiLen)
	{
		while(!bDoGetSpiFlag(psSpi, SPI_TXE_FLAG));			/* Wait until TX buffer is not empty */

		if((psSpi->CR1 & (0x01 << 11U)) != 0x00)
		{
			psSpi->DR = *((uint16_t*)pu8SpiTxBuff);			/* Load 16 bits into SPI_DR register */
			++u32SpiLen;									/* Increment loop counter            */
			(uint16_t*)pu8SpiTxBuff++;
		}
		else
		{
			psSpi->DR = *pu8SpiTxBuff;						/* Load 8 bits into SPI_DR register  */
			pu8SpiTxBuff++;
		}
	}
}

/* ===========================================================================
 * Function name: vDoSpiReceiveData()
 * Parameters   :
 * 					TS_SPI_REG_DEF *psSpi - SPI Definition
 * 					uint8_t *pu8SpiRxBuff - Address of RX Buffer
 * 					uint32_t u32SpiDataLen - SPI RX Buffer length
 * Return       : void
 * ===========================================================================
 */

void vDoSpiReceiveData(TS_SPI_REG_DEF *psSpi, uint8_t *pu8SpiRxBuff, uint32_t u32SpiDataLen)
{
	static uint32_t u32SpiLen ;

	for(u32SpiLen = 0; u32SpiLen < u32SpiDataLen ; ++u32SpiLen)
	{
		while(!bDoGetSpiFlag(psSpi, SPI_RXNE_FLAG));		/* Wait until RX buffer is not empty */

		if((psSpi->CR1 & (0x01 << 11U)) != 0x00)
		{
			*((uint16_t*)pu8SpiRxBuff) = psSpi->DR;			/* Read 16 bits from SPI_DR register */
			++u32SpiLen;									/* Increment loop counter            */
			(uint16_t*)pu8SpiRxBuff++;
		}
		else
		{
			*pu8SpiRxBuff = psSpi->DR;						/* Read 8 bits from SPI_DR register  */
			pu8SpiRxBuff++;
		}
	}
}

/* SPI Peripheral control function */

/* ===========================================================================
 * Function name: vDoSpiPeriControl()
 * Parameters   :
 * 					TS_SPI_REG_DEF *psSpi - SPI Definition
 * 					boolean bState - State of SPI peripheral
 * Return       : void
 * ===========================================================================
 */

void vDoSpiPeriControl(TS_SPI_REG_DEF *psSpi, bool bState)
{
	if(bState)
	{
		psSpi->CR1 |= (0x01 << 6U);
	}
	else
	{
		psSpi->CR1 &= ~(0x01 << 6U);
	}
}

/* SPI SSI control function */

/* ===========================================================================
 * Function name: vDoSpiSsiControl()
 * Parameters   :
 * 					TS_SPI_REG_DEF *psSpi - SPI Definition
 * 					boolean bState - State of SPI SSI
 * Return       : void
 * ===========================================================================
 */

void vDoSpiSsiControl(TS_SPI_REG_DEF *psSpi, bool bState)
{
	if(bState)
	{
		psSpi->CR1 |= (0x01 << 8U);
	}
	else
	{
		psSpi->CR1 &= ~(0x01 << 8U);
	}
}
