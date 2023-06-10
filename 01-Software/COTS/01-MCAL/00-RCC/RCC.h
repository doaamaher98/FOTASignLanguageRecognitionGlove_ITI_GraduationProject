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





/* ================================================ User Defined Types ================================================ */
/* Error Status Type */
typedef enum 
{
	RCC_enuOK=0,
	RCC_enuNOK,
}RCC_tenuErrorStatus;

/* Processor Clock Type */
typedef enum
{
	RCC_enuHSI =0,					// Internal RC   = 8Mhz
	RCC_enuHSE,						// Crystal = 4 to 16Mhz, RC = upto 25Mhz
	RCC_enuPLL_DIV2,				// To Amplify the clock upto 72Mhz
	RCC_enuLSE,
	RCC_enuExternalSrc,
	RCC_enuLSI,
	RCC_enuNumberOfClocks
}RCC_tenuClockSource;

/* PLL Multiplication Factor */
typedef enum 
{
	RCC_enuPLL_2 = 0,
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

/* Interrupt Source */
typedef enum
{
	
	
	
}

/* Peripherals Clock Enable/Disable */
typedef enum
{
	RCC_enu=0,
}RCC_tenuBusType;

/* ================================================ APIs ================================================ */
/* ====================================================================================================== */

/* Inputs        : System Clock choice from the options										*/
/* 				   Options :-																*/
/* 				   ----------																*/
/* 				   1- 															*/
/*				   2- 															*/
/*				   3- 															*/
/* Return        : Error Status (To ensure function Safety)                                 */
/* Functionality : Selecting the System's Clock Source                                      */





#endif