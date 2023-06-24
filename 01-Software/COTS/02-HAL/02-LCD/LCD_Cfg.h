/*************************************************************************************************************************************
* Module:      LCD Configuration                                                                                                     *
* File Name:   LCD_Cfg.h                                                                                                             *
* Description: Configuration header file for LCD Module                                                                              *
* Author:      Esraa_Mohamed                                                                                                         *
**************************************************************************************************************************************/
#ifndef LCD_CFG_H_
#define LCD_CFG_H_

/*============================================================= TYPES ===============================================================*/

/* Define LCD's will use */
typedef enum
{
	LCD_1,
	LCD_Count,
}LCD_enuCfg_t;


/* Define LCD's Data Pins */
typedef enum
{
	DATA_0,
	DATA_1,
	DATA_2,
	DATA_3,
	DATA_4,
	DATA_5,
	DATA_6,
	DATA_7,
	NUM_DATA
}LCD_enuDATA_t;

#endif /* LCD_CFG_H_ */
/*============================================================== THE_END ============================================================*/




