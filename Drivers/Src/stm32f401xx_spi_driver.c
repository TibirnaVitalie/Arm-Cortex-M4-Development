/* === Include external headers === */


/* === Include own header === */
#include "stm32f401xx_spi_driver.h"

/* === Local Functions === */

static inline void vDoSpiTxeHandle(TS_SPI_HANDLE *psSpiHandle);
static inline void vDoSpiRxneHandle(TS_SPI_HANDLE *psSpiHandle);
static inline void vDoSpiOvrHandle(TS_SPI_HANDLE *psSpiHandle);

/* SPI interrupts handle functions */

/* ===========================================================================
 * Function name: vDoSpiTxeHandle()
 * Parameters   :
 * 					TS_SPI_HANDLE *psSpiHandle - SPI Handle
 * Return       : void
 * ===========================================================================
 */

static inline void vDoSpiTxeHandle(TS_SPI_HANDLE *psSpiHandle)
{
	if((psSpiHandle->psSpiBaseAddr->CR1 & (0x01 << 11U)) != 0x00)
	{
		/* Load 16 bits into SPI_DR register */
		psSpiHandle->psSpiBaseAddr->DR = *((uint16_t*)psSpiHandle->pu8SpiTxBuff);
		--psSpiHandle->u32SpiTxBuffLen;
		--psSpiHandle->u32SpiTxBuffLen;
		(uint16_t*)psSpiHandle->pu8SpiTxBuff++;
	}
	else
	{
		/* Load 8 bits into SPI_DR register */
		psSpiHandle->psSpiBaseAddr->DR = *psSpiHandle->pu8SpiTxBuff;
		--psSpiHandle->u32SpiTxBuffLen;
		psSpiHandle->pu8SpiTxBuff++;
	}

	if(0U == psSpiHandle->u32SpiTxBuffLen)
	{
		vDoSpiCloseTransmission(psSpiHandle);
		vDoSpiEventCallback(psSpiHandle, eStatusEventSpiTxDone);
	}
}

/* ===========================================================================
 * Function name: vDoSpiRxneHandle()
 * Parameters   :
 *					TS_SPI_HANDLE *psSpiHandle - SPI Handle
 * Return       : void
 * ===========================================================================
 */

static inline void vDoSpiRxneHandle(TS_SPI_HANDLE *psSpiHandle)
{
	if((psSpiHandle->psSpiBaseAddr->CR1 & (0x01 << 11U)) != 0x00)
	{
		/* Read 16 bits from SPI_DR register */
		*((uint16_t*)psSpiHandle->pu8SpiRxBuff) = psSpiHandle->psSpiBaseAddr->DR;
		--psSpiHandle->u32SpiRxBuffLen;
		--psSpiHandle->u32SpiRxBuffLen;
		(uint16_t*)psSpiHandle->pu8SpiRxBuff++;
	}
	else
	{
		/* Read 8 bits from SPI_DR register */
		*psSpiHandle->pu8SpiRxBuff = psSpiHandle->psSpiBaseAddr->DR;
		--psSpiHandle->u32SpiRxBuffLen;
		psSpiHandle->pu8SpiRxBuff++;
	}

	if(0U == psSpiHandle->u32SpiRxBuffLen)
	{
		vDoSpiCloseReception(psSpiHandle);
		vDoSpiEventCallback(psSpiHandle, eStatusEventSpiRxDone);
	}
}

/* ===========================================================================
 * Function name: vDoSpiOvrHandle()
 * Parameters   :
 * 					TS_SPI_HANDLE *psSpiHandle - SPI Handle
 * Return       : void
 * ===========================================================================
 */

static inline void vDoSpiOvrHandle(TS_SPI_HANDLE *psSpiHandle)
{
	if(eStateSpiBusBusyTx != psSpiHandle->eStateSpiBus)
	{
		vDoSpiClearOvrFlag(psSpiHandle->psSpiBaseAddr);
	}

	/* Inform the application */
	vDoSpiEventCallback(psSpiHandle, eStatusEventSpiOvrErr);
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
	uint8_t u8SpiBusMode = (psSpiHandle->psSpiConfig->u8SpiBusConfig & 0x03);

	/* Initialize SPI Device Mode */
	psSpiHandle->psSpiBaseAddr->CR1 &= ~(0x01 << 2U);
	psSpiHandle->psSpiBaseAddr->CR1 |= ((psSpiHandle->psSpiConfig->u8SpiDeviceMode & 0x01) << 2U);

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
	psSpiHandle->psSpiBaseAddr->CR1 |= ((psSpiHandle->psSpiConfig->u8SpiSclkSpeed & 0x07) << 3U);

	/* Initialize SPI Data Frame Format */
	psSpiHandle->psSpiBaseAddr->CR1 &= ~(0x01 << 11U);
	psSpiHandle->psSpiBaseAddr->CR1 |= ((psSpiHandle->psSpiConfig->u8SpiDff & 0x01) << 11U);

	/* Initialize SPI Clock Polarity */
	psSpiHandle->psSpiBaseAddr->CR1 &= ~(0x01 << 1U);
	psSpiHandle->psSpiBaseAddr->CR1 |= ((psSpiHandle->psSpiConfig->u8SpiCpol & 0x01) << 1U);

	/* Initialize SPI Clock Phase */
	psSpiHandle->psSpiBaseAddr->CR1 &= ~(0x01 << 0U);
	psSpiHandle->psSpiBaseAddr->CR1 |= ((psSpiHandle->psSpiConfig->u8SpiCpha & 0x01) << 0U);

	/* Initialize SPI Slave Management */
	psSpiHandle->psSpiBaseAddr->CR1 &= ~(0x01 << 9U);
	psSpiHandle->psSpiBaseAddr->CR1 |= ((psSpiHandle->psSpiConfig->u8SpiSsm & 0x01) << 9U);
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

/* Interrupts based SPI Data Send and Receive functions */

/* ===========================================================================
 * Function name: vDoSpiSendDataIt()
 * Parameters   :
 * 					TS_SPI_HANDLE *psSpiHandle - SPI Handle structure
 * 					uint8_t *pu8SpiTxBuff - Address of TX Buffer
 * 					uint32_t u32SpiDataLen - SPI TX Buffer length
 * Return       : TE_SPI_BUS_STATE - State of SPI Bus
 * ===========================================================================
 */

TE_SPI_BUS_STATE vDoSpiSendDataIt(TS_SPI_HANDLE *psSpiHandle, uint8_t *pu8SpiTxBuff, uint32_t u32SpiDataLen)
{
	TE_SPI_BUS_STATE eStateSpiBus = psSpiHandle->eStateSpiBus;

	if(eStateSpiBus != eStateSpiBusBusyTx)
	{
		/* Store TX Buffer address and TX Buffer length in handle structure */
		psSpiHandle->pu8SpiTxBuff = pu8SpiTxBuff;
		psSpiHandle->u32SpiTxBuffLen = u32SpiDataLen;

		/* Set SPI Bus in TX busy mode */
		psSpiHandle->eStateSpiBus = eStateSpiBusBusyTx;

		/* Enable interrupt on TXE Flag in SPI_SR register */
		psSpiHandle->psSpiBaseAddr->CR2 |= (0x01 << 7U);
	}

	return eStateSpiBus;
}

/* ===========================================================================
 * Function name: vDoSpiReceiveDataIt()
 * Parameters   :
 * 					TS_SPI_HANDLE *psSpiHandle - SPI Handle structure
 * 					uint8_t *pu8SpiRxBuff - Address of RX Buffer
 * 					uint32_t u32SpiDataLen - SPI RX Buffer length
 * Return       : TE_SPI_BUS_STATE - State of SPI Bus
 * ===========================================================================
 */

TE_SPI_BUS_STATE vDoSpiReceiveDataIt(TS_SPI_HANDLE *psSpiHandle, uint8_t *pu8SpiRxBuff, uint32_t u32SpiDataLen)
{
	TE_SPI_BUS_STATE eStateSpiBus = psSpiHandle->eStateSpiBus;

	if(eStateSpiBus != eStateSpiBusBusyRx)
	{
		/* Store RX Buffer address and RX Buffer length in handle structure */
		psSpiHandle->pu8SpiRxBuff = pu8SpiRxBuff;
		psSpiHandle->u32SpiRxBuffLen = u32SpiDataLen;

		/* Set SPI Bus in RX busy mode */
		psSpiHandle->eStateSpiBus = eStateSpiBusBusyRx;

		/* Enable interrupt on RXNE Flag in SPI_SR register */
		psSpiHandle->psSpiBaseAddr->CR2 |= (0x01 << 6U);
	}

	return eStateSpiBus;
}

/* SPI IRQ configuration and ISR handling functions */

/* ===========================================================================
 * Function name: vDoSpiIrqConfig()
 * Parameters   :
 * 					TS_NVIC_REG_DEF *psNvic - NIVC definition
 * 					uint8_t u8IqrNumber - IQR Number
 * 					uint8_t u8IqrPriority - IQR Priority
 * 					boolean bIqrState - State of IQR
 * Return       : void
 * ===========================================================================
 */
void vDoSpiIrqConfig(TS_NVIC_REG_DEF *psNvic, uint8_t u8IrqNumber, uint8_t u8IrqPriority, bool bIqrState)
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
 * Function name: vDoSpiIrqHandling()
 * Parameters   :
 * 					TS_EXTI_REG_DEF *psExti - EXTI definition
 * 					TS_SPI_HANDLE *psSpiHandle - SPI Handle
 * Return       : void
 * ===========================================================================
 */

void vDoSpiIrqHandling(TS_EXTI_REG_DEF *psExti, TS_SPI_HANDLE *psSpiHandle)
{
	if(psSpiHandle->psSpiBaseAddr->CR2 & (0x01 << 7U) &&
	   psSpiHandle->psSpiBaseAddr->SR  & (0x01 << 1U))
	{
		vDoSpiTxeHandle(psSpiHandle);
	}

	if(psSpiHandle->psSpiBaseAddr->CR2 & (0x01 << 6U) &&
	   psSpiHandle->psSpiBaseAddr->SR  & (0x01 << 0U))
	{
		vDoSpiRxneHandle(psSpiHandle);
	}

	if(psSpiHandle->psSpiBaseAddr->CR2 & (0x01 << 5U) &&
	   psSpiHandle->psSpiBaseAddr->SR  & (0x01 << 6U))
	{
		vDoSpiOvrHandle(psSpiHandle);
	}

}

/* SPI Peripheral control functions */

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

/* ===========================================================================
 * Function name: vDoSpiClearOvrFlag()
 * Parameters   :
 * 					TS_SPI_REG_DEF *psSpi - SPI Definition
 * Return       : void
 * ===========================================================================
 */

void vDoSpiClearOvrFlag(TS_SPI_REG_DEF *psSpi)
{
	uint32_t u32RegisterVal = 0;

	/* Clear OVR flag */
	u32RegisterVal = psSpi->DR;
	u32RegisterVal = psSpi->SR;

	/* Avoid unused variable warning */
	(void)u32RegisterVal;
}

/* ===========================================================================
 * Function name: vDoSpiCloseTransmission()
 * Parameters   :
 * 					TS_SPI_HANDLE *psSpiHandle - SPI Handle structure
 * Return       : void
 * ===========================================================================
 */

void vDoSpiCloseTransmission(TS_SPI_HANDLE *psSpiHandle)
{
	/* Disable TXE flag interrupts */
	psSpiHandle->psSpiBaseAddr->CR2 &= ~(1 << 7U);
	psSpiHandle->pu8SpiTxBuff = NULL;
	psSpiHandle->u32SpiTxBuffLen = 0;

	/* Inform the application */
	psSpiHandle->eStateSpiBus = eStateSpiBusReady;
}

/* ===========================================================================
 * Function name: vDoSpiCloseReception()
 * Parameters   :
 * 					TS_SPI_HANDLE *psSpiHandle - SPI Handle structure
 * Return       : void
 * ===========================================================================
 */

void vDoSpiCloseReception(TS_SPI_HANDLE *psSpiHandle)
{
	/* Disable RXNE flag interrupts */
	psSpiHandle->psSpiBaseAddr->CR2 &= ~(1 << 6U);

	/* Inform the application */
	psSpiHandle->eStateSpiBus = eStateSpiBusReady;
}
