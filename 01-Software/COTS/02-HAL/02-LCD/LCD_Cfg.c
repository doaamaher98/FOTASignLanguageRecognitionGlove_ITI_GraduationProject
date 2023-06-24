/*************************************************************************************************************************************
* Module:      LED Configuration                                                                                                     *
* File Name:   LED_Cfg.c                                                                                                             *
* Description: Source file for configuration of LED driver                                                                           *
* Author:      Esraa_Mohamed                                                                                                         *
**************************************************************************************************************************************/

/*============================================================ INCLUDE ==============================================================*/

#include "GPIO.h"
#include "LCD_Cfg.h"
#include "LCD.h"

/*============================================================ VARIABLES ============================================================*/

/****************************************
 * For each LCD
 ****************************************
 **********************
 * PINS_CONFIGURATION
 **********************
 * .PORT:
 *         GPIO_enuGPIOA
 *         GPIO_enuGPIOB
 *         GPIO_enuGPIOC
 *
 * .PIN:
 * 		  GPIO_PIN0 ->  GPIO_PIN15
 *
 * .Mode:
 *
 *	GPIO_enuOutput_10MHz_PP
 *	GPIO_enuOutput_10MHz_OD
 *
 *	GPIO_enuOutput_2MHz_PP
 *	GPIO_enuOutput_2MHz_OD
 *
 *	GPIO_enuOutput_50MHz_PP
 *	GPIO_enuOutput_50MHz_OD
 *
 *
 **********************
 * LCD_C/C's
 **********************
 *
 * .NUM_LINES:
 *        LCD_ONE_LINE         CMD_FUNCTION_SET_ONE_LINE
 *		  LCD_TWO_LINES        CMD_FUNCTION_SET_TWO_LINE
 * 	      LCD_FOUR_LINES
 *
 * .NUM_COL:
 *        LCD_16_COL
 *  	  LCD_20_COL
 *
 * .Cursor:
 *	      CURSOR_OFF           CMD_DISPLAY_CURSOR_OFF
 *        CURSOR_ON            CMD_DISPLAY_CURSOR_ON
 *        CURSOR_ON_BLINK      CMD_DISPLAY_CURSOR_ON | CMD_DISPLAY_CURSOR_BLINKING
 *
 * .CharPexcel:
 *        LCD_CHAR_PEXCEL_5X8  CMD_FUNCTION_SET_CHAR_PEXCEL_5X8
 *        LCD_CHAR_PEXCEL_5X11 CMD_FUNCTION_SET_CHAR_PEXCEL_5X11
 *
 * .BackLight:
 *        LCD_BACKLIGHT_OFF
 *        LCD_BACKLIGHT_ON
 *
 * .Mode:
 *        LCD_MODE_4BITS
 *        LCD_MODE_8BITS
 *
 *
 ****************************************/
const LCD_strCfg_t Lcd_Cfg [LCD_Count]
=
{
		[LCD_1]=
		{
				/* Configuration of RS pin */
				.LCD_strCfgPins_t.RSPin.GPIO_Port  = GPIO_enuGPIOA,
				.LCD_strCfgPins_t.RSPin.GPIO_Pin   = GPIO_enuPin_5,
				.LCD_strCfgPins_t.RSPin.GPIO_Mode  = GPIO_enuOutput_10MHz_PP,

				/* Configuration of R/W pin */
				.LCD_strCfgPins_t.RWPin.GPIO_Port  = GPIO_enuGPIOA,
				.LCD_strCfgPins_t.RWPin.GPIO_Pin   = GPIO_enuPin_6,
				.LCD_strCfgPins_t.RWPin.GPIO_Mode  = GPIO_enuOutput_10MHz_PP,

				/* Configuration of EN pin */
				.LCD_strCfgPins_t.EnablePin.GPIO_Port  = GPIO_enuGPIOA,
				.LCD_strCfgPins_t.EnablePin.GPIO_Pin   = GPIO_enuPin_7,
				.LCD_strCfgPins_t.EnablePin.GPIO_Mode  = GPIO_enuOutput_10MHz_PP,

				/* Configuration of DATA_0 pin */
				.LCD_strCfgPins_t.DataPins[DATA_0].GPIO_Port  = GPIO_enuGPIOA,
				.LCD_strCfgPins_t.DataPins[DATA_0].GPIO_Pin   = GPIO_enuPin_8,
				.LCD_strCfgPins_t.DataPins[DATA_0].GPIO_Mode  = GPIO_enuOutput_10MHz_PP,

				/* Configuration of DATA_1 pin */
				.LCD_strCfgPins_t.DataPins[DATA_1].GPIO_Port  = GPIO_enuGPIOB,
				.LCD_strCfgPins_t.DataPins[DATA_1].GPIO_Pin   = GPIO_enuPin_0,
				.LCD_strCfgPins_t.DataPins[DATA_1].GPIO_Mode  = GPIO_enuOutput_10MHz_PP,

				/* Configuration of DATA_2 pin */
				.LCD_strCfgPins_t.DataPins[DATA_2].GPIO_Port  = GPIO_enuGPIOB,
				.LCD_strCfgPins_t.DataPins[DATA_2].GPIO_Pin   = GPIO_enuPin_1,
				.LCD_strCfgPins_t.DataPins[DATA_2].GPIO_Mode  = GPIO_enuOutput_10MHz_PP,

				/* Configuration of DATA_3 pin */
				.LCD_strCfgPins_t.DataPins[DATA_3].GPIO_Port  = GPIO_enuGPIOB,
				.LCD_strCfgPins_t.DataPins[DATA_3].GPIO_Pin   = GPIO_enuPin_5,
				.LCD_strCfgPins_t.DataPins[DATA_3].GPIO_Mode  = GPIO_enuOutput_10MHz_PP,

				/* Configuration of DATA_4 pin */
				.LCD_strCfgPins_t.DataPins[DATA_4].GPIO_Port  = GPIO_enuGPIOB,
				.LCD_strCfgPins_t.DataPins[DATA_4].GPIO_Pin   = GPIO_enuPin_6,
				.LCD_strCfgPins_t.DataPins[DATA_4].GPIO_Mode  = GPIO_enuOutput_10MHz_PP,

				/* Configuration of DATA_5 pin */
				.LCD_strCfgPins_t.DataPins[DATA_5].GPIO_Port  = GPIO_enuGPIOB,
				.LCD_strCfgPins_t.DataPins[DATA_5].GPIO_Pin   = GPIO_enuPin_7,
				.LCD_strCfgPins_t.DataPins[DATA_5].GPIO_Mode  = GPIO_enuOutput_10MHz_PP,

				/* Configuration of DATA_6 pin */
				.LCD_strCfgPins_t.DataPins[DATA_6].GPIO_Port  = GPIO_enuGPIOB,
				.LCD_strCfgPins_t.DataPins[DATA_6].GPIO_Pin   = GPIO_enuPin_8,
				.LCD_strCfgPins_t.DataPins[DATA_6].GPIO_Mode  = GPIO_enuOutput_10MHz_PP,

				/* Configuration of DATA_7 pin */
				.LCD_strCfgPins_t.DataPins[DATA_7].GPIO_Port  = GPIO_enuGPIOB,
				.LCD_strCfgPins_t.DataPins[DATA_7].GPIO_Pin   = GPIO_enuPin_9,
				.LCD_strCfgPins_t.DataPins[DATA_7].GPIO_Mode  = GPIO_enuOutput_10MHz_PP,

				/* Configuration of LCD operations */
			    .LCD_strCfgOperations_t.NUM_LINES  = CMD_FUNCTION_SET_TWO_LINE,
				.LCD_strCfgOperations_t.NUM_COL    = LCD_16_COL,
				.LCD_strCfgOperations_t.CharPexcel = CMD_FUNCTION_SET_CHAR_PEXCEL_5X8,
			    .LCD_strCfgOperations_t.BackLight  = LCD_BACKLIGHT_ON,
				.LCD_strCfgOperations_t.CursorMode = CMD_DISPLAY_CURSOR_ON | CMD_DISPLAY_CURSOR_BLINKING,
				.LCD_strCfgOperations_t.Mode       = LCD_MODE_8BITS,
		}
};

/*============================================================== THE_END ============================================================*/
