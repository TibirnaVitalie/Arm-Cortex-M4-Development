#ifndef INC_STM32F401XX_SPI_DRIVER_H_
#define INC_STM32F401XX_SPI_DRIVER_H_

/* Include external headers */
#include "stm32f401xx.h"

typedef struct
{
	uint8_t u8SpiDeviceMode;							/* SPI Device Mode */
	uint8_t u8SpiBusConfig;								/* SPI BUS Configuration */
	uint8_t u8SpiSclkSpeed;								/* SPI Serial Clock speed setting */
	uint8_t u8SpiDFF;									/* SPI Data Frame Format */
	uint8_t u8SpiCpol;									/* SPI Serial Clock Polarity */
	uint8_t u8SpiApha;									/* SPI Serial Clock Phase */
	uint8_t u8SpiSsm;									/* SPI Software Slave Management */
} TS_SPI_CONFIG;

typedef struct
{
	TS_SPI_REG_DEF *psSpiBaseAddr;						/* SPI Base Address */
	TS_SPI_CONFIG *sSpiConfig;							/* SPI configuration settings */
} TS_SPI_HANDLE;

/* === APIs supported by this driver === */

/* SPI Peripheral Clock control function */

void vDoSpiPeriClockControl(TS_SPI_REG_DEF *psSpi, bool bState);

/* SPI Init/DeInit functions */

void vDoSpiIni(TS_SPI_HANDLE *psSpiHandle);
void vDoSpiDeIni(TS_SPI_REG_DEF *psSpi);

/* SPI Data Send and Receive functions */

void vDoSpiSendData(TS_SPI_REG_DEF *psSpi, uint8_t *pu8SpiTxBuff, uint32_t u32SpiDataLen);
void vDoSpiReceiveData(TS_SPI_REG_DEF *psSpi, uint8_t *pu8SpiRxBuff, uint32_t u32SpiDataLen);

/* SPI IRQ configuration and ISR handling functions */

void vDoSpiIrqConfig(TS_NVIC_REG_DEF *psNvic, uint8_t u8IrqNumber, uint8_t u8IrqPriority, bool bIqrState);
void vDoSpiIrqHandling(TS_EXTI_REG_DEF *psExti, TS_SPI_HANDLE *psSpiHandle);

#endif /* INC_STM32F401XX_SPI_DRIVER_H_ */
