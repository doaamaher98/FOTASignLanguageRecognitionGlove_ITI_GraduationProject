/* ================================================================= */
/* Author 	: Doaa Maher											 */
/* Date		: 9 Jun 2023											 */
/* Target 	: ARM Cortex M3											 */
/* Version  : V1.0													 */
/* Descip. 	: GPIO main program										 */
/* ================================================================= */

/* ======================================= Inclusions ======================================= */
#include "Bit_Math.h"

#include "GPIO.h"
#include "GPIO_Config.h"
#include "GPIO_Private.h"

/* ======================================= Definitions ======================================= */
#define						MAX_PERIPHERAL_NUM					32
#define						TIMEOUT								100000
#define						NUM_PORTS							3

#define						PINS_NUM							8

#define						LOW_PINS							7
#define						HIGH_PINS							15

#define						PIN_BITS							4

#define						CLR_LAST_4_BITS_MASK				0b1111 
#define						CLR_FIRST_4_BITS_MASK				0b0000

#define 					LOW_PORT 							0x00FF
#define 					HIGH_PORT 							0xFF00
/* ======================================= User Defined Data Type ====================================== */
/* Constant pointer to the base address */
GPIO_tstrRegisters_t *const volatile GPIO[NUM_PORTS] = 
{
	/* GPIOA */			{0x40010800},
	/* GPIOB */			{0x40010C00},
	/* GPIOC */			{0x40011000}
};


/* ======================================= Global Variables ======================================= */

/* ======================================= Static Global Variables ======================================= */


/* ======================================= Static Functions ======================================= */



/* ======================================= Global pointer to function (Callback Functions) ======================================= */



/* =============================================== APIs ============================================================= */
GPIO_tenuErrorStatus GPIO_enuSetPinDirection (GPIO_tenuPorts Cpy_u8Port, GPIO_tenuPins Cpy_u8Pin, u8 Cpy_u8Mode)
{
	GPIO_tenuErrorStatus LocalErrorStatus = GPIO_enuOK;
	
	/* Temp Value */
	u32 Local_u32Temp =0;
	
	/* ================== Error Checking ================== */
	if (Cpy_u8Port < GPIO_enuNumberOfPorts)
	{
		if (Cpy_u8Pin < GPIO_enuNumberOfPins)
		{
			switch (Cpy_u8Port)
			{
				case GPIO_enuGPIOA:
				/* If Low Pins (0->7) */
				if (Cpy_u8Pin <= LOW_PINS)
				{
					/* Resetting the Register */
					Local_u32Temp = GPIO[GPIO_enuGPIOA]->GPIO_CRL;
					
					/* Clear the Mode */
					Local_u32Temp &= ~((CLR_LAST_4_BITS_MASK) << (Cpy_u8Pin * PIN_BITS));
					
					/* Set the Mode inside the Register */
					Local_u32Temp |= ((Cpy_u8Mode) << (Cpy_u8Pin * PIN_BITS));
					
					/* Setting the Value once again in register */
					GPIO[GPIO_enuGPIOA]->GPIO_CRL = Local_u32Temp;
				}
				
				/* If High Pins (8->15) */
				else if (Cpy_u8Pin <= HIGH_PINS)
				{
					/* Subtracting 8 from the Pin number */
					Cpy_u8Pin -= PINS_NUM;
					
					/* Resetting the Register */
					Local_u32Temp = GPIO[GPIO_enuGPIOA]->GPIO_CRH;
					
					/* Clear the Mode */
					Local_u32Temp &= ~((CLR_LAST_4_BITS_MASK) << (Cpy_u8Pin * PIN_BITS));
					
					/* Set the Mode inside the Register */
					Local_u32Temp |= ((Cpy_u8Mode) << (Cpy_u8Pin * PIN_BITS));
					
					/* Setting the Value once again in register */
					GPIO[GPIO_enuGPIOA]->GPIO_CRH = Local_u32Temp;
				}
				break;
				
				case GPIO_enuGPIOB:
				/* If Low Pins (0->7) */
				if (Cpy_u8Pin <= LOW_PINS)
				{
					/* Resetting the Register */
					Local_u32Temp = GPIO[GPIO_enuGPIOB]->GPIO_CRL;
					
					/* Clear the Mode */
					Local_u32Temp &= ~((CLR_LAST_4_BITS_MASK) << (Cpy_u8Pin * PIN_BITS));
					
					/* Set the Mode inside the Register */
					Local_u32Temp |= ((Cpy_u8Mode) << (Cpy_u8Pin * PIN_BITS));
					
					/* Setting the Value once again in register */
					GPIO[GPIO_enuGPIOB]->GPIO_CRL = Local_u32Temp;
				}
				
				/* If High Pins (8->15) */
				else if (Cpy_u8Pin <= HIGH_PINS)
				{
					/* Subtracting 8 from the Pin number */
					Cpy_u8Pin -= PINS_NUM;
					
					/* Resetting the Register */
					Local_u32Temp = GPIO[GPIO_enuGPIOB]->GPIO_CRH;
					
					/* Clear the Mode */
					Local_u32Temp &= ~((CLR_LAST_4_BITS_MASK) << (Cpy_u8Pin * PIN_BITS));
					
					/* Set the Mode inside the Register */
					Local_u32Temp |= ((Cpy_u8Mode) << (Cpy_u8Pin * PIN_BITS));
					
					/* Setting the Value once again in register */
					GPIO[GPIO_enuGPIOB]->GPIO_CRH = Local_u32Temp;
				}
				break;
				
				case GPIO_enuGPIOC:
				/* If Low Pins (0->7) */
				if (Cpy_u8Pin <= LOW_PINS)
				{
					/* Resetting the Register */
					Local_u32Temp = GPIO[GPIO_enuGPIOC]->GPIO_CRL;
					
					/* Clear the Mode */
					Local_u32Temp &= ~((CLR_LAST_4_BITS_MASK) << (Cpy_u8Pin * PIN_BITS));
					
					/* Set the Mode inside the Register */
					Local_u32Temp |= ((Cpy_u8Mode) << (Cpy_u8Pin * PIN_BITS));
					
					/* Setting the Value once again in register */
					GPIO[GPIO_enuGPIOC]->GPIO_CRL = Local_u32Temp;
				}
				
				/* If High Pins (8->15) */
				else if (Cpy_u8Pin <= HIGH_PINS)
				{
					/* Subtracting 8 from the Pin number */
					Cpy_u8Pin -= PINS_NUM;
					
					/* Resetting the Register */
					Local_u32Temp = GPIO[GPIO_enuGPIOC]->GPIO_CRH;
					
					/* Clear the Mode */
					Local_u32Temp &= ~((CLR_LAST_4_BITS_MASK) << (Cpy_u8Pin * PIN_BITS));
					
					/* Set the Mode inside the Register */
					Local_u32Temp |= ((Cpy_u8Mode) << (Cpy_u8Pin * PIN_BITS));
					
					/* Setting the Value once again in register */
					GPIO[GPIO_enuGPIOC]->GPIO_CRH = Local_u32Temp;
				}
				break;
				
				default :
					LocalErrorStatus = GPIO_enuInvalidPortNumber; break;
			}
			
		}
		else
		{
			LocalErrorStatus = GPIO_enuInvalidPin;
		}
		
	}
	else
	{
		LocalErrorStatus = GPIO_enuInvalidPort;
	}
	
	return LocalErrorStatus;
}
/*****************************************************************************************************************/
GPIO_tenuErrorStatus GPIO_enuSetPinValue (GPIO_tenuPorts Cpy_u8Port, GPIO_tenuPins Cpy_u8Pin, GPIO_tenuPinState Cpy_u8Value)
{
	GPIO_tenuErrorStatus LocalErrorStatus = GPIO_enuOK;
	
	/* ================== Error Checking ================== */
	if (Cpy_u8Port < GPIO_enuNumberOfPorts)
	{
		if (Cpy_u8Pin < GPIO_enuNumberOfPins)
		{
			switch (Cpy_u8Port)
			{
				case GPIO_enuGPIOA:
				/* ================= Checking Pin State ================= */
				/* If State == HIGH */
				if (Cpy_u8Value == GPIO_enuHIGH)
				{
					SET_BIT(GPIO[GPIO_enuGPIOA]->GPIO_ODR, Cpy_u8Pin);	
				}
				/* If State == LOW */
				else if (Cpy_u8Value == GPIO_enuLOW)
				{
					CLR_BIT(GPIO[GPIO_enuGPIOA]->GPIO_ODR, Cpy_u8Pin);
					
				}
				break;
				
				case GPIO_enuGPIOB: 
				/* ================= Checking Pin State ================= */
				/* If State == HIGH */
				if (Cpy_u8Value == GPIO_enuHIGH)
				{
					SET_BIT(GPIO[GPIO_enuGPIOB]->GPIO_ODR, Cpy_u8Pin);	
				}
				/* If State == LOW */
				else if (Cpy_u8Value == GPIO_enuLOW)
				{
					CLR_BIT(GPIO[GPIO_enuGPIOB]->GPIO_ODR, Cpy_u8Pin);
					
				}
				break;
				
				case GPIO_enuGPIOC:
				/* ================= Checking Pin State ================= */
				/* If State == HIGH */
				if (Cpy_u8Value == GPIO_enuHIGH)
				{
					SET_BIT(GPIO[GPIO_enuGPIOC]->GPIO_ODR, Cpy_u8Pin);	
				}
				/* If State == LOW */
				else if (Cpy_u8Value == GPIO_enuLOW)
				{
					CLR_BIT(GPIO[GPIO_enuGPIOC]->GPIO_ODR, Cpy_u8Pin);
					
				}
				break;
				
				default : 
					LocalErrorStatus = GPIO_enuInvalidPortNumber; break;
			}
			
		}
		else
		{
			LocalErrorStatus = GPIO_enuInvalidPin;
		}
		
	}
	else
	{
		LocalErrorStatus = GPIO_enuInvalidPort;
	}
	
	return LocalErrorStatus;
}
/*****************************************************************************************************************/
u8 GPIO_u8GetPinValue (GPIO_tenuPorts Cpy_u8Port, GPIO_tenuPins Cpy_u8Pin)
{
	/* Returned Result */
	u8 Local_u8Value = 0;
	
	switch (Cpy_u8Port)
			{
				case GPIO_enuGPIOA:
				Local_u8Value = GET_BIT(GPIO[GPIO_enuGPIOA]->GPIO_IDR ,Cpy_u8Pin);
				break;
				
				case GPIO_enuGPIOB: 
				Local_u8Value = GET_BIT(GPIO[GPIO_enuGPIOB]->GPIO_IDR ,Cpy_u8Pin);
				break;
				
				case GPIO_enuGPIOC:
				Local_u8Value = GET_BIT(GPIO[GPIO_enuGPIOC]->GPIO_IDR ,Cpy_u8Pin);
				break;
				
				default : break;
			}
	  
	return Local_u8Value;
}
/*****************************************************************************************************************/
GPIO_tenuErrorStatus GPIO_enuSetPortDirection (GPIO_tenuPorts Cpy_u8Port, GPIO_tenuPinState Cpy_u8State, u8 Cpy_u8Mode)
{
	GPIO_tenuErrorStatus LocalErrorStatus = GPIO_enuOK;
	
	/* ================== Error Checking ================== */
	if (Cpy_u8Port < GPIO_enuNumberOfPorts)
	{
		switch (Cpy_u8Port)
		{
			case GPIO_enuGPIOA:
			/* ================= Checking Pin State ================= */
			if (Cpy_u8State == GPIO_enuLOW)
			{
				GPIO[GPIO_enuGPIOA]->GPIO_CRL = (0x11111111 * Cpy_u8Mode);
			}
			else if (Cpy_u8State == GPIO_enuHIGH)
			{
				GPIO[GPIO_enuGPIOA]->GPIO_CRH = (0x11111111 * Cpy_u8Mode);
			}
			break;
			
			case GPIO_enuGPIOB: 
			/* ================= Checking Pin State ================= */
			if (Cpy_u8State == GPIO_enuLOW)
			{
				GPIO[GPIO_enuGPIOB]->GPIO_CRL = (0x11111111 * Cpy_u8Mode);
			}
			else if (Cpy_u8State == GPIO_enuHIGH)
			{
				GPIO[GPIO_enuGPIOB]->GPIO_CRH = (0x11111111 * Cpy_u8Mode);
			}
			break;
			
			case GPIO_enuGPIOC:
			/* ================= Checking Pin State ================= */
			if (Cpy_u8State == GPIO_enuLOW)
			{
				GPIO[GPIO_enuGPIOC]->GPIO_CRL = (0x11111111 * Cpy_u8Mode);
			}
			else if (Cpy_u8State == GPIO_enuHIGH)
			{
				GPIO[GPIO_enuGPIOC]->GPIO_CRH = (0x11111111 * Cpy_u8Mode);
			}
			break;
			
			default : break;
			}
		}
	else
	{
		LocalErrorStatus = GPIO_enuInvalidPort;
	}
	
	return LocalErrorStatus;
} 
/*****************************************************************************************************************/
GPIO_tenuErrorStatus GPIO_enuSetPortValue (GPIO_tenuPorts Cpy_u8Port, GPIO_tenuPinState Cpy_u8State, u16 Cpy_u16Value)
{
	GPIO_tenuErrorStatus LocalErrorStatus = GPIO_enuOK;
	
	if (Cpy_u8Port < GPIO_enuNumberOfPorts)
	{
		switch (Cpy_u8Port)
		{
			case GPIO_enuGPIOA:
			/* ================= Checking Pin State ================= */
			if (Cpy_u8State == GPIO_enuLOW)
			{
				GPIO[GPIO_enuGPIOA]->GPIO_ODR = (GPIO[GPIO_enuGPIOA]->GPIO_ODR & HIGH_PORT ) | ((u8)Cpy_u16Value) ;
			}
			else if (Cpy_u8State == GPIO_enuHIGH)
			{
				GPIO[GPIO_enuGPIOA]->GPIO_ODR = (GPIO[GPIO_enuGPIOA]->GPIO_ODR & LOW_PORT ) | ((u8)Cpy_u16Value) ;
			}
			break;
			
			case GPIO_enuGPIOB: 
			/* ================= Checking Pin State ================= */
			if (Cpy_u8State == GPIO_enuLOW)
			{
				GPIO[GPIO_enuGPIOB]->GPIO_ODR = (GPIO[GPIO_enuGPIOB]->GPIO_ODR & HIGH_PORT ) | ((u8)Cpy_u16Value) ;
			}
			else if (Cpy_u8State == GPIO_enuHIGH)
			{
				GPIO[GPIO_enuGPIOB]->GPIO_ODR = (GPIO[GPIO_enuGPIOB]->GPIO_ODR & LOW_PORT ) | ((u8)Cpy_u16Value) ;
			}
			break;
			
			case GPIO_enuGPIOC:
			/* ================= Checking Pin State ================= */
			if (Cpy_u8State == GPIO_enuLOW)
			{
				GPIO[GPIO_enuGPIOC]->GPIO_ODR = (GPIO[GPIO_enuGPIOC]->GPIO_ODR & HIGH_PORT ) | ((u8)Cpy_u16Value) ;
			}
			else if (Cpy_u8State == GPIO_enuHIGH)
			{
				GPIO[GPIO_enuGPIOC]->GPIO_ODR = (GPIO[GPIO_enuGPIOC]->GPIO_ODR & LOW_PORT ) | ((u8)Cpy_u16Value) ;
			}
			break;
			
			default : break;
			}
		}
	else
	{
		LocalErrorStatus = GPIO_enuInvalidPort;
	}

	return LocalErrorStatus;
}
/*****************************************************************************************************************/
u16 GPIO_enuGetPortValue (GPIO_tenuPorts Cpy_u8Port, GPIO_tenuPinState Cpy_u8State)
{
	u16 Local_u16Value = 0;
	
	switch (Cpy_u8Port)
	{
		case GPIO_enuGPIOA:
		Local_u16Value = GPIO[GPIO_enuGPIOA]->GPIO_IDR;
		/* =================== Check State =================== */
		if (Cpy_u8State == GPIO_enuLOW)
		{
			Local_u16Value &= LOW_PORT;
		}
		else if (Cpy_u8State == GPIO_enuHIGH)
		{
			Local_u16Value &= HIGH_PORT;
		}
		break;
		
		case GPIO_enuGPIOB: 
		Local_u16Value = GPIO[GPIO_enuGPIOB]->GPIO_IDR;
		/* =================== Check State =================== */
		if (Cpy_u8State == GPIO_enuLOW)
		{
			Local_u16Value &= LOW_PORT;
		}
		else if (Cpy_u8State == GPIO_enuHIGH)
		{
			Local_u16Value &= HIGH_PORT;
		}
		break;
		
		case GPIO_enuGPIOC:
		Local_u16Value = GPIO[GPIO_enuGPIOC]->GPIO_IDR;
		/* =================== Check State =================== */
		if (Cpy_u8State == GPIO_enuLOW)
		{
			Local_u16Value &= LOW_PORT;
		}
		else if (Cpy_u8State == GPIO_enuHIGH)
		{
			Local_u16Value &= HIGH_PORT;
		}
		break;
		
		default : break;
		}
	
	return Local_u16Value;
}
/*****************************************************************************************************************/
