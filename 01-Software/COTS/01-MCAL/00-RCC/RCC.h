/* ================================================================= */
/* Author 	: Doaa Maher											 */
/* Date		: 8 Jun 2023											 */
/* Target 	: ARM Cortex M3											 */
/* Version  : V1.0													 */
/* Descip. 	: RCC header file										 */
/* ================================================================= */

#ifndef RCC_H
#define RCC_H

/* ================================================ Preprocessor ================================================ */
#include "Std_Types.h"


/* ================================================ User Defined Types ================================================ */
/* Error Status Type */
typedef enum 
{
	RCC_enuOK=0,
	RCC_enuNOK,
	RCC_enuInvalidBus,
	RCC_enuInvalidBusOption,
	RCC_enuInvalidPeripheralID,
	RCC_enuInvalidClockSrc,
	RCC_enuInvalidClockSrcOption,
	RCC_enuTIMEOUT,
	
}RCC_tenuErrorStatus;

/* Processor Clock Type */
typedef enum
{
	RCC_enuHSI =0,					// Internal RC   = 8Mhz
	RCC_enuHSE_CRYSTAL,				// Crystal = 4 to 16Mhz 
	RCC_enuHSE_RC,					// RC = upto 25Mhz
	RCC_enuPLL,						// To Amplify the clock upto 72Mhz
//	RCC_enuLSE,
//	RCC_enuExternalSrc,
//	RCC_enuLSI,
	RCC_enuNumberOfClocks
}RCC_tenuClockSource;

/* Bus Type */
typedef enum
{
	RCC_enuAPB1=0,
	RCC_enuAPB2,
	RCC_enuAHB,
	RCC_enuNumberOfBuses,
}RCC_tenuBusType;


/* PLL INPUT Options */
typedef enum
{
	RCC_enuIN_PLL_HSI_DIV2=0,
	RCC_enuIN_PLL_HSE_DIV2,
	RCC_enuIN_PLL_HSE,
}RCC_tenuPLL_Input;

/* PLL Multiplication Factor */
typedef enum 
{
	RCC_enuPLL_2 = 0b0000,
	RCC_enuPLL_3,
	RCC_enuPLL_4,
	RCC_enuPLL_5,
	RCC_enuPLL_6,
	RCC_enuPLL_7,
	RCC_enuPLL_8,
	RCC_enuPLL_9,
	RCC_enuPLL_10,
	RCC_enuPLL_11,
	RCC_enuPLL_12,
	RCC_enuPLL_13,
	RCC_enuPLL_14,
	RCC_enuPLL_15,
	RCC_enuPLL1_16,
	RCC_enuPLL2_16,
}RCC_tenuPLLMulFactor;

/* APB2 Prescaler */
typedef enum
{
	RCC_enuAPB2_NOT_DIVIDED=0,
	RCC_enuAPB2_DIV_BY_2 = 4,
	RCC_enuAPB2_DIV_BY_4,
	RCC_enuAPB2_DIV_BY_8,
	RCC_enuAPB2_DIV_BY_16,
	RCC_enuNumberOfAPB2Prescalers
}RCC_tenuAPB2Prescaler;


/* APB1 Prescaler */
typedef enum
{
	RCC_enuAPB1_NOT_DIVIDED=0,
	RCC_enuAPB1_DIV_BY_2 = 4,
	RCC_enuAPB1_DIV_BY_4,
	RCC_enuAPB1_DIV_BY_8,
	RCC_enuAPB1_DIV_BY_16,
	RCC_enuNumberOfAPB1Prescalers
}RCC_tenuAPB1Prescaler;


/* AHB Prescaler */
typedef enum
{
	RCC_enuAHB_NOT_DIVIDED=0,
	RCC_enuAHB_DIV_BY_2 = 8,
	RCC_enuAHB_DIV_BY_4,
	RCC_enuAHB_DIV_BY_8,
	RCC_enuAHB_DIV_BY_16,
	RCC_enuAHB_DIV_BY_64,
	RCC_enuAHB_DIV_BY_128,
	RCC_enuAHB_DIV_BY_256,
	RCC_enuAHB_DIV_BY_512,
	RCC_enuNumberOfAHBPrescalers
}RCC_tenuAHBPrescaler;


/* Enable or Disable Peripheral Clock */
typedef enum 
{
	RCC_enuClockDisable=0,
	RCC_enuClockEnable,
	RCC_enuClockRESET,
}RCC_tenuClockStatus;

/* Peripherals Clock Enable/Disable on AHB */
typedef enum
{
	RCC_enuDMA1_EN=0,
	RCC_enuDMA2_EN,
	RCC_enuSRAM_EN,
	RCC_enuFLITF_EN=4,
	RCC_enuCRCEN_EN=6,
	RCC_enuFSMC_EN=8,
	RCC_enuSDIO_EN=10,
}RCC_tenuAHBEnablePeripherals;

/* Peripherals Clock Enable/Disable on APB2 */
typedef enum
{
	RCC_enuAFIO_EN=0,
	RCC_enuGPIOA_EN,
	RCC_enuGPIOB_EN,
	RCC_enuGPIOC_EN,
	RCC_enuGPIOD_EN,
	RCC_enuGPIOE_EN,
	RCC_enuGPIOF_EN,
	RCC_enuGPIOG_EN,
	RCC_enuADC1_EN,
	RCC_enuADC2_EN,
	RCC_enuTMR1_EN,
	RCC_enuSPI1_EN,
	RCC_enuTMR8_EN,
	RCC_enuUSART1_EN,
	RCC_enuADC3_EN,
	RCC_enuTMR9_EN=19,
	RCC_enuTMR10_EN,
	RCC_enuTMR11_EN,
}RCC_tenuAPB2EnablePeripherals;

/* Peripherals Clock Enable/Disable on APB1 */
typedef enum
{
	RCC_enuTMR2_EN=0,
	RCC_enuTMR3_EN,
	RCC_enuTMR4_EN,
	RCC_enuTMR5_EN,
	RCC_enuTMR6_EN,
	RCC_enuTMR7_EN,
	RCC_enuTMR12_EN,
	RCC_enuTMR13_EN,
	RCC_enuTMR14_EN,
	RCC_enuWWD_EN=11,
	RCC_enuSPI2_EN=14,
	RCC_enuSPI3_EN,
	RCC_enuUSART2_EN=17,
	RCC_enuUSART3_EN,
	RCC_enuUSART4_EN,
	RCC_enuUSART5_EN,
	RCC_enuI2C1_EN,
	RCC_enuI2C2_EN,
	RCC_enuUSB_EN,
	RCC_enuCAN_EN=25,
	RCC_enuDAC_EN=29,
}RCC_tenuAPB1EnablePeripherals;


/* Peripherals Clock RESET on APB2 */
typedef enum
{
	RCC_enuTMR11_RST=21,
	RCC_enuTMR10_RST=20,
	RCC_enuTMR9_RST=19,
	RCC_enuADC3_RST=15,
	RCC_enuUSART1_RST=14,
	RCC_enuTMR8_RST=13,
	RCC_enuSPI1_RST=12,
	RCC_enuTMR1_RST=11,
	RCC_enuADC2_RST=10,
	RCC_enuADC1_RST=9,
	RCC_enuGPIOG_RST=8,
	RCC_enuGPIOF_RST=7,
	RCC_enuGPIOE_RST=6,
	RCC_enuGPIOD_RST=5,
	RCC_enuGPIOC_RST=4,
	RCC_enuGPIOB_RST=3,
	RCC_enuGPIOA_RST=2,
	RCC_enuAFIO_RST=0,
}RCC_tenuAPB2ResetPeripherals;

/* Peripherals Clock RESET on APB1 */
typedef enum
{
	RCC_enuDAC_RST=29,
	RCC_enuI2C2_RST=22,
	RCC_enuI2C1_RST=21,
	RCC_enuUART5_RST=20,
	RCC_enuUART4_RST=19,
	RCC_enuUSART3_RST=18,
	RCC_enuUSART2_RST=17,
	RCC_enuSPI3_RST=15,
	RCC_enuSPI2_RST=14,
	RCC_enuWWD_RST =11,
	RCC_enuTMR14_RST=8,
	RCC_enuTMR13_RST=7,
	RCC_enuTMR12_RST=6,
	RCC_enuTMR7_RST=5,
	RCC_enuTMR6_RST=4,
	RCC_enuTMR5_RST=3,
	RCC_enuTMR4_RST=2,
	RCC_enuTMR3_RST=1,
	RCC_enuTMR2_RST=0,
}RCC_tenuAPB1ResetPeripherals;

/* RCC_CR Register Bits */
typedef enum
{
	RCC_enuHSI_ON=0,
	RCC_enuHSI_RDY,
	RCC_enuHSE_ON=16,
	RCC_enuHSE_RDY,
	RCC_enuHSE_BYP,
	RCC_enuCSS_ON,
	RCC_enuPLL_ON=24,
	RCC_enuPLL_RDY,
}RCC_tenuRCC_CR_Register;

/* RCC_CFGR Register Bits */
typedef enum
{
	RCC_enuSW0=0,
	RCC_enuSW1,
	RCC_enuSWS0,
	RCC_enuSWS1,
	RCC_enuAHB_PRE0,
	RCC_enuAHB_PRE1,
	RCC_enuAHB_PRE2,
	RCC_enuAHB_PRE3,
	RCC_enuAPB1_PRE0,
	RCC_enuAPB1_PRE1,
	RCC_enuAPB1_PRE2,
	RCC_enuAPB2_PRE0,
	RCC_enuAPB2_PRE1,
	RCC_enuAPB2_PRE2,
	RCC_enuADC_PRE0,
	RCC_enuADC_PRE1,
	RCC_enuPLL_SRC,
	RCC_enuPLL_HSE,
	RCC_enuMCO0=24,
	RCC_enuMCO1,
	RCC_enuMCO2,
}RCC_tenuRCC_CFGR_Register;


/* Structure of Registers (as they are followed by each other in the memory by 4B) */
typedef struct 
{
	volatile u32 RCC_CR;
	volatile u32 RCC_CFGR;
	volatile u32 RCC_CIR;
	volatile u32 RCC_APB2RSTR;
	volatile u32 RCC_APB1RSTR;
	volatile u32 RCC_AHBENR;
	volatile u32 RCC_APB2ENR;
	volatile u32 RCC_APB1ENR;
	volatile u32 RCC_BDCR;
	volatile u32 RCC_CSR;
}RCC_tstrRegisters_t;



/* ================================================ APIs ================================================ */
/* ====================================================================================================== */

/********************************************************************************************/
/* Inputs        : void																		*/
/* Return        : Error Status (To ensure function Safety)                                 */
/* Functionality : Selecting/Disable the System's Clock Source                  			*/
/********************************************************************************************/
RCC_tenuErrorStatus RCC_enuInitSystemClock (void);


/********************************************************************************************/
/* Inputs        : 1. System Clock choice from the options									*/
/* 				   Options :-																*/
/* 				   ----------																*/
/* 				   1- RCC_enuAPB1															*/
/*				   2- RCC_enuAPB2															*/
/*				   3- RCC_enuAHB															*/
/*				  2. Peripheral ID.															*/
/* Return        : Error Status (To ensure function Safety)                                 */
/* Functionality : Enabling the Peripheral's Clock                                    		*/
/********************************************************************************************/
RCC_tenuErrorStatus RCC_enuEnablePeripheralClk (RCC_tenuBusType Cpy_u8Bus, u8 Cpy_u8Peripheral);


/********************************************************************************************/
/* Inputs        : 1. System Clock choice from the options									*/
/* 				   Options :-																*/
/* 				   ----------																*/
/* 				   1- RCC_enuAPB1															*/
/*				   2- RCC_enuAPB2															*/
/*				   3- RCC_enuAHB															*/
/*				  2. Peripheral ID.															*/
/* Return        : Error Status (To ensure function Safety)                                 */
/* Functionality : Disabling the Peripheral's Clock                                    		*/
/********************************************************************************************/
RCC_tenuErrorStatus RCC_enuDisablePeripheralClk (RCC_tenuBusType Cpy_u8Bus, u8 Cpy_u8Peripheral);



#endif