/******************************************************************************************************************************************
* Module:      ADC Interface                                                                                                              *
* File Name:   ADC.h                                                                                                                      *
* Description: Header file for ADC driver include functions prototype                                                                     *                                                                                                      *
******************************************************************************************************************************************/
#ifndef ADC_H_
#define ADC_H_

/*=============================================================== INCLUDE ===============================================================*/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

/*=============================================================== DEFINE ================================================================*/

/*===========================================================*/
/*====================== ADC_PERIPHERALS ====================*/
/*===========================================================*/
/* ADDRESSES */

#define ADC1          (( u32*)0x40012400)
#define ADC2          ((volatile u32*)0x40012800)
#define ADC3          ((volatile u32*)0x40013C00)

/*================================================================ TYPES ================================================================*/

/*============== ERROR_STATUS ===============*/
typedef enum
{
    ADC_enuOk ,
	ADC_enuNOk,
	ADC_enuNULLPTR,
}ADC_enuErrorStatus_t;

/*=========================================================== APIS_PROTOTYPES ===========================================================*/

void ADC_vidSingleChannelInit 					     (u32* Copy_u32ADC_Num, u8 Copy_u8Channel);
ADC_enuErrorStatus_t ADC_enuSetNextChannel   		 (u32* Copy_u32ADC_Num, u8 Copy_u8NextChannel);
ADC_enuErrorStatus_t ADC_enuSingleChannelCheck		 (u32* Add_u32ADC_Num, u8 * Add_pu8Check );
ADC_enuErrorStatus_t ADC_enuSingleChannelRX			 (u32* Add_u32ADC_Num, u16 * Add_pu16Data);



ADC_enuErrorStatus_t ADC_enuMultiChannelInit		 (u32* Add_u32ADC_Num, u8 Copy_u8FirstChannel);
ADC_enuErrorStatus_t ADC_enuMultiChannel_RX			 (u32* Add_u32ADC_Num, u8 Copy_u8Channels , u8 * Copy_pu8AdcChannels , u16 * Copy_pu16AnalogRX);



#endif /* ADC_H_ */
/*=============================================================== THE_END ===============================================================*/
