/*************************************************************************************************************************************
* Module:      Application                                                                                                           *
* File Name:   main.c                                                                                                                *
* Description: Source file include implementation of FOTA Sign Language Recognition Glove_ITI_GraduationProject                      *                                                         *
* Author:      Esraa_Mohamed                                                                                                         *
**************************************************************************************************************************************/
/*============================================================ INCLUDE ==============================================================*/
#include "RCC.h"
#include "RCC_Config.h"
#include "GPIO.h"
#include "STK.h"
#include "Delay.h"
#include "UART.h"
#include "UART_Cfg.h"
#include "ADC.h"
#include "LCD_Cfg.h"
#include "LCD.h"
#include "DfPlayer_Prv.h"
#include "DfPlayer.h"

/*============================================================ DEFINES ==============================================================*/

/* Folder Number */
#define DFP_Folder							1


/* Track Number */
#define DFP_Track1							1
#define DFP_Track2							2
#define DFP_Track3							3
#define DFP_Track4							4
#define DFP_Track5							5
#define DFP_Track6							6
#define DFP_Track7							7
#define DFP_Track8							8
#define DFP_Track9							9

#define DFP_FOLDER							0
#define DFP_TRACK							1

#define CHANNEL_NUMBER						5

/* Normal Value */
#define FLEX_1	10
#define FLEX_2	10
#define FLEX_3	10
#define FLEX_4	10
#define FLEX_5	10
#define POT6	10

/*=========================================================== VARIABLES =============================================================*/

/* Choose Channel number of ADC PINS (0,1,2,3,4,5,6,7,8,9) */
u8 adc_channels[CHANNEL_NUMBER] = {0,1,2,3,4};
/* Set Number of channel */
u8 channels = CHANNEL_NUMBER;
/* Array of Data for ADC channel */
u16 analog_rx[CHANNEL_NUMBER] = {0};

/*==================================================== DECLARETION_STATIC_FUNCTION ==================================================*/

/* App Function Prototype */
void SignLanguage(void);

/*============================================================= MAIN ===============================================================*/

void main()
{
	/* Initialize RCC 8Mhz */
	RCC_enuInitSystemClock();

	/************************/

	/* Enable GPIOA */
	RCC_enuEnablePeripheralClk(RCC_enuAPB2 , RCC_enuGPIOA_EN);

	/* Enable GPIOB */
	RCC_enuEnablePeripheralClk(RCC_enuAPB2 , RCC_enuGPIOB_EN);

	/* Enable USART1 */
	RCC_enuEnablePeripheralClk(RCC_enuAPB2 , RCC_enuUSART1_EN);

	/* Enable ADC1 */
	RCC_enuEnablePeripheralClk(RCC_enuAPB2 , RCC_enuADC1_EN);

	/************************/

	/* Enable Sys_tick */
	STK_enuInit();

	/* Initialize LCD*/
	lcd_vidInit();

	/************************/

	/* DF-Player on USART1 */
	/* A9  = TX1 out 50MHz */
	GPIO_enuSetPinDirection(GPIO_enuGPIOA , GPIO_enuPin_9 , GPIO_enuOutput_50MHz_AF_PP);
	/* A10 = RX1 input Floating */
	GPIO_enuSetPinDirection(GPIO_enuGPIOA , GPIO_enuPin_10 , GPIO_enuInput_Floating);
	/* Initialize USART BaudRate = 9600 */
	MUART_VidInit();

	/************************/

	/* Initialize ADC Multiple Channel Mode */
	ADC_enuMultiChannelInit(ADC1,adc_channels[0]);

	/************************/

	/* FLEXs */
	GPIO_enuSetPinDirection(GPIO_enuGPIOA , GPIO_enuPin_0 , GPIO_enuInput_Analog);
	GPIO_enuSetPinDirection(GPIO_enuGPIOA , GPIO_enuPin_1 , GPIO_enuInput_Analog);
	GPIO_enuSetPinDirection(GPIO_enuGPIOA , GPIO_enuPin_2 , GPIO_enuInput_Analog);
	GPIO_enuSetPinDirection(GPIO_enuGPIOA , GPIO_enuPin_3 , GPIO_enuInput_Analog);
	GPIO_enuSetPinDirection(GPIO_enuGPIOA , GPIO_enuPin_4 , GPIO_enuInput_Analog);

	while(1)
	{
		/* Application Function*/
		SignLanguage();

	}/* end of main while */

}/* end of main */


/*==================================================== DEFINATION_STATIC_FUNCTION ==================================================*/


/* App Function Implementation */
void SignLanguage(void)
{
	/* Declare and Initialize Local Variable */
	int Indx_record[10][2] = {0};
	u8 Local_u8RecordCounter = 0;
	u8 Local_u8Counter;

	ADC_enuMultiChannel_RX(ADC1,channels , adc_channels , analog_rx);
	/* Arabic language <- F1 C */
	if(analog_rx[1] > FLEX_1)
	{
		while(1)
		{

			/* read variable from FLEX */
			ADC_enuMultiChannel_RX(ADC1,channels , adc_channels , analog_rx);

			/* sabah */
			/*  F1 C                    ,F2 C                    ,F3 O                    ,F4 O                    ,F5  O                                 */
			if((analog_rx[0] > FLEX_1) && (analog_rx[1] > FLEX_2) && (analog_rx[2] < FLEX_3) && (analog_rx[3] < FLEX_4) && (analog_rx[4] < FLEX_5) )
			{
				/* Set record Indx */
				Indx_record[Local_u8RecordCounter][DFP_FOLDER] = DFP_Folder;
				Indx_record[Local_u8RecordCounter][DFP_TRACK]  = DFP_Track1;
				lcd_enuWriteString("Sabah",5,0,0,LCD_1);
				/* Increment for next position of array_reacord */
				Local_u8RecordCounter++;

				/* Still in this loop until new word*/
				while((analog_rx[0] > FLEX_1) && (analog_rx[1] > FLEX_2) && (analog_rx[2] < FLEX_3) && (analog_rx[3] < FLEX_4) && (analog_rx[4] < FLEX_5))
				{
					/* read variable from POTS , ADXL*/
					ADC_enuMultiChannel_RX(ADC1,channels , adc_channels , analog_rx);
				}
			}

			/* elkhair */
			/*  F1 O                    ,F2 O                     ,F3 O                    ,F4 C                     ,F5  C         */
			else if((analog_rx[0] < FLEX_1) && (analog_rx[1] < FLEX_2) && (analog_rx[2] < FLEX_3) && (analog_rx[3] > FLEX_4) && (analog_rx[4] > FLEX_5) )
			{
				/* Set record Indx */
				Indx_record[Local_u8RecordCounter][DFP_FOLDER] = DFP_Folder;
				Indx_record[Local_u8RecordCounter][DFP_TRACK]  = DFP_Track2;
				lcd_enuWriteString("Elkhair",7,0,0,LCD_1);
				/* Increment for next position of array_reacord */
				Local_u8RecordCounter++;

				/* Still in this loop until new word*/
				while((analog_rx[0] < FLEX_1) && (analog_rx[1] < FLEX_2) && (analog_rx[2] < FLEX_3) && (analog_rx[3] > FLEX_4) && (analog_rx[4] > FLEX_5))
				{
					/* read variable from POTS , ADXL */
					ADC_enuMultiChannel_RX(ADC1,channels , adc_channels , analog_rx);
				}
			}

			/* keifa */
			/*  F1 O                    ,F2 O                     ,F3 O                    ,F4 C                     ,F5  C                  */
			else if((analog_rx[0] < FLEX_1) && (analog_rx[1] < FLEX_2) && (analog_rx[2] < FLEX_3) && (analog_rx[3] > FLEX_4) && (analog_rx[4] > FLEX_5))
			{
				/* Set record Indx */
				Indx_record[Local_u8RecordCounter][DFP_FOLDER] = DFP_Folder;
				Indx_record[Local_u8RecordCounter][DFP_TRACK]  = DFP_Track3;
				lcd_enuWriteString("keifa",5,0,0,LCD_1);

				/* Increment for next position of array_reacord */
				Local_u8RecordCounter++;

				/* Still in this loop until new word*/
				while((analog_rx[0] < FLEX_1) && (analog_rx[1] < FLEX_2) && (analog_rx[2] < FLEX_3) && (analog_rx[3] > FLEX_4) && (analog_rx[4] > FLEX_5))
				{
					/* read variable from POTS , ADXL */
					ADC_enuMultiChannel_RX(ADC1,channels , adc_channels , analog_rx);
				}
			}

			/* halek -- arak lahkn */
			/*  F1 O                    ,F2 C                     ,F3 C                    ,F4 C                     ,F5 C                     ,REST  O                   ,X POSITIVE                */
			else if((analog_rx[0] < FLEX_1) && (analog_rx[1] > FLEX_2) && (analog_rx[2] > FLEX_3) && (analog_rx[3] > FLEX_4) && (analog_rx[4] > FLEX_5))
			{
				_delay_ms(500);
				ADC_enuMultiChannel_RX(ADC1,channels , adc_channels , analog_rx);

				/* Arak lahkn */
				/*  F1 O                    ,F2 O                     ,F3 C                    ,F4 C                     ,F5 C                     ,REST  O              ,X POSITIVE                */
				if((analog_rx[0] < FLEX_1) && (analog_rx[1] < FLEX_2) && (analog_rx[2] > FLEX_3) && (analog_rx[3] > FLEX_4) && (analog_rx[4] > FLEX_5))
				{
					/* Set record Indx */
					Indx_record[Local_u8RecordCounter][DFP_FOLDER] = DFP_Folder;
					Indx_record[Local_u8RecordCounter][DFP_TRACK]  = DFP_Track9;
					lcd_enuWriteString("Arak Lahkn",10,0,0,LCD_1);

					/* Increment for next position of array_reacord */
					Local_u8RecordCounter++;

					/* Still in this loop until new word*/
					while((analog_rx[0] < FLEX_1) && (analog_rx[1] < FLEX_2) && (analog_rx[2] > FLEX_3) && (analog_rx[3] > FLEX_4) && (analog_rx[4] > FLEX_5))
					{
						/* read variable from FLEX*/
						ADC_enuMultiChannel_RX(ADC1,channels , adc_channels , analog_rx);
					}
				}

				/* halek */
				else
				{
					/* Set record Indx */
					Indx_record[Local_u8RecordCounter][DFP_FOLDER] = DFP_Folder;
					Indx_record[Local_u8RecordCounter][DFP_TRACK]  = DFP_Track4;
					lcd_enuWriteString("Halek",5,0,0,LCD_1);

					/* Increment for next position of array_reacord */
					Local_u8RecordCounter++;

					/* Still in this loop until new word*/
					while((analog_rx[0] < FLEX_1) && (analog_rx[1] < FLEX_2) && (analog_rx[2] < FLEX_3) && (analog_rx[3] > FLEX_4) && (analog_rx[4] > FLEX_5))
					{
						/* read variable from POTS , ADXL */
						ADC_enuMultiChannel_RX(ADC1,channels , adc_channels , analog_rx);
					}
				}
			}

			/* shokrn  --  sllam alekm*/
			/*  F1 C                    ,F2 O                     ,F3 O                    ,F4 O                     ,F5  O                                */
			else if((analog_rx[0] > FLEX_1) && (analog_rx[1] < FLEX_2) && (analog_rx[2] < FLEX_3) && (analog_rx[3] < FLEX_4) && (analog_rx[4] < FLEX_5))
			{
				_delay_ms(500);
				ADC_enuMultiChannel_RX(ADC1,channels , adc_channels , analog_rx);

				/* sllam alekm */
				/*  F1 C                    ,F2 C                     ,F3 C                    ,F4 C                     ,F5 C                     ,REST  O              ,X POSITIVE                */
				if((analog_rx[0] > FLEX_1) && (analog_rx[1] > FLEX_2) && (analog_rx[2] > FLEX_3) && (analog_rx[3] > FLEX_4) && (analog_rx[4] > FLEX_5))
				{
					/* Set record Indx */
					Indx_record[Local_u8RecordCounter][DFP_FOLDER] = DFP_Folder;
					Indx_record[Local_u8RecordCounter][DFP_TRACK]  = DFP_Track1;
					lcd_enuWriteString("Sllam alekm",11,0,0,LCD_1);

					/* Increment for next position of array_reacord */
					Local_u8RecordCounter++;

					/* Still in this loop until new word*/
					while((analog_rx[0] > FLEX_1) && (analog_rx[1] > FLEX_2) && (analog_rx[2] > FLEX_3) && (analog_rx[3] > FLEX_4) && (analog_rx[4] > FLEX_5))
					{
						/* read variable from POTS , ADXL */
						ADC_enuMultiChannel_RX(ADC1,channels , adc_channels , analog_rx);
					}
				}
				/* shokrn */
				else
				{
					/* Set record Indx */
					Indx_record[Local_u8RecordCounter][DFP_FOLDER] = DFP_Folder;
					Indx_record[Local_u8RecordCounter][DFP_TRACK]  = DFP_Track8;
					lcd_enuWriteString("Shokrn",6,0,0,LCD_1);

					/* Increment for next position of array_reacord */
					Local_u8RecordCounter++;

					/* Still in this loop until new word*/
					while((analog_rx[0] > FLEX_1) && (analog_rx[1] < FLEX_2) && (analog_rx[2] < FLEX_3) && (analog_rx[3] < FLEX_4) && (analog_rx[4] < FLEX_5) )
					{
						/* read variable from POTS , ADXL */
						ADC_enuMultiChannel_RX(ADC1,channels , adc_channels , analog_rx);
					}
				}
			}



			/************************************************************************************************************************************************************************/

			/* AEINA */
			/*  F1 C                    ,F2 C                    ,F3 O                    ,F4 O                     ,F5  O                       */
			else if((analog_rx[0] > FLEX_1) && (analog_rx[1] > FLEX_2) && (analog_rx[2] < FLEX_3) && (analog_rx[3] < FLEX_4) && (analog_rx[4] < FLEX_5))
			{
				/* Set record Indx */
				Indx_record[Local_u8RecordCounter][DFP_FOLDER] = DFP_Folder;
				Indx_record[Local_u8RecordCounter][DFP_TRACK]  = DFP_Track2;
				lcd_enuWriteString("AEINA",5,0,0,LCD_1);

				/* Increment for next position of array_reacord */
				Local_u8RecordCounter++;

				/* Still in this loop until new word*/
				while((analog_rx[0] > FLEX_1) && (analog_rx[1] > FLEX_2) && (analog_rx[2] < FLEX_3) && (analog_rx[3] < FLEX_4) && (analog_rx[4] < FLEX_5))
				{
					/* read variable from POTS , ADXL and Bluetooth */
					ADC_enuMultiChannel_RX(ADC1,channels , adc_channels , analog_rx);				}
			}

			/* tazhab */
			/*  F1 C                    ,F2 O                     ,F3 C                        ,F4 C                   ,F5 C                     ,REST  O                  ,X POSITIVE                     */
			else if((analog_rx[0] > FLEX_1) && (analog_rx[1] < FLEX_2) && (analog_rx[2] > FLEX_3) && (analog_rx[3] > FLEX_4) && (analog_rx[4] > FLEX_5) )
			{
				/* Set record Indx */
				Indx_record[Local_u8RecordCounter][DFP_FOLDER] = DFP_Folder;
				Indx_record[Local_u8RecordCounter][DFP_TRACK]  = DFP_Track3;
				lcd_enuWriteString("Tazhab",6,0,0,LCD_1);

				/* Increment for next position of array_reacord */
				Local_u8RecordCounter++;

				/* Still in this loop until new word*/
				while((analog_rx[0] > FLEX_1) && (analog_rx[1] < FLEX_2) && (analog_rx[2] > FLEX_3) && (analog_rx[3] > FLEX_4) && (analog_rx[4] > FLEX_5))
				{
					/* read variable from FLEX */
					ADC_enuMultiChannel_RX(ADC1,channels , adc_channels , analog_rx);
				}
			}



			/************************************************************************************************************************************************************************/
			/* LADEI */
			/*       F1 O                    ,F2 C                     ,F3 C                    ,F4 C                     ,F5 C                                                */
			else if((analog_rx[0] < FLEX_1) && (analog_rx[1] > FLEX_2) && (analog_rx[2] > FLEX_3) && (analog_rx[3] > FLEX_4) && (analog_rx[4] > FLEX_5) )
			{
				/* Set record Indx */
				Indx_record[Local_u8RecordCounter][DFP_FOLDER] = DFP_Folder;
				Indx_record[Local_u8RecordCounter][DFP_TRACK]  = DFP_Track4;
				lcd_enuWriteString("LADEI",5,0,0,LCD_1);

				/* Increment for next position of array_reacord */
				Local_u8RecordCounter++;

				/* Still in this loop until new word*/
				while((analog_rx[0] < FLEX_1) && (analog_rx[1] > FLEX_2) && (analog_rx[2] > FLEX_3) && (analog_rx[3] > FLEX_4) && (analog_rx[4] > FLEX_5) )
				{
					/* read variable from FLEX */
					ADC_enuMultiChannel_RX(ADC1,channels , adc_channels , analog_rx);
				}
			}

			/* EkhTBAR */
			/*  F1 O                    ,F2 O                     ,F3 O                    ,F4 O                     ,F5 O                                                      */
			else if((analog_rx[0] < FLEX_1) && (analog_rx[1] < FLEX_2) && (analog_rx[2] < FLEX_3) && (analog_rx[3] < FLEX_4) && (analog_rx[4] < FLEX_5)  )
			{
				/* Set record Indx */
				Indx_record[Local_u8RecordCounter][DFP_FOLDER] = DFP_Folder;
				Indx_record[Local_u8RecordCounter][DFP_TRACK]  = DFP_Track5;
				lcd_enuWriteString("EkhTBAR",7,0,0,LCD_1);

				/* Increment for next position of array_reacord */
				Local_u8RecordCounter++;

				/* Still in this loop until new word*/
				while((analog_rx[0] < FLEX_1) && (analog_rx[1] < FLEX_2) && (analog_rx[2] < FLEX_3) && (analog_rx[3] < FLEX_4) && (analog_rx[4] < FLEX_5) )
				{
					/* read variable from FLEX */
					ADC_enuMultiChannel_RX(ADC1,channels , adc_channels , analog_rx);
				}
			}

			/* wdaa3n */
			/*      F1 O                    ,F2 O                     ,F3 O                    ,F4 O                     ,F5  O                      */
			else if((analog_rx[0] < FLEX_1) && (analog_rx[1] < FLEX_2) && (analog_rx[2] < FLEX_3) && (analog_rx[3] < FLEX_4) && (analog_rx[4] < FLEX_5) )
			{
				/* Set record Indx */
				Indx_record[Local_u8RecordCounter][DFP_FOLDER] = DFP_Folder;
				Indx_record[Local_u8RecordCounter][DFP_TRACK]  = DFP_Track6;
				lcd_enuWriteString("wdaa3n",6,0,0,LCD_1);

				/* Increment for next position of array_reacord */
				Local_u8RecordCounter++;

				/* Still in this loop until new word*/
				while((analog_rx[0] < FLEX_1) && (analog_rx[1] < FLEX_2) && (analog_rx[2] < FLEX_3) && (analog_rx[3] < FLEX_4) && (analog_rx[4] < FLEX_5))
				{
					/* read variable from POTS , ADXL */
					ADC_enuMultiChannel_RX(ADC1,channels , adc_channels , analog_rx);
				}
			}


			/* ana */
			/*  F1 C                    ,F2 O                     ,F3 C                        ,F4 C                   ,F5 C                      */
			else if((analog_rx[0] > FLEX_1) && (analog_rx[1] < FLEX_2) && (analog_rx[2] > FLEX_3) && (analog_rx[3] > FLEX_4) && (analog_rx[4] > FLEX_5))
			{
				/* Set record Indx */
				Indx_record[Local_u8RecordCounter][DFP_FOLDER] = DFP_Folder;
				Indx_record[Local_u8RecordCounter][DFP_TRACK]  = DFP_Track7;
				lcd_enuWriteString("ana",3,0,0,LCD_1);

				/* Increment for next position of array_reacord */
				Local_u8RecordCounter++;

				/* Still in this loop until new word*/
				while((analog_rx[0] > FLEX_1) && (analog_rx[1] < FLEX_2) && (analog_rx[2] > FLEX_3) && (analog_rx[3] > FLEX_4) && (analog_rx[4] > FLEX_5))
				{
					/* read variable from POTS , ADXL */
					ADC_enuMultiChannel_RX(ADC1,channels , adc_channels , analog_rx);
				}
			}

			/* Ready To Speak*/
			/*  F1 O                    ,F2 O                     ,F3 O                    ,F4 O                     ,F5 O                                       */
			else if((analog_rx[0] < FLEX_1) && (analog_rx[1] < FLEX_2) && (analog_rx[2] < FLEX_3) && (analog_rx[3] < FLEX_4) && (analog_rx[4] < FLEX_5)  )
			{
				/* Iterate on array Indx_record */
				for(Local_u8Counter = 0; Local_u8Counter < Local_u8RecordCounter; Local_u8Counter++)
				{
					/* play track */
					DFP_PlayTrackInFolder(Indx_record[Local_u8Counter][DFP_FOLDER],Indx_record[Local_u8Counter][DFP_TRACK],UART_1);

					/* wait 1s between each track */
					_delay_ms(1000);
				}

				/* Reset Variable */
				Local_u8RecordCounter = 0;

				/* Still in this loop until new word*/
				while((analog_rx[0] < FLEX_1) && (analog_rx[1] < FLEX_2) && (analog_rx[2] < FLEX_3) && (analog_rx[3] < FLEX_4) && (analog_rx[4] < FLEX_5))
				{
					/* read variable from POTS , ADXL */
					ADC_enuMultiChannel_RX(ADC1,channels , adc_channels , analog_rx);
				}
			}
		}/* end of arabic while */
	}/* end of if Arabic */

	/* English language <- F2  C */
	else if(analog_rx[1] > FLEX_2)
	{
		while(1)
		{
			/* read variable from FLEX */
			ADC_enuMultiChannel_RX(ADC1,channels , adc_channels , analog_rx);

			/* Stop */
			/*  F1 O                    ,F2 O                     ,F3 O                    ,F4 O                     ,F5 O                            */
			if((analog_rx[0] < FLEX_1) && (analog_rx[1] < FLEX_2) && (analog_rx[2] < FLEX_3) && (analog_rx[3] < FLEX_4) && (analog_rx[4] < FLEX_5) )
			{
				/* Set record Indx */
				Indx_record[Local_u8RecordCounter][DFP_FOLDER] = DFP_Folder;
				Indx_record[Local_u8RecordCounter][DFP_TRACK]  = DFP_Track8;
				lcd_enuWriteString("Stop",4,0,0,LCD_1);

				/* Increment for next position of array_reacord */
				Local_u8RecordCounter++;

				/* Still in this loop until new word*/
				while((analog_rx[0] < FLEX_1) && (analog_rx[1] < FLEX_2) && (analog_rx[2] < FLEX_3) && (analog_rx[3] < FLEX_4) && (analog_rx[4] < FLEX_5) )
				{
					/* read variable from POTS , ADXL */
					ADC_enuMultiChannel_RX(ADC1,channels , adc_channels , analog_rx);
				}
			}

			/* I feel pain */
			/*  F1 C                    ,F2 C                     ,F3 C                    ,F4 C                    ,F5 C                              */
			else if((analog_rx[0] > FLEX_1) && (analog_rx[1] > FLEX_2) && (analog_rx[2] > FLEX_3) && (analog_rx[3] > FLEX_4) && (analog_rx[4] > FLEX_5) )
			{
				/* Set record Indx */
				Indx_record[Local_u8RecordCounter][DFP_FOLDER] = DFP_Folder;
				Indx_record[Local_u8RecordCounter][DFP_TRACK]  = DFP_Track9;
				lcd_enuWriteString("I feel pain",11,0,0,LCD_1);

				/* Increment for next position of array_reacord */
				Local_u8RecordCounter++;

				/* Still in this loop until new word*/
				while((analog_rx[0] > FLEX_1) && (analog_rx[1] > FLEX_2) && (analog_rx[2] > FLEX_3) && (analog_rx[3] > FLEX_4) && (analog_rx[4] > FLEX_5))
				{
					/* read variable from POTS , ADXL */
					ADC_enuMultiChannel_RX(ADC1,channels , adc_channels , analog_rx);
				}
			}

			/* victory */
			/*  F1 C                    ,F2 O                     ,F3 O                    ,F4 C                     ,F5 C                            */
			else if((analog_rx[0] > FLEX_1) && (analog_rx[1] < FLEX_2) && (analog_rx[2] < FLEX_3) && (analog_rx[3] > FLEX_4) && (analog_rx[4] > FLEX_5))
			{
				/* Set record Indx */
				Indx_record[Local_u8RecordCounter][DFP_FOLDER] = DFP_Folder;
				Indx_record[Local_u8RecordCounter][DFP_TRACK]  = DFP_Track1;
				lcd_enuWriteString("victory",7,0,0,LCD_1);

				/* Increment for next position of array_reacord */
				Local_u8RecordCounter++;

				/* Still in this loop until new word*/
				while((analog_rx[0] > FLEX_1) && (analog_rx[1] < FLEX_2) && (analog_rx[2] < FLEX_3) && (analog_rx[3] > FLEX_4) && (analog_rx[4] > FLEX_5) )
				{
					/* read variable from POTS , ADXL */
					ADC_enuMultiChannel_RX(ADC1,channels , adc_channels , analog_rx);
				}
			}
			/* I Love You */
			/*  F1 O                    ,F2 O                     ,F3 C                    ,F4 C                     ,F5 O                                 */
			else if((analog_rx[0] < FLEX_1) && (analog_rx[1] < FLEX_2) && (analog_rx[2] > FLEX_3) && (analog_rx[3] > FLEX_4) && (analog_rx[4] < FLEX_5))
			{
				/* Set record Indx */
				Indx_record[Local_u8RecordCounter][DFP_FOLDER] = DFP_Folder;
				Indx_record[Local_u8RecordCounter][DFP_TRACK]  = DFP_Track2;
				lcd_enuWriteString("I Love You",10,0,0,LCD_1);

				/* Increment for next position of array_reacord */
				Local_u8RecordCounter++;

				/* Still in this loop until new word*/
				while((analog_rx[0] < FLEX_1) && (analog_rx[1] < FLEX_2) && (analog_rx[2] > FLEX_3) && (analog_rx[3] > FLEX_4) && (analog_rx[4] < FLEX_5) )
				{
					/* read variable from POTS , ADXL */
					ADC_enuMultiChannel_RX(ADC1,channels , adc_channels , analog_rx);
				}
			}

			/* See You Later  --  Good Job */
			/*  F1 O                    ,F2 C                     ,F3 C                    ,F4 C                     ,F5 C                     ,REST O                     ,X POSITIVE               */
			else if((analog_rx[0] < FLEX_1) && (analog_rx[1] > FLEX_2) && (analog_rx[2] > FLEX_3) && (analog_rx[3] > FLEX_4) && (analog_rx[4] > FLEX_5))
			{
				_delay_ms(500);
				ADC_enuMultiChannel_RX(ADC1,channels , adc_channels , analog_rx);

				/* See You Later */
				/*  F1 O                    ,F2 O                     ,F3 C                    ,F4 C                     ,F5 C                     ,REST O               ,X POSITIVE                */
				if((analog_rx[0] < FLEX_1) && (analog_rx[1] < FLEX_2) && (analog_rx[2] > FLEX_3) && (analog_rx[3] > FLEX_4) && (analog_rx[4] > FLEX_5))
				{
					/* Set record Indx */
					Indx_record[Local_u8RecordCounter][DFP_FOLDER] = DFP_Folder;
					Indx_record[Local_u8RecordCounter][DFP_TRACK]  = DFP_Track3;
					lcd_enuWriteString("See You Later",13,0,0,LCD_1);

					/* Increment for next position of array_reacord */
					Local_u8RecordCounter++;

					/* Still in this loop until new word*/
					while((analog_rx[0] < FLEX_1) && (analog_rx[1] < FLEX_2) && (analog_rx[2] > FLEX_3) && (analog_rx[3] > FLEX_4) && (analog_rx[4] > FLEX_5))
					{
						/* read variable from POTS , ADXL */
						ADC_enuMultiChannel_RX(ADC1,channels , adc_channels , analog_rx);
					}
				}
				/* Good job */
				else
				{
					/* Set record Indx */
					Indx_record[Local_u8RecordCounter][DFP_FOLDER] = DFP_Folder;
					Indx_record[Local_u8RecordCounter][DFP_TRACK]  = DFP_Track4;
					lcd_enuWriteString("Good job",8,0,0,LCD_1);

					/* Increment for next position of array_reacord */
					Local_u8RecordCounter++;

					/* Still in this loop until new word*/
					while((analog_rx[0] < FLEX_1) && (analog_rx[1] > FLEX_2) && (analog_rx[2] > FLEX_3) && (analog_rx[3] > FLEX_4) && (analog_rx[4] > FLEX_5))
					{
						/* read variable from POTS , ADXL */
						ADC_enuMultiChannel_RX(ADC1,channels , adc_channels , analog_rx);
					}
				}
			}
			/* Ready To Speak*/
			/*  F1 O                    ,F2 O                     ,F3 O                    ,F4 O                     ,F5 O                       */
			else if((analog_rx[0] < FLEX_1) && (analog_rx[1] < FLEX_2) && (analog_rx[2] < FLEX_3) && (analog_rx[3] < FLEX_4) && (analog_rx[4] < FLEX_5) )
			{
				lcd_enuWriteString("Ready To Speak",13,0,0,LCD_1);

				/* Iterate on array Indx_record */
				for(Local_u8Counter = 0; Local_u8Counter < Local_u8RecordCounter; Local_u8Counter++)
				{
					/* play track */
					DFP_PlayTrackInFolder(Indx_record[Local_u8Counter][DFP_FOLDER],Indx_record[Local_u8Counter][DFP_TRACK],UART_1);

					/* wait 1s between each track */
					_delay_ms(1000);
				}

				/* Reset Variable */
				Local_u8RecordCounter = 0;

				/* Still in this loop until new word*/
				while((analog_rx[0] < FLEX_1) && (analog_rx[1] < FLEX_2) && (analog_rx[2] < FLEX_3) && (analog_rx[3] < FLEX_4) && (analog_rx[4] < FLEX_5) )
				{
					/* read variable from FLEX*/
					ADC_enuMultiChannel_RX(ADC1,channels , adc_channels , analog_rx);
				}
			}
		}/* end of English while */
	}/* end of if ENGLISH */
}/* end of Application Function */
