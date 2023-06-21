/******************************************************************************************************************************************
 * Module:      ADC                                                                                                                        *
 * File Name:   ADC.c                                                                                                                      *
 * Description: Source file include implementation of ADC driver Functions                                                                 *                                                                                                          *
 ******************************************************************************************************************************************/

/*=============================================================== INCLUDE ===============================================================*/

#include "ADC.h"
#include "Delay.h"
#include "STK.h"

/*=============================================================== DEFINE ================================================================*/


/*================================================================ TYPES ================================================================*/
/* ADC_REGISTERS */
typedef struct
{
	/* ADC status register */
	volatile u32	ADC_SR;
	/* ADC control register 1 */
	volatile u32	ADC_CR1;
	/* ADC control register 2 */
	volatile u32	ADC_CR2;
	/* ADC sample time register 1 */
	volatile u32	ADC_SMPR1;
	/* ADC sample time register 2 */
	volatile u32	ADC_SMPR2;
	/* ADC injected channel data offset register 1 */
	volatile u32	ADC_JOFR1;
	/* ADC injected channel data offset register 2 */
	volatile u32	ADC_JOFR2;
	/* ADC injected channel data offset register 3 */
	volatile u32	ADC_JOFR3;
	/* ADC injected channel data offset register 4 */
	volatile u32	ADC_JOFR4;
	/* ADC watch_dog high threshold register */
	volatile u32	ADC_HTR;
	/* ADC watch_dog low threshold register */
	volatile u32	ADC_LTR;
	/* ADC regular sequence register 1 */
	volatile u32	ADC_SQR1;
	/* ADC regular sequence register 2 */
	volatile u32	ADC_SQR2;
	/* ADC regular sequence register 3 */
	volatile u32	ADC_SQR3;
	/* ADC injected sequence register */
	volatile u32	ADC_JSQR;
	/* ADC injected data register 1 */
	volatile u32	ADC_JDR1;
	/* ADC injected data register 2 */
	volatile u32	ADC_JDR2;
	/* ADC injected data register 3 */
	volatile u32	ADC_JDR3;
	/* ADC injected data register 4 */
	volatile u32	ADC_JDR4;
	/* ADC regular data register */
	volatile u32	ADC_DR;
}ADC_strReg_t;

/*=========================================================== APIS_DEFINATION ===========================================================*/

void ADC_vidSingleChannelInit(u32* Copy_u32ADC_Num, u8 Copy_u8Channel)
{
	/* Clear All CR2 */
	((ADC_strReg_t*) Copy_u32ADC_Num)->ADC_CR2  = 0;

	/* Set Number Channel of ADC */
	((ADC_strReg_t*) Copy_u32ADC_Num)->ADC_SQR3 = Copy_u8Channel;

	/* ADC ON */
	((ADC_strReg_t*) Copy_u32ADC_Num)->ADC_CR2 |= 1;

	/* wait for stability */
	_delay_ms(100);

	/* ADC ON again */
	((ADC_strReg_t*) Copy_u32ADC_Num)->ADC_CR2 |= 1;

	/* Set Continuous conversion */
	((ADC_strReg_t*) Copy_u32ADC_Num)->ADC_CR2 |= 2;
}
/*=========================================*/
ADC_enuErrorStatus_t ADC_enuMultiChannelInit(u32* Add_u32ADC_Num, u8 Copy_u8FirstChannel)
{
	ADC_enuErrorStatus_t Loc_enuErrorStatus = ADC_enuOk;

	if( (Add_u32ADC_Num != ADC1) || (Add_u32ADC_Num != ADC2) || (Add_u32ADC_Num != ADC3) )
	{
		Loc_enuErrorStatus = ADC_enuNOk;
	}
	else
	{
		/* Clear All CR2 */
		((ADC_strReg_t*) Add_u32ADC_Num)->ADC_CR2  = 0;

		/* ADC ON */
		((ADC_strReg_t*) Add_u32ADC_Num)->ADC_CR2 |= 1;

		/* wait for stability */
		_delay_ms(100);

		/* Set Number of first Channel of ADC */
		((ADC_strReg_t*) Add_u32ADC_Num)->ADC_SQR3 = Copy_u8FirstChannel;

		/* Set Continuous conversion */
		((ADC_strReg_t*) Add_u32ADC_Num)->ADC_CR2 |= 2;

		/* ADC ON again */
		((ADC_strReg_t*) Add_u32ADC_Num)->ADC_CR2 |= 1;
	}

	return Loc_enuErrorStatus;

}
/*=========================================*/
ADC_enuErrorStatus_t ADC_enuSetNextChannel(u32* Add_u32ADC_Num, u8 Copy_u8NextChannel)
{
	ADC_enuErrorStatus_t Loc_enuErrorStatus = ADC_enuOk;

	if( (Add_u32ADC_Num != ADC1) || (Add_u32ADC_Num != ADC2) || (Add_u32ADC_Num != ADC3) )
	{
		Loc_enuErrorStatus = ADC_enuNOk;
	}
	else
	{
		/* Set Number of Next Channel of ADC */
		((ADC_strReg_t*) Add_u32ADC_Num)->ADC_SQR3 = Copy_u8NextChannel;
	}

	return Loc_enuErrorStatus;
}
/*=========================================*/
ADC_enuErrorStatus_t ADC_enuSingleChannelCheck(u32* Add_u32ADC_Num, u8 * Add_pu8Check )
{
	ADC_enuErrorStatus_t Loc_enuErrorStatus = ADC_enuOk;

	if( (Add_u32ADC_Num != ADC1) || (Add_u32ADC_Num != ADC2) || (Add_u32ADC_Num != ADC3) )
	{
		Loc_enuErrorStatus = ADC_enuNOk;
	}
	else
	{
		/* Check Flag of EOC */
		if(((ADC_strReg_t*) Add_u32ADC_Num)->ADC_SR & 2)
		{
			*Add_pu8Check = 1;
		}
		else
		{
			*Add_pu8Check= 0;
		}
	}

	return Loc_enuErrorStatus;
}
/*=========================================*/
ADC_enuErrorStatus_t ADC_enuSingleChannelRX(u32* Add_u32ADC_Num, u16 * Add_pu16Data)
{
	ADC_enuErrorStatus_t Loc_enuErrorStatus = ADC_enuOk;
	u16 Loc_u16Data = 0;

	if( (Add_u32ADC_Num != ADC1) || (Add_u32ADC_Num != ADC2) || (Add_u32ADC_Num != ADC3) )
	{
		Loc_enuErrorStatus = ADC_enuNOk;
	}

	else if( Add_pu16Data == NULL_PTR)
	{
		Loc_enuErrorStatus = ADC_enuNULLPTR;
	}
	else
	{
		/* Read Data of ADC from DR Register */
		Loc_u16Data = ((ADC_strReg_t*) Add_u32ADC_Num)->ADC_DR;

		/* range of value of ADC of 3.3v (0 : 985), and of 5v(0 : 1000) */
		/* If you want to set range from(0 : 4035)(resolution 12 bits)of 3.3v or from(0 : 4095)(resolution 12 bits)of 5v, you don't need this equation */
		*Add_pu16Data  = (Loc_u16Data*1000)/0xfff;
	}

	return Loc_enuErrorStatus;
}
/*=========================================*/
ADC_enuErrorStatus_t ADC_enuMultiChannel_RX(u32* Add_u32ADC_Num, u8 Copy_u8Channels , u8 * Copy_pu8AdcChannels , u16 * Copy_pu16AnalogRX)
{
	ADC_enuErrorStatus_t Loc_enuErrorStatus = ADC_enuOk;

	u16 Loc_u16TempRX = 0;
	u8 Loc_u8Counter  = 0;
	u8 Loc_pu8Check = 0;

	while (1)
	{
		/* Check Flag of EOC */
		Loc_enuErrorStatus = ADC_enuSingleChannelCheck(Add_u32ADC_Num, &Loc_pu8Check );

		if(Loc_pu8Check)
		{
			/* Read Data of ADC from DR Register */
			ADC_enuSingleChannelRX(Add_u32ADC_Num, &Loc_u16TempRX);

			/* Assign this data in array */
			Copy_pu16AnalogRX[Loc_u8Counter] = Loc_u16TempRX;
			Loc_u8Counter++;

			/* Check if all channel has a value or not */
			if(Loc_u8Counter == Copy_u8Channels)
			{
				Loc_u8Counter = 0;
				ADC_enuSetNextChannel(Add_u32ADC_Num, Copy_pu8AdcChannels[Loc_u8Counter]);
				break;
			}
			else
			{
				ADC_enuSetNextChannel(Add_u32ADC_Num, Copy_pu8AdcChannels[Loc_u8Counter]);
			}
		}
	}

	return Loc_enuErrorStatus;
}
/*=============================================================== THE_END ===============================================================*/
