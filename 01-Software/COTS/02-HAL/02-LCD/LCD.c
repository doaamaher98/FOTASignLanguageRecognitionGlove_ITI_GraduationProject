/*************************************************************************************************************************************
* Module:      LCD                                                                                                                   *
* File Name:   LCD.c                                                                                                                 *
* Description: Source file include implementation of LCD module Functions                                                            *
* Author:      Esraa_Mohamed                                                                                                         *
**************************************************************************************************************************************/

/*============================================================ INCLUDE ==============================================================*/

#include "GPIO.h"
#include "Delay.h"
#include "LCD_Cfg.h"
#include "LCD.h"

/*============================================================ DEFINES ==============================================================*/

#define  NOT_INIT                             0
#define  INIT_DONE                            1


#define POWERON_DELAY                         40
#define LCD_DELAY                             2

#define DATA_WIDTH                            8

#define GET_BITSTATUS                         1

#define POS_X0                                1
#define POS_Y0                                0

#define  LCD_FIRST_LINE                       0x00
#define  LCD_SECOND_LINE                      0x01
#define  LCD_THIRD_LINE                       0x02
#define  LCD_FOURTH_LINE                      0x03

/*============================================================= TYPES ===============================================================*/

extern const LCD_strCfg_t Lcd_Cfg [LCD_Count];
/*=========================================================== VARIABLES =============================================================*/

u8 g_lcdInit  = NOT_INIT ;

static LCD_enuLCDState_t g_lcdState[LCD_Count] = {LCD_STATE_POWERON};

/*=================================================== STATIC_API'S_PROTOTYPES =======================================================*/

static void write (u8 Cpy_u8Data, u8 Cpy_u8LCDNum);

static void writeCommand (u8 Cpy_u8Command, u8 Cpy_u8LCDNum);

static void writeData(u8 Cpy_u8Data, u8 Cpy_u8LCDNum);

static void goToXY (u8 Cpy_u8PosX, u8 Cpy_u8PosY,u8 Cpy_u8LCDNum);

/*======================================================== APIS_DEFINATION ==========================================================*/

void lcd_vidInit(void)
{
	u8 Loc_u8Counter = 0;
	u8 Loc_u8DataCount = 0;

	/* Initialize lcd's  */
	for(Loc_u8Counter =0; Loc_u8Counter< LCD_Count; ++Loc_u8Counter)
	{
		/* 1-Control pins */
		GPIO_enuSetPinDirection (Lcd_Cfg [Loc_u8Counter].LCD_strCfgPins_t.RSPin.GPIO_Port, Lcd_Cfg [Loc_u8Counter].LCD_strCfgPins_t.RSPin.GPIO_Pin,Lcd_Cfg [Loc_u8Counter].LCD_strCfgPins_t.RSPin.GPIO_Mode);
		GPIO_enuSetPinDirection (Lcd_Cfg [Loc_u8Counter].LCD_strCfgPins_t.RWPin.GPIO_Port, Lcd_Cfg [Loc_u8Counter].LCD_strCfgPins_t.RWPin.GPIO_Pin,Lcd_Cfg [Loc_u8Counter].LCD_strCfgPins_t.RWPin.GPIO_Mode);
		GPIO_enuSetPinDirection (Lcd_Cfg [Loc_u8Counter].LCD_strCfgPins_t.EnablePin.GPIO_Port, Lcd_Cfg [Loc_u8Counter].LCD_strCfgPins_t.EnablePin.GPIO_Pin,Lcd_Cfg [Loc_u8Counter].LCD_strCfgPins_t.EnablePin.GPIO_Mode);

		/* 2-Data/Command pins */
		for(Loc_u8DataCount =0; Loc_u8DataCount< NUM_DATA; ++Loc_u8DataCount)
		{
			GPIO_enuSetPinDirection (Lcd_Cfg [Loc_u8Counter].LCD_strCfgPins_t.DataPins[Loc_u8DataCount].GPIO_Port, Lcd_Cfg [Loc_u8Counter].LCD_strCfgPins_t.DataPins[Loc_u8DataCount].GPIO_Pin,Lcd_Cfg [Loc_u8Counter].LCD_strCfgPins_t.DataPins[Loc_u8DataCount].GPIO_Mode);
		}

		_delay_ms(POWERON_DELAY);

		/* Write Function_Set Command to initialize number of line and character_pexcel */
	    if (Lcd_Cfg[Loc_u8Counter].LCD_strCfgOperations_t.Mode == LCD_MODE_4BITS)
		{
			writeCommand(CMD_INITIALIZE_LCD_4BIT_MODE ,Loc_u8Counter);
			writeCommand(CMD_FUNCTION_SET_MODE_4_BITS | Lcd_Cfg[Loc_u8Counter].LCD_strCfgOperations_t.NUM_LINES |Lcd_Cfg[Loc_u8Counter].LCD_strCfgOperations_t.CharPexcel , Loc_u8Counter);
		}
		else
		{
	    	writeCommand(CMD_FUNCTION_SET_MODE_8_BITS | Lcd_Cfg[Loc_u8Counter].LCD_strCfgOperations_t.NUM_LINES |Lcd_Cfg[Loc_u8Counter].LCD_strCfgOperations_t.CharPexcel, Loc_u8Counter);
		}

	    _delay_ms(LCD_DELAY);

	    /* Display ON/OFF Control Command to initialize displaying and set cursor mode*/
		writeCommand(CMD_DisplayON_OFF | Lcd_Cfg[Loc_u8Counter].LCD_strCfgOperations_t.CursorMode, Loc_u8Counter);

		_delay_ms(LCD_DELAY);

		/* Clear Screen Command to clear screen at beginning */
		writeCommand(CMD_CLEAR_SCREEN, Loc_u8Counter);
		_delay_ms(LCD_DELAY);

		g_lcdState[Loc_u8Counter] = LCD_STATE_IDLE;
	}
}

                                      /***************************************************/

LCD_enuLCDState_t lcd_enuWriteString(const char* string,u8 Copy_u8StringLength,u8 Copy_u8PosX,u8 Copy_u8PosY,u8 Copy_u8LcdName)
{
	LCD_enuLCDState_t LCD_enuLCDState = LCD_STATE_IDLE;
	u8 Loc_u8currentPos =0;
	static u8 LCD_MAX_LOC;
	static u8 LCD_MAX_LINE;

	LCD_MAX_LOC = Lcd_Cfg[Copy_u8LcdName].LCD_strCfgOperations_t.NUM_COL;

	switch(Lcd_Cfg[Copy_u8LcdName].LCD_strCfgOperations_t.NUM_LINES)
	{
		case CMD_FUNCTION_SET_ONE_LINE:
			LCD_MAX_LINE= LCD_FIRST_LINE;
			break;
		case CMD_FUNCTION_SET_TWO_LINE:
			LCD_MAX_LINE= LCD_SECOND_LINE;
			break;
	}

	if(g_lcdState[Copy_u8LcdName] == LCD_STATE_IDLE)
	{
		LCD_enuLCDState = LCD_STATE_OK;
		goToXY(Copy_u8PosX, Copy_u8PosY, Copy_u8LcdName);

		while(Loc_u8currentPos != Copy_u8StringLength)
		{

			if( (Loc_u8currentPos) && (Loc_u8currentPos % LCD_MAX_LOC == 0) )
		     {

				if(Copy_u8PosX < LCD_MAX_LINE)
				{
					Copy_u8PosX++;
					goToXY (Copy_u8PosX,POS_Y0,Copy_u8LcdName);
				}
				else
				{
					Copy_u8PosX=LCD_FIRST_LINE;
					goToXY (Copy_u8PosX,POS_Y0,Copy_u8LcdName);
				}
			 }
			 writeData(string[Loc_u8currentPos],Copy_u8LcdName);
			 Loc_u8currentPos++;
		}

		g_lcdState[Copy_u8LcdName] = LCD_STATE_IDLE;

	}
	else
	{
		LCD_enuLCDState = LCD_STATE_NOT_INITIALIZED;
	}

    return	LCD_enuLCDState;
}
                                      /***************************************************/

LCD_enuLCDState_t lcd_enuClear(u8 Copy_u8LcdName)
{
	LCD_enuLCDState_t LCD_enuLCDState = LCD_STATE_IDLE;

	if(g_lcdState[Copy_u8LcdName] == LCD_STATE_IDLE)
	{
		writeCommand(CMD_CLEAR_SCREEN, Copy_u8LcdName);
		writeCommand(CMD_CURSOR_RETURN_HOME, Copy_u8LcdName);
	}
	else
	{
		LCD_enuLCDState = LCD_STATE_NOT_INITIALIZED;
	}

    return	LCD_enuLCDState;
}

/*=================================================== STATIC_API'S_DEFINITION =======================================================*/

static void write (u8 Cpy_u8Data, u8 Cpy_u8LCDNum)
{
	u8 Loc_u8Counter = 0;
	GPIO_tenuPinState Loc_u8BitStatus = 0;
	GPIO_enuSetPinValue (Lcd_Cfg [Cpy_u8LCDNum].LCD_strCfgPins_t.RWPin.GPIO_Port, Lcd_Cfg [Cpy_u8LCDNum].LCD_strCfgPins_t.RWPin.GPIO_Pin, GPIO_enuLOW);
	GPIO_enuSetPinValue (Lcd_Cfg [Cpy_u8LCDNum].LCD_strCfgPins_t.EnablePin.GPIO_Port,Lcd_Cfg [Cpy_u8LCDNum].LCD_strCfgPins_t.EnablePin.GPIO_Pin,GPIO_enuHIGH);

	if(Lcd_Cfg [Cpy_u8LCDNum].LCD_strCfgOperations_t.Mode == LCD_MODE_8BITS)
	{
		for(Loc_u8Counter =0; Loc_u8Counter < DATA_WIDTH; ++Loc_u8Counter)
		{
			Loc_u8BitStatus = ( Cpy_u8Data >> Loc_u8Counter) & GET_BITSTATUS;
			GPIO_enuSetPinValue(Lcd_Cfg [Cpy_u8LCDNum].LCD_strCfgPins_t.DataPins[Loc_u8Counter].GPIO_Port, Lcd_Cfg [Cpy_u8LCDNum].LCD_strCfgPins_t.DataPins[Loc_u8Counter].GPIO_Pin , Loc_u8BitStatus );
		}
	}
	else
	{
		for(Loc_u8Counter = LCD_MODE_4BITS; Loc_u8Counter < DATA_WIDTH ; ++Loc_u8Counter)
		{
			Loc_u8BitStatus = ( Cpy_u8Data >> Loc_u8Counter) & GET_BITSTATUS;
			GPIO_enuSetPinValue(Lcd_Cfg [Cpy_u8LCDNum].LCD_strCfgPins_t.DataPins[Loc_u8Counter].GPIO_Port,Lcd_Cfg [Cpy_u8LCDNum].LCD_strCfgPins_t.DataPins[Loc_u8Counter].GPIO_Pin, Loc_u8BitStatus);
		}
		GPIO_enuSetPinValue (Lcd_Cfg [Cpy_u8LCDNum].LCD_strCfgPins_t.EnablePin.GPIO_Port,Lcd_Cfg [Cpy_u8LCDNum].LCD_strCfgPins_t.EnablePin.GPIO_Pin,GPIO_enuLOW);
		GPIO_enuSetPinValue (Lcd_Cfg [Cpy_u8LCDNum].LCD_strCfgPins_t.EnablePin.GPIO_Port,Lcd_Cfg [Cpy_u8LCDNum].LCD_strCfgPins_t.EnablePin.GPIO_Pin,GPIO_enuHIGH);

		for(Loc_u8Counter = 0; Loc_u8Counter < LCD_MODE_4BITS; ++Loc_u8Counter)
		{
			Loc_u8BitStatus = ( Cpy_u8Data >> Loc_u8Counter) & GET_BITSTATUS;
			GPIO_enuSetPinValue(Lcd_Cfg [Cpy_u8LCDNum].LCD_strCfgPins_t.DataPins[Loc_u8Counter].GPIO_Port,Lcd_Cfg [Cpy_u8LCDNum].LCD_strCfgPins_t.DataPins[Loc_u8Counter].GPIO_Pin, Loc_u8BitStatus);
		}

	}

	GPIO_enuSetPinValue (Lcd_Cfg [Cpy_u8LCDNum].LCD_strCfgPins_t.EnablePin.GPIO_Port,Lcd_Cfg [Cpy_u8LCDNum].LCD_strCfgPins_t.EnablePin.GPIO_Pin,GPIO_enuLOW);
}

                                      /***************************************************/
static void writeCommand (u8 Cpy_u8Command, u8 Cpy_u8LCDNum)
{
	GPIO_enuSetPinValue (Lcd_Cfg [Cpy_u8LCDNum].LCD_strCfgPins_t.RSPin.GPIO_Port,Lcd_Cfg [Cpy_u8LCDNum].LCD_strCfgPins_t.RSPin.GPIO_Pin,GPIO_enuLOW);
	write(Cpy_u8Command,Cpy_u8LCDNum);
}

                                      /***************************************************/
static void writeData(u8 Cpy_u8Data, u8 Cpy_u8LCDNum)
{
	GPIO_enuSetPinValue (Lcd_Cfg [Cpy_u8LCDNum].LCD_strCfgPins_t.RSPin.GPIO_Port,Lcd_Cfg [Cpy_u8LCDNum].LCD_strCfgPins_t.RSPin.GPIO_Pin,GPIO_enuHIGH);
	write(Cpy_u8Data,Cpy_u8LCDNum);
}

                                      /***************************************************/
static void goToXY (u8 Cpy_u8PosX, u8 Cpy_u8PosY,u8 Cpy_u8LCDNum)
{
	u8 Loc_u8Location =0;

	/* first of all calculate the required location */
	switch(Cpy_u8PosX)
	{
		case LCD_FIRST_LINE:
				Loc_u8Location= (Cpy_u8PosY | FIRST_LINE);
				break;
		case LCD_SECOND_LINE:
				Loc_u8Location= (Cpy_u8PosY | SECOND_LINE);
				break;
		case LCD_THIRD_LINE:
				Loc_u8Location= (Cpy_u8PosY | THIRD_LINE);
				break;
		case LCD_FOURTH_LINE:
				Loc_u8Location= (Cpy_u8PosY | FOURTH_LINE);
				break;
	}
	/* to write to a specific address in the LCD
	 * we need to apply the corresponding command 0b10000000+Location */
	writeCommand(Loc_u8Location | CMD_SET_DDRAM_ADDRESS ,Cpy_u8LCDNum);

}
/*============================================================== THE_END ============================================================*/
