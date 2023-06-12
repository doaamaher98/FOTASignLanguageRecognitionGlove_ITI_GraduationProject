/* ================================================================= */
/* Author 	: Doaa Maher											 */
/* Date		: 11 Jun 2023											 */
/* Target 	: ARM Cortex M3											 */
/* Version  : V1.0													 */
/* Descip. 	: LED header file										 */
/* ================================================================= */

#ifndef 	LED_H
#define		LED_H

#include "Std_Types.h"
#include "LED_Cfg.h"


// Error Status
typedef enum
{
	LED_enuOK=0,
	LED_enuNOK,
	LED_enuInvalidPin,
	LED_enuInvalidPort,
	LED_enuInvalidState,
	LED_enuInvalidSpeed,
	LED_enuInvalidType
}LED_tenuErrorStatus;

// Struct with LED Config
typedef struct
{
	LED_tenuLEDName LED_Name;
	LED_tenuLEDColor LED_Color;
	LED_tenuLEDPorts LED_Port;
	LED_tenuLEDPins LED_Pin;
	LED_tenuState LED_State;
	LED_tenuActiveStatus LED_ActiveStatus;
	u8 LED_Speed;
}LED_tstrConfig_t;


// Extern Array
extern const LED_tstrConfig_t LED_tstrConfig [LED_enuLED_Count];

/******************************* APIs *********************************/
LED_tenuErrorStatus LED_enuSetLEDValue (LED_tenuLEDPorts Led_Port,LED_tenuLEDPins Led_Pin, LED_tenuActiveStatus Cpy_u8LEDVal);
LED_tenuErrorStatus LED_enuToggleLED   (LED_tenuLEDPorts Led_Port,LED_tenuLEDPins Led_Pin, LED_tenuActiveStatus Cpy_u8LEDVal);

#endif
