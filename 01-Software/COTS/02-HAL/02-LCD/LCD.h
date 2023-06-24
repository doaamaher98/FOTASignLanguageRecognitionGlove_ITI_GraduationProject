/*************************************************************************************************************************************
* Module:      LCD Interface                                                                                                         *
* File Name:   LCD.h                                                                                                                 *
* Description: Header file for LCD module include functions prototype                                                                *
* Author:      Esraa_Mohamed                                                                                                         *
**************************************************************************************************************************************/
#ifndef LCD_H_
#define LCD_H_

/*============================================================ INCLUDE ==============================================================*/

#include "STD_TYPES.h"

/*============================================================ DEFINEs ==============================================================*/

/****************************************************************
*                      MASKS                                    *
*****************************************************************/
#define  LCD_MODE_4BITS                       0x04
#define  LCD_MODE_8BITS                       0x08

#define  FIRST_LINE                           0x00
#define  SECOND_LINE                          0x40
#define  THIRD_LINE                           0x10
#define  FOURTH_LINE                          0x50

#define  LCD_16_COL                           0x10
#define  LCD_20_COL                           0x14

/* LCD Commands */
#define  CMD_INITIALIZE_LCD_4BIT_MODE         0x02
#define  CMD_FUNCTION_SET_MODE_4_BITS         0X20
#define  CMD_FUNCTION_SET_MODE_8_BITS         0X30
#define  CMD_DisplayON_OFF                    0X08


#define  CMD_FUNCTION_SET_ONE_LINE            0x00
#define  CMD_FUNCTION_SET_TWO_LINE            0x08

#define  CMD_FUNCTION_SET_CHAR_PEXCEL_5X8     0X00
#define  CMD_FUNCTION_SET_CHAR_PEXCEL_5X11    0x04


#define  CMD_DISPLAY_CURSOR_OFF               0x0C
#define  CMD_DISPLAY_CURSOR_ON                0x0E
#define  CMD_DISPLAY_CURSOR_BLINKING          0x01

#define  CMD_CLEAR_SCREEN                     0x01


#define  CMD_CURSOR_DISPLAY_SHIFT             0x10
#define  CMD_CURSOR_DISPLAY_RIGHT             0x14

#define  CMD_CURSOR_RETURN_HOME               0x02

#define  CMD_SET_DDRAM_ADDRESS	              0x80
#define  CMD_SET_CGRAM_ADDRESS		          0x40

/*============================================================== TYPES  =============================================================*/
/* PIN_CONFIGURATION */
typedef struct
{
	GPIO_tenuPorts  GPIO_Port;
	GPIO_tenuPins   GPIO_Pin;
	u8    GPIO_Mode;
}GPIO_strPinConfg_t;

/*========== LCD_CONFIGURATION =============*/
typedef struct
{
	/*======== LCD_PINS_CONFIGURATION =========*/
    struct
	{
		GPIO_strPinConfg_t  RSPin;
		GPIO_strPinConfg_t  RWPin;
		GPIO_strPinConfg_t  EnablePin;
		GPIO_strPinConfg_t  DataPins[NUM_DATA];
	}LCD_strCfgPins_t;

	/*===== LCD_Operations_CONFIGURATION ======*/
	struct
	{
		u8 NUM_LINES;
		u8 NUM_COL;
		u8 BackLight;
		u8 CursorMode;
		u8 CharPexcel;
		u8 Font;
		u8 Mode;
	}LCD_strCfgOperations_t;

}LCD_strCfg_t;

/*============ LCD_BACKLIGHT ==============*/
typedef enum
	{
		LCD_BACKLIGHT_OFF,
		LCD_BACKLIGHT_ON
	}LCD_enuLCDBackLight_t;

/*============== LCD_STATE ===============*/
typedef enum
	{
		LCD_STATE_POWERON,
		LCD_STATE_IDLE,
		LCD_STATE_NOT_INITIALIZED,
		LCD_STATE_OK
	}LCD_enuLCDState_t;

/*========================================================= APIS_PROTOTYPES =========================================================*/

/*
*  Description:  Initialize lcd's pins will be used
*/

void lcd_vidInit(void);

/*
*  Input :       Name of LCD want to write on it, string that will be written, in which line and column
*  Description:  Write the string passed on the passed LCD in the line and the column passed
*  Return:       LCD_enuLCDState_t to report LCD state
*/
LCD_enuLCDState_t lcd_enuWriteString(const char* string,u8 Copy_u8StringLength,u8 Copy_u8PosX,u8 Copy_u8PosY,u8 Copy_u8LcdName);

/*
*  Input :       Name of LCD want to clear it
*  Description:  Clear the passed LCD
*  Return:       LCD_enuLCDState_t to report LCD state
*/
LCD_enuLCDState_t lcd_enuClear(u8 Copy_u8LcdName);

#endif /* LCD_H_ */
/*============================================================== THE_END ============================================================*/
