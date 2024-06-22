#ifndef INC_STM32F401XX_H_
#define INC_STM32F401XX_H_

#include <stdint.h>
#include <stdbool.h>

/* === STM32 F401xx BASE ADDRESSES === */

/* Base addresses of Flash, SRAM and ROM memories */

#define FLASH_BASEADDR				0x08000000U			/* Flash memory base address*/
#define SRAM1_BASEADDR				0x20000000U			/* SRAM1 memory base address*/
#define SRAM						SRAM1_BASEADDR		/* SRAM  memory base address*/
#define ROM_BASEADDR				0x1FFF0000U			/* ROM   memory base address*/

/* Buses addresses */

#define PERIPH_BASEADDR				0x40000000U			/* Peripheral buses base address */
#define APB1_BASEADDR				PERIPH_BASEADDR		/* APB1 base address */
#define APB2_BASEADDR				0x40010000U			/* APB2 base address */
#define AHB1_BASEADDR				0x40020000U			/* AHB1 base address */
#define AHB2_BASEADDR				0x50000000U			/* AHB2 base address */

/* GPIOs addresses */

#define GPIOA_BASEADDR				AHB1_BASEADDR		/* GPIOA base address */
#define GPIOB_BASEADDR				0x40020400U			/* GPIOB base address */
#define GPIOC_BASEADDR				0x40020800U			/* GPIOC base address */
#define GPIOD_BASEADDR				0x40020C00U			/* GPIOD base address */
#define GPIOE_BASEADDR				0x40021000U			/* GPIOE base address */
#define GPIOH_BASEADDR				0x40021C00U			/* GPIOH base address */

/* I2C addresses */

#define I2C1_BASEADDR				0x40005400U			/* I2C1 base address */
#define I2C2_BASEADDR				0x40005800U			/* I2C2 base address */
#define I2C3_BASEADDR				0x40005C00U			/* I2C3 base address */

/* SPI addresses */

#define SPI1_BASEADDR				0x40013000U			/* SPI1 base address */
#define SPI2_BASEADDR				0x40003800U			/* SPI2 base address */
#define SPI3_BASEADDR				0x40003C00U			/* SPI3 base address */
#define SPI4_BASEADDR				0x40013400U			/* SPI4 base address */

/* USART addresses */

#define USART1_BASEADDR				0x40011000U			/* USART1 base address */
#define USART2_BASEADDR				0x40004400U			/* USART2 base address */
#define USART6_BASEADDR				0x40014000U			/* USART6 base address */

/* EXTI address */

#define EXTI_BASEADDR				0x40013C00U			/* EXTI base address */

/* SYSCFG address */

#define SYSCFG_BASEADDR				0x40013800U			/* SYSCFG base address */

/* RCC address */

#define RCC_BASEADDR				0x40023800U			/* RCC base address */

/* NVIC address */

#define NVIC_BASEADDR				0xE000E100U			/* NVIC base address */

/* === Configuration structures === */

/* GPIOs configuration structure */

typedef struct
{
	volatile uint32_t MODER;							/* Address offset: 0x00 */
	volatile uint32_t OTYPER;							/* Address offset: 0x04 */
	volatile uint32_t OSPEEDR;							/* Address offset: 0x08 */
	volatile uint32_t PUPDR;							/* Address offset: 0x0C */
	volatile uint32_t IDR;								/* Address offset: 0x10 */
	volatile uint32_t ODR;								/* Address offset: 0x14 */
	volatile uint32_t BSRR;								/* Address offset: 0x18 */
	volatile uint32_t LCKR;								/* Address offset: 0x1C */
	volatile uint32_t AFR[2];							/* Address offset: 0x20 and 0x24 */
} TS_GPIO_REG_DEF;

/* I2Cs configuration structure */

typedef struct
{
	volatile uint32_t CR1;								/* Address offset: 0x00 */
	volatile uint32_t CR2;								/* Address offset: 0x04 */
	volatile uint32_t OAR1;								/* Address offset: 0x08 */
	volatile uint32_t OAR2;								/* Address offset: 0x0C */
	volatile uint32_t DR;								/* Address offset: 0x10 */
	volatile uint32_t SR1;								/* Address offset: 0x14 */
	volatile uint32_t SR2;								/* Address offset: 0x18 */
	volatile uint32_t CCR;								/* Address offset: 0x1C */
	volatile uint32_t TRICE;							/* Address offset: 0x20 */
	volatile uint32_t FLTR;								/* Address offset: 0x24 */
} TS_I2C_REG_DEF;

/* SPIs configuration structure */

typedef struct
{
	volatile uint32_t CR1;								/* Address offset: 0x00 */
			 uint32_t Reserved1;
	volatile uint32_t SR;								/* Address offset: 0x08 */
	volatile uint32_t DR;								/* Address offset: 0x0C */
	volatile uint32_t CRCPR;							/* Address offset: 0x10 */
	volatile uint32_t RXCRCR;							/* Address offset: 0x14 */
	volatile uint32_t TXCRCR;							/* Address offset: 0x18 */
	volatile uint32_t I2SCFGR;							/* Address offset: 0x1C */
	volatile uint32_t I2SPR;							/* Address offset: 0x20 */
} TS_SPI_REG_DEF;

/* USARTs configuration structure */

typedef struct
{
	volatile uint32_t SR;								/* Address offset: 0x00 */
	volatile uint32_t DR;								/* Address offset: 0x04 */
	volatile uint32_t BRR;								/* Address offset: 0x08 */
	volatile uint32_t CR1;								/* Address offset: 0x0C */
	volatile uint32_t CR2;								/* Address offset: 0x10 */
	volatile uint32_t CR3;								/* Address offset: 0x14 */
	volatile uint32_t GTPR;								/* Address offset: 0x18 */
} TS_USART_REG_DEF;

/* EXTI configuration structure */

typedef struct
{
	volatile uint32_t IMR;								/* Address offset: 0x00 */
	volatile uint32_t EMR;								/* Address offset: 0x04 */
	volatile uint32_t RTSR;								/* Address offset: 0x08 */
	volatile uint32_t FTSR;								/* Address offset: 0x0C */
	volatile uint32_t SWIER;							/* Address offset: 0x10 */
	volatile uint32_t PR;								/* Address offset: 0x14 */
} TS_EXTI_REG_DEF;

/* EXTI configuration structure */

typedef struct
{
	volatile uint32_t MEMRMP;							/* Address offset: 0x00 */
	volatile uint32_t PMC;								/* Address offset: 0x04 */
	volatile uint32_t EXTICR[4];						/* Address offset: 0x08 */
			 uint32_t Reserved1;
			 uint32_t Reserved2;
	volatile uint32_t CMPCR;							/* Address offset: 0x20 */
} TS_SYSCFG_REG_DEF;

/* RCC configuration structure */

typedef struct
{
	volatile uint32_t CR;								/* Address offset: 0x00 */
	volatile uint32_t PLLCFGR;							/* Address offset: 0x04 */
	volatile uint32_t CFGR;								/* Address offset: 0x08 */
	volatile uint32_t CIR;								/* Address offset: 0x0C */
	volatile uint32_t AHB1RSTR;							/* Address offset: 0x10 */
	volatile uint32_t AHB2RSTR;							/* Address offset: 0x14 */
			 uint32_t Reserved1;
			 uint32_t Reserved2;
	volatile uint32_t APB1RSTR;							/* Address offset: 0x20 */
	volatile uint32_t APB2RSTR;							/* Address offset: 0x24 */
			 uint32_t Reserved3;
			 uint32_t Reserved4;
	volatile uint32_t AHB1ENR;							/* Address offset: 0x30 */
	volatile uint32_t AHB2ENR;							/* Address offset: 0x34 */
			 uint32_t Reserved5;
			 uint32_t Reserved6;
	volatile uint32_t APB1ENR;							/* Address offset: 0x40 */
	volatile uint32_t APB2ENR;							/* Address offset: 0x44 */
			 uint32_t Reserved7;
			 uint32_t Reserved8;
	volatile uint32_t AHB1LPENR;						/* Address offset: 0x50 */
	volatile uint32_t AHB2LPENR;						/* Address offset: 0x54 */
			 uint32_t Reserved9;
			 uint32_t Reserved10;
	volatile uint32_t APB1LPENR;						/* Address offset: 0x60 */
	volatile uint32_t APB2LPENR;						/* Address offset: 0x64 */
			 uint32_t Reserved11;
			 uint32_t Reserved12;
	volatile uint32_t BDCR;								/* Address offset: 0x70 */
	volatile uint32_t CSR;								/* Address offset: 0x74 */
			 uint32_t Reserved13;
			 uint32_t Reserved14;
	volatile uint32_t SSCGR;							/* Address offset: 0x80 */
	volatile uint32_t PLLI2SCFGR;						/* Address offset: 0x84 */
	 	 	 uint32_t Reserved15;
	volatile uint32_t DCKCFGR;							/* Address offset: 0x8C */
} TS_RCC_REG_DEF;

/* NVIC configuration structure */

typedef struct
{
	volatile uint32_t ISER[8];							/* Offset: 0x0100 */
			 uint32_t Reserved1[24];
	volatile uint32_t ICER[8];							/* Offset: 0x0180 */
			 uint32_t Reserved2[24];
	volatile uint32_t ISPR[8];							/* Offset: 0x0200 */
			 uint32_t Reserved3[24];
	volatile uint32_t ICPR[8];							/* Offset: 0x0280 */
			 uint32_t Reserved4[24];
	volatile uint32_t IABR[8];							/* Offset: 0x0300 */
			 uint32_t Reserved5[56];
	volatile uint32_t IPR[60];							/* Offset: 0x0400 */
			 uint32_t Reserved6[644];
	volatile uint32_t STIR;								/* Offset: 0x0E00 */
} TS_NVIC_REG_DEF;

/* === Peripheral definitions === */

/* GPIOs definitions */

#define GPIOA						((TS_GPIO_REG_DEF*) GPIOA_BASEADDR)
#define GPIOB						((TS_GPIO_REG_DEF*) GPIOB_BASEADDR)
#define GPIOC						((TS_GPIO_REG_DEF*) GPIOC_BASEADDR)
#define GPIOD						((TS_GPIO_REG_DEF*) GPIOD_BASEADDR)
#define GPIOE						((TS_GPIO_REG_DEF*) GPIOE_BASEADDR)
#define GPIOH						((TS_GPIO_REG_DEF*) GPIOH_BASEADDR)

/* I2Cs definitions */

#define I2C1						((TS_I2C_REG_DEF*) I2C1_BASEADDR)
#define I2C2						((TS_I2C_REG_DEF*) I2C2_BASEADDR)
#define I2C3						((TS_I2C_REG_DEF*) I2C3_BASEADDR)

/* SPIs definitions */
#define SPI1						((TS_SPI_REG_DEF*) SPI1_BASEADDR)
#define SPI2						((TS_SPI_REG_DEF*) SPI2_BASEADDR)
#define SPI3						((TS_SPI_REG_DEF*) SPI3_BASEADDR)
#define SPI4						((TS_SPI_REG_DEF*) SPI4_BASEADDR)

/* USARTs definitions */

#define USART1						((TS_USART_REG_DEF*) USART1_BASEADDR)
#define USART2						((TS_USART_REG_DEF*) USART2_BASEADDR)
#define USART6						((TS_USART_REG_DEF*) USART6_BASEADDR)

/* EXTI definition */

#define EXTI						((TS_EXTI_REG_DEF*) EXTI_BASEADDR)

/* SYSCFG definition */

#define SYSCFG						((TS_SYSCFG_REG_DEF*) SYSCFG_BASEADDR)

/* RCC definition */

#define RCC							((TS_RCC_REG_DEF*) RCC_BASEADDR)

/* NVIC definition */

#define NVIC						((TS_NVIC_REG_DEF*) NVIC_BASEADDR)

/* === Peripheral Clocks enable macros === */

/* GPIOs Clocks enable macros */

#define GPIOA_PCKL_EN()				(RCC->AHB1ENR |= (1 << 0))		/* GPIO A Peripheral clock enable in RCC register */
#define GPIOB_PCKL_EN()				(RCC->AHB1ENR |= (1 << 1))		/* GPIO B Peripheral clock enable in RCC register */
#define GPIOC_PCKL_EN()				(RCC->AHB1ENR |= (1 << 2))		/* GPIO C Peripheral clock enable in RCC register */
#define GPIOD_PCKL_EN()				(RCC->AHB1ENR |= (1 << 3))		/* GPIO D Peripheral clock enable in RCC register */
#define GPIOE_PCKL_EN()				(RCC->AHB1ENR |= (1 << 4))		/* GPIO E Peripheral clock enable in RCC register */
#define GPIOH_PCKL_EN()				(RCC->AHB1ENR |= (1 << 7))		/* GPIO H Peripheral clock enable in RCC register */

/* I2Cs Clocks enable macros */

#define I2C1_PCKL_EN()				(RCC->APB1ENR |= (1 << 21))		/* I2C 1 Peripheral clock enable in RCC register */
#define I2C2_PCKL_EN()				(RCC->APB1ENR |= (1 << 22))		/* I2C 2 Peripheral clock enable in RCC register */
#define I2C3_PCKL_EN()				(RCC->APB1ENR |= (1 << 23))		/* I2C 3 Peripheral clock enable in RCC register */

/* SPIs Clocks enable macros */

#define SPI1_PCKL_EN()				(RCC->APB2ENR |= (1 << 12))		/* SPI 1 Peripheral clock enable in RCC register */
#define SPI2_PCKL_EN()				(RCC->APB1ENR |= (1 << 14))		/* SPI 2 Peripheral clock enable in RCC register */
#define SPI3_PCKL_EN()				(RCC->APB1ENR |= (1 << 15))		/* SPI 3 Peripheral clock enable in RCC register */
#define SPI4_PCKL_EN()				(RCC->APB2ENR |= (1 << 13))		/* SPI 4 Peripheral clock enable in RCC register */

/* USARTs Clocks enable macros */

#define USART1_PCKL_EN()			(RCC->APB2ENR |= (1 << 4))		/* USART 1 Peripheral clock enable in RCC register */
#define USART2_PCKL_EN()			(RCC->APB1ENR |= (1 << 17))		/* USART 2 Peripheral clock enable in RCC register */
#define USART6_PCKL_EN()			(RCC->APB2ENR |= (1 << 5))		/* USART 6 Peripheral clock enable in RCC register */

/* SYSCFG Clock enable macro */

#define SYSCFG_PCKL_EN()			(RCC->APB2ENR |= (1 << 14))		/* SYSCFG Peripheral clock enable in RCC register */

/* === Peripheral Clocks disable macros === */

/* GPIOs Clocks disable macros */

#define GPIOA_PCKL_DI()				(RCC->AHB1ENR &= ~(1 << 0))		/* GPIO A Peripheral clock disable in RCC register */
#define GPIOB_PCKL_DI()				(RCC->AHB1ENR &= ~(1 << 1))		/* GPIO B Peripheral clock disable in RCC register */
#define GPIOC_PCKL_DI()				(RCC->AHB1ENR &= ~(1 << 2))		/* GPIO C Peripheral clock disable in RCC register */
#define GPIOD_PCKL_DI()				(RCC->AHB1ENR &= ~(1 << 3))		/* GPIO D Peripheral clock disable in RCC register */
#define GPIOE_PCKL_DI()				(RCC->AHB1ENR &= ~(1 << 4))		/* GPIO E Peripheral clock disable in RCC register */
#define GPIOH_PCKL_DI()				(RCC->AHB1ENR &= ~(1 << 7))		/* GPIO H Peripheral clock disable in RCC register */

/* I2Cs Clocks disable macros */

#define I2C1_PCKL_DI()				(RCC->APB1ENR &= ~(1 << 21))	/* I2C 1 Peripheral clock disable in RCC register */
#define I2C2_PCKL_DI()				(RCC->APB1ENR &= ~(1 << 22))	/* I2C 2 Peripheral clock disable in RCC register */
#define I2C3_PCKL_DI()				(RCC->APB1ENR &= ~(1 << 23))	/* I2C 3 Peripheral clock disable in RCC register */

/* SPIs Clocks disable macros */

#define SPI1_PCKL_DI()				(RCC->APB2ENR &= ~(1 << 12))	/* SPI 1 Peripheral clock disable in RCC register */
#define SPI2_PCKL_DI()				(RCC->APB1ENR &= ~(1 << 14))	/* SPI 2 Peripheral clock disable in RCC register */
#define SPI3_PCKL_DI()				(RCC->APB1ENR &= ~(1 << 15))	/* SPI 3 Peripheral clock disable in RCC register */
#define SPI4_PCKL_DI()				(RCC->APB2ENR &= ~(1 << 13))	/* SPI 4 Peripheral clock disable in RCC register */

/* USARTs Clocks disable macros */

#define USART1_PCKL_DI()			(RCC->APB2ENR &= ~(1 << 4))		/* USART 1 Peripheral clock disable in RCC register */
#define USART2_PCKL_DI()			(RCC->APB1ENR &= ~(1 << 17))	/* USART 2 Peripheral clock disable in RCC register */
#define USART6_PCKL_DI()			(RCC->APB2ENR &= ~(1 << 5))		/* USART 6 Peripheral clock disable in RCC register */

/* SYSCFG Clock disable macro */

#define SYSCFG_PCKL_DI()			(RCC->APB2ENR &= ~(1 << 14))	/* SYSCFG Peripheral clock disable in RCC register */

/* === GPIOs reset macros === */

#define GPIOA_REG_RESET()			{RCC->AHB1RSTR |= (1 << 0); RCC->AHB1RSTR &= ~(1 << 0);}		/* Reset GPIO A  in RCC register */
#define GPIOB_REG_RESET()			{RCC->AHB1RSTR |= (1 << 1); RCC->AHB1RSTR &= ~(1 << 1);}		/* Reset GPIO B  in RCC register */
#define GPIOC_REG_RESET()			{RCC->AHB1RSTR |= (1 << 2); RCC->AHB1RSTR &= ~(1 << 2);}		/* Reset GPIO C  in RCC register */
#define GPIOD_REG_RESET()			{RCC->AHB1RSTR |= (1 << 3); RCC->AHB1RSTR &= ~(1 << 3);}		/* Reset GPIO D  in RCC register */
#define GPIOE_REG_RESET()			{RCC->AHB1RSTR |= (1 << 4); RCC->AHB1RSTR &= ~(1 << 4);}		/* Reset GPIO E  in RCC register */
#define GPIOH_REG_RESET()			{RCC->AHB1RSTR |= (1 << 7); RCC->AHB1RSTR &= ~(1 << 7);}		/* Reset GPIO H  in RCC register */

/* === IRQ(Interrupt Request) Numbers === */

#define IRQ_NO_EXTI0				6
#define IRQ_NO_EXTI1				7
#define IRQ_NO_EXTI2				8
#define IRQ_NO_EXTI3				9
#define IRQ_NO_EXTI4				10
#define IRQ_NO_EXTI9_5				23
#define IRQ_NO_EXTI15_10			40

#define NVIC_IRQ_PRI0				0
#define NVIC_IRQ_PRI1				1
#define NVIC_IRQ_PRI2				2
#define NVIC_IRQ_PRI3				3
#define NVIC_IRQ_PRI4				4
#define NVIC_IRQ_PRI5				5
#define NVIC_IRQ_PRI6				6
#define NVIC_IRQ_PRI7				7
#define NVIC_IRQ_PRI8				8
#define NVIC_IRQ_PRI9				9
#define NVIC_IRQ_PRI10				10
#define NVIC_IRQ_PRI11				11
#define NVIC_IRQ_PRI12				12
#define NVIC_IRQ_PRI13				13
#define NVIC_IRQ_PRI14				14
#define NVIC_IRQ_PRI15				15

#endif /* INC_STM32F401XX_H_ */
