/* ================================================================= */
/* Author 	: Doaa Maher											 */
/* Date		: 11 Jun 2023											 */
/* Target 	: ARM Cortex M3											 */
/* Version  : V1.0													 */
/* Descip. 	: LED Config main file									 */
/* ================================================================= */

#include "GPIO.h"

#include "LED.h"

const LED_tstrConfig_t LED_tstrConfig [LED_enuLED_Count] =
{
	[LED_enuLED_Warning] =
	{
		.LED_Color = LED_enuLED_Red,
		.LED_Pin = GPIO_enuPin_0,
		.LED_Port = GPIO_enuGPIOA,
		.LED_ActiveStatus = LED_enuActiveHigh,
		.LED_State = LED_enuLED_ON,
		.LED_Speed = GPIO_enuOutput_10MHz_PP,
	},

};
