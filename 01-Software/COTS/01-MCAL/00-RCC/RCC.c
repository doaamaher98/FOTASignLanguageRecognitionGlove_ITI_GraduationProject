/* ================================================================= */
/* Author 	: Doaa Maher											 */
/* Date		: 8 Jun 2023											 */
/* Target 	: ARM Cortex M3											 */
/* Version  : V1.0													 */
/* Descip. 	: RCC main program										 */
/* ================================================================= */

/* ======================================= Inclusions ======================================= */
#include "Bit_Math.h"

#include "RCC.h"
#include "RCC_Config.h"
#include "RCC_Private.h"

/* ======================================= Definitions ======================================= */
#define						MAX_PERIPHERAL_NUM					32
#define						TIMEOUT								100000
/* ======================================= User Defined Data Type ====================================== */
/* Constant pointer to the base address */
RCC_tstrRegisters_t *const volatile RCC = (RCC_tstrRegisters_t*)0x40021000;


/* ======================================= Global Variables ======================================= */

/* ======================================= Static Global Variables ======================================= */


/* ======================================= Static Functions ======================================= */



/* ======================================= Global pointer to function (Callback Functions) ======================================= */



/* =============================================== APIs ============================================================= */
RCC_tenuErrorStatus RCC_enuInitSystemClock (void)
{
	RCC_tenuErrorStatus LocalErrorStatus = RCC_enuOK;
	
	/* A Timeout Local Variable */
	u32 Local_u32TIMEOUT = 0;
	
	/* =========== Error Checking ============ */
	if (Cpy_u8ClkSrc < RCC_enuNumberOfClocks)
	{
		#if RCC_SYSCLK_SRC == RCC_enuHSI
			/* HSI Selected As System Clock */
			CLR_BIT(RCC->RCC_CFGR , RCC_enuSW0);
			CLR_BIT(RCC->RCC_CFGR , RCC_enuSW1);
			
			/* Enable The HSI Clock */
			SET_BIT(RCC->RCC_CR   , RCC_enuHSI_ON);
			
			/* Checking While The HSI Clock Is Ready */
			while( ((GET_BIT(RCC->RCC_CR , RCC_enuHSI_RDY)) == 0 ) && (Local_u32TIMEOUT < TIMEOUT) )
			{ 
				/* Increment the TIMEOUT */
				Local_u32TIMEOUT++; 
			}
			/* Check if TIMEOUT occured */
			if(Local_u32TIMEOUT >= TIMEOUT)
			{
				/* TIMEOUT Occured */
				LocalErrorStatus = RCC_enuTIMEOUT;
			}
		
		#elif RCC_SYSCLK_SRC == RCC_enuHSE_CRYSTAL
			/* HSE Selected As System Clock */
			SET_BIT(RCC->RCC_CFGR, RCC_enuSW0);
			CLR_BIT(RCC->RCC_CFGR, RCC_enuSW1);
			
			/* Enable The HSE Clock */
			SET_BIT(RCC->RCC_CR   , RCC_enuHSE_ON);
			
			
			/* Checking While The HSE Clock Is Ready */
			while( ((GET_BIT(RCC->RCC_CR, RCC_enuHSE_RDY)) == 0) && (Local_u32TIMEOUT < TIMEOUT) )
			{
				/* Increment the TIMEOUT */
				Local_u32TIMEOUT++; 
			}
			if(Local_u32TIMEOUT >= TIMEOUT)
			{
				/* TIMEOUT Occured */
				LocalErrorStatus = RCC_enuTIMEOUT;
			}
		
		#elif RCC_SYSCLK_SRC == RCC_enuHSE_RC
			/* The HSEBYP Can Be Written Only When HSE Oscilator Is Disabled */
			/* HSE Clock Disabled */
			CLR_BIT(RCC->RCC_CR, RCC_enuHSE_ON);
			
			/* HSEBYPASS Clock Enable */
			SET_BIT(RCC->RCC_CR, RCC_enuHSE_BYP);
			
			/* HSE Selected As System Clock */
			SET_BIT(RCC->RCC_CFGR , RCC_enuSW0);
			CLR_BIT(RCC->RCC_CFGR , RCC_enuSW1);
			
			/* Enable The HSE Clock */
			SET_BIT( RCC->RCC_CR, RCC_enuHSE_ON);
			
			/* Checking While The HSE Clock Is Ready */
			while( ((GET_BIT(RCC->RCC_CR, RCC_enuHSE_RDY)) == 0) && (Local_u32TIMEOUT < TIMEOUT) )
			{
				/* Increment the TIMEOUT */
				Local_u32TIMEOUT++; 
			}
			if(Local_u32TIMEOUT >= TIMEOUT)
			{
				/* TIMEOUT Occured */
				LocalErrorStatus = RCC_enuTIMEOUT;
			}
		
		#elif RCC_SYSCLK_SRC == RCC_enuPLL
			/* PLL Selected As System Clock */
			CLR_BIT(RCC->RCC_CFGR, RCC_enuSW0);
			SET_BIT(RCC->RCC_CFGR, RCC_enuSW1);
			
			/*
			*
			*/
		#else

		#error " Wrong Clock System Type Configuration "

		#endif
	}
	else
	{
		LocalErrorStatus = RCC_enuInvalidClockSrc;
	}
	return LocalErrorStatus;
}

/*****************************************************************************************************************/
RCC_tenuErrorStatus RCC_enuEnablePeripheralClk (RCC_tenuBusType Cpy_u8Bus, u8 Cpy_u8Peripheral)
{
	/* Local Error Status definition */
	RCC_tenuErrorStatus LocalErrorStatus = RCC_enuOK;
	
	/* Local Temp */
	u32 Local_u32Temp =0;
	
	/* ==================== Error Checking ===================== */
	if (Cpy_u8Bus < RCC_enuNumberOfBuses)
	{
		if (Cpy_u8Peripheral < MAX_PERIPHERAL_NUM)
		{
			/* Checking the Bus */
			switch (Cpy_u8Bus)
			{
				case RCC_enuAPB1:
					SET_BIT(RCC->RCC_APB1ENR, Cpy_u8Peripheral);
				break;
				
				case RCC_enuAPB2:
					SET_BIT(RCC->RCC_APB2ENR, Cpy_u8Peripheral);
				break;
				
				case RCC_enuAHB:
					SET_BIT(RCC->RCC_AHBENR, Cpy_u8Peripheral);
				break;
				
				default :
					LocalErrorStatus = RCC_enuInvalidBusOption;
				break;
			}
		}
		else
		{
			LocalErrorStatus = RCC_enuInvalidPeripheralID;
		}
		
	}
	else
	{
		LocalErrorStatus = RCC_enuInvalidBus;
	}
	
	return LocalErrorStatus;
}

/*****************************************************************************************************************/
RCC_tenuErrorStatus RCC_enuDisablePeripheralClk (RCC_tenuBusType Cpy_u8Bus, u8 Cpy_u8Peripheral)
{
	/* Local Error Status definition */
	RCC_tenuErrorStatus LocalErrorStatus = RCC_enuOK;
	
	/* Local Temp */
	u32 Local_u32Temp =0;
	
	/* ==================== Error Checking ===================== */
	if (Cpy_u8Bus < RCC_enuNumberOfBuses)
	{
		if (Cpy_u8Peripheral < MAX_PERIPHERAL_NUM)
		{
			/* Checking the Bus */
			switch (Cpy_u8Bus)
			{
				case RCC_enuAPB1:
					CLR_BIT(RCC->RCC_APB1ENR, Cpy_u8Peripheral);
				break;
				
				case RCC_enuAPB2:
					CLR_BIT(RCC->RCC_APB2ENR, Cpy_u8Peripheral);
				break;
				
				case RCC_enuAHB:
					CLR_BIT(RCC->RCC_AHBENR, Cpy_u8Peripheral);
				break;
				
				default :
					LocalErrorStatus = RCC_enuInvalidBusOption;
				break;
			}
		}
		else
		{
			LocalErrorStatus = RCC_enuInvalidPeripheralID;
		}
		
	}
	else
	{
		LocalErrorStatus = RCC_enuInvalidBus;
	}
	
	return LocalErrorStatus;
}
/*****************************************************************************************************************/