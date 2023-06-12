/* ================================================================= */
/* Author 	: Doaa Maher											 */
/* Date		: 9 Jun 2023											 */
/* Target 	: ARM Cortex M3											 */
/* Version  : V1.0													 */
/* Descip. 	: GPIO header file										 */
/* ================================================================= */

#ifndef GPIO_H
#define GPIO_H

/* ================================================ Preprocessor ================================================ */
#include "Std_Types.h"

#define					GPIOx_CRL_CLEAR						0x00000000

/* ================================================ User Defined Types ================================================ */
/* Error Status Type */
typedef enum 
{
	GPIO_enuOK=0,
	GPIO_enuNOK,
	GPIO_enuInvalidPort,
	GPIO_enuInvalidPin,
	
}GPIO_tenuErrorStatus;

/* Pin States */
typedef enum
{
	GPIO_enuLOW=0,
	GPIO_enuHIGH,
}GPIO_tenuPinState;

/* Pin Direction */
typedef enum
{
	GPIO_enuINPUT=0,
	GPIO_enuOUTPUT,
}GPIO_tenuPinMode;


/* GPIO Ports*/
typedef enum
{
	GPIO_enuGPIOA=0,
	GPIO_enuGPIOB,
	GPIO_enuGPIOC,
	GPIO_enuNumberOfPorts,
}GPIO_tenuPorts;


/* GPIO 16 Pins = Port */
typedef enum
{
	GPIO_enuPin_0=0b0000,
	GPIO_enuPin_1,
	GPIO_enuPin_2,
	GPIO_enuPin_3,
	GPIO_enuPin_4,
	GPIO_enuPin_5,
	GPIO_enuPin_6,
	GPIO_enuPin_7,
	GPIO_enuPin_8,
	GPIO_enuPin_9,
	GPIO_enuPin_10,
	GPIO_enuPin_11,
	GPIO_enuPin_12,
	GPIO_enuPin_13,
	GPIO_enuPin_14,
	GPIO_enuPin_15,
	GPIO_enuNumberOfPins,
}GPIO_tenuPins;


/* GPIO Input States */
typedef enum 
{
	GPIO_enuInput_Analog= 0b0000,
	GPIO_enuInput_Floating=0b0100,
	GPIO_enuInput_PullUp_PullDown=0b1000,
}GPIO_tenuInputStates;

/* GPIO Output States for Speed = 10MHz */
typedef enum
{
	GPIO_enuOutput_10MHz_PP=0b0001,
	GPIO_enuOutput_10MHz_OD=0b0101,
	GPIO_enuOutput_10MHz_AF_PP=0b1001,
	GPIO_enuOutput_10MHz_AF_OD=0b1101
}GPIO_tenuOutputStates_10MHz;


/* GPIO Output States for Speed = 2MHz */
typedef enum
{
	GPIO_enuOutput_2MHz_PP=0b0010,
	GPIO_enuOutput_2MHz_OD=0b0110,
	GPIO_enuOutput_2MHz_AF_PP=0b1010,
	GPIO_enuOutput_2MHz_AF_OD=0b1110,
}GPIO_tenuOutputStates_2MHz;

/* GPIO Output States for Speed = 50MHz */
typedef enum
{
	GPIO_enuOutput_50MHz_PP=0b0011,
	GPIO_enuOutput_50MHz_OD=0b0111,
	GPIO_enuOutput_50MHz_AF_PP=0b1011,
	GPIO_enuOutput_50MHz_AF_OD=0b1111,
}GPIO_tenuOutputStates_50MHz;


/* Structure of Registers (as they are followed by each other in the memory by 4B) */
typedef struct 
{
	volatile u32 GPIO_CRL;
	volatile u32 GPIO_CRH;
	volatile u32 GPIO_IDR;
	volatile u32 GPIO_ODR;
	volatile u32 GPIO_BSRR;
	volatile u32 GPIO_BRR;
	volatile u32 GPIO_LCKR;
}GPIO_tstrRegisters_t;



/* ================================================ APIs ================================================ */
/* ====================================================================================================== */

/********************************************************************************************/
/* Inputs        : Port, Pin and Mode														*/
/* Return        : Error Status (To ensure function Safety)                                 */
/* Functionality : Setting Pin Direction (Input or Output)		                  			*/
/********************************************************************************************/
GPIO_tenuErrorStatus GPIO_enuSetPinDirection (GPIO_tenuPorts Cpy_u8Port, GPIO_tenuPins Cpy_u8Pin, u8 Cpy_u8Mode);


/********************************************************************************************/
/* Inputs        : Port, Pin and Value														*/
/* Return        : Error Status (To ensure function Safety)                                 */
/* Functionality : Setting Pin Value (High or Low)				                  			*/
/********************************************************************************************/
GPIO_tenuErrorStatus GPIO_enuSetPinValue (GPIO_tenuPorts Cpy_u8Port, GPIO_tenuPins Cpy_u8Pin, GPIO_tenuPinState Cpy_u8Value);
 

/********************************************************************************************/
/* Inputs        : Port and Pin																*/
/* Return        : Pin Value					     		                                */
/* Functionality : Get Pin Value (High or Low)					                  			*/
/********************************************************************************************/
u8 GPIO_u8GetPinValue (GPIO_tenuPorts Cpy_u8Port, GPIO_tenuPins Cpy_u8Pin);




/********************************************************************************************/
/* Inputs        : Port, Position and Mode													*/
/* Return        : Error Status (To ensure function Safety)                                 */
/* Functionality : Setting Port Direction (Input or Output)		                  			*/
/********************************************************************************************/
GPIO_tenuErrorStatus GPIO_enuSetPortDirection (GPIO_tenuPorts Cpy_u8Port, GPIO_tenuPinState Cpy_u8State, u8 Cpy_u8Mode);


/********************************************************************************************/
/* Inputs        : Port, Position and Value													*/
/* Return        : Error Status (To ensure function Safety)                                 */
/* Functionality : Setting Port Value (High or Low)				                  			*/
/********************************************************************************************/
GPIO_tenuErrorStatus GPIO_enuSetPortValue (GPIO_tenuPorts Cpy_u8Port, GPIO_tenuPinState Cpy_u8State, u16 Cpy_u16Value);
 

/********************************************************************************************/
/* Inputs        : Port and position														*/
/* Return        : Port Value					     		                                */
/* Functionality : Get Pin Value (High or Low)					                  			*/
/********************************************************************************************/
u16 GPIO_enuGetPortValue (GPIO_tenuPorts Cpy_u8Port, GPIO_tenuPinState Cpy_u8State);


#endif