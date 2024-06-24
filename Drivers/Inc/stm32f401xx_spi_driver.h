#ifndef INC_STM32F401XX_SPI_DRIVER_H_
#define INC_STM32F401XX_SPI_DRIVER_H_

/* Include external headers */
#include "stm32f401xx.h"

typedef struct
{
	uint8_t u8SpiDeviceMode;							/* SPI Device Mode */
	uint8_t u8SpiBusConfig;								/* SPI BUS Configuration */
	uint8_t u8SpiSclkSpeed;								/* SPI Serial Clock speed setting */
	uint8_t u8SpiDff;									/* SPI Data Frame Format */
	uint8_t u8SpiCpol;									/* SPI Serial Clock Polarity */
	uint8_t u8SpiCpha;									/* SPI Serial Clock Phase */
	uint8_t u8SpiSsm;									/* SPI Software Slave Management */
} TS_SPI_CONFIG;

typedef struct
{
	TS_SPI_REG_DEF *psSpiBaseAddr;						/* SPI Base Address */
	TS_SPI_CONFIG *sSpiConfig;							/* SPI configuration settings */
} TS_SPI_HANDLE;

/* === SPIs possible modes === */

/* SPI possible device modes */

#define SPI_DEVICE_MOVE_SLAVE							0x00
#define SPI_DEVICE_MOVE_MASTER							0x01

/* SPI BUS possible modes */

#define SPI_BUS_CONFIG_FD								0x00
#define SPI_BUS_CONFIG_HD								0x01
#define SPI_BUS_CONFIG_SIMPLEX_RXONLY					0x02

/* SPI Baud Rate control */

#define SPI_SPEED_PCLK_DIV2								0x00
#define SPI_SPEED_PCLK_DIV4								0x01
#define SPI_SPEED_PCLK_DIV8								0x02
#define SPI_SPEED_PCLK_DIV16							0x03
#define SPI_SPEED_PCLK_DIV32							0x04
#define SPI_SPEED_PCLK_DIV64							0x05
#define SPI_SPEED_PCLK_DIV128							0x06
#define SPI_SPEED_PCLK_DIV256							0x07

/* SPI Data Frame Format control */

#define SPI_DFF_8BITS									0x00
#define SPI_DFF_16BITS									0x01

/* SPI Clock Polarity control */

#define SPI_CPOL_LOW									0x00
#define SPI_CPOL_HIGH									0x01

/* SPI Clock Phase control */

#define SPI_CPHA_LOW									0x00
#define SPI_CPHA_HIGH									0x01

/* SPI Software Slave Management control */

#define SPI_SSM_SW										0x00
#define SPI_SSM_HW										0x01

/* === SPIs macros === */

/* SPI Status flags (SPI_SR Register) */

#define SPI_RXNE_FLAG									0x00
#define SPI_TXE_FLAG									0x01
#define SPI_CHSIDE_FLAG									0x02
#define SPI_UDR_FLAG									0x03
#define SPI_CRCERR_FLAG									0x04
#define SPI_MODF_FLAG									0x05
#define SPI_OVR_FLAG									0x06
#define SPI_BSY_FLAG									0x07
#define SPI_FRE_FLAG									0x08

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

/* SPI Peripheral control */

void vDoSpiPeriControl(TS_SPI_REG_DEF *psSpi, bool bState);
void vDoSpiSsiControl(TS_SPI_REG_DEF *psSpi, bool bState);

#endif /* INC_STM32F401XX_SPI_DRIVER_H_ */
