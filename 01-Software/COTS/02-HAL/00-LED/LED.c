/* ================================================================= */
/* Author 	: Doaa Maher											 */
/* Date		: 11 Jun 2023											 */
/* Target 	: ARM Cortex M3											 */
/* Version  : V1.0													 */
/* Descip. 	: LED main file											 */
/* ================================================================= */
#include "GPIO.h"
#include "LED.h"

/*********************** APIs Implementations ********************/
LED_tenuErrorStatus LED_enuSetLEDValue (LED_tenuLEDPorts Led_Port,LED_tenuLEDPins Led_Pin, LED_tenuActiveStatus Cpy_u8LEDVal)
{
	LED_tenuErrorStatus LocalErrorStatus = LED_enuOK;

	GPIO_enuSetPinValue(LED_tstrConfig[Led_Port].LED_Port, LED_tstrConfig[Led_Pin].LED_Pin, LED_tstrConfig[Led_Pin].LED_ActiveStatus);

	return LocalErrorStatus;
}
/**********************************************************************************/
LED_tenuErrorStatus LED_enuToggleLED   (LED_tenuLEDPorts Led_Port,LED_tenuLEDPins Led_Pin, LED_tenuActiveStatus Cpy_u8LEDVal)
{
	LED_tenuErrorStatus LocalErrorStatus = LED_enuOK;

	GPIO_enuSetPinValue(LED_tstrConfig[Led_Port].LED_Port, LED_tstrConfig[Led_Pin].LED_Pin, 0 ^ LED_tstrConfig[Led_Pin].LED_ActiveStatus);

	return LocalErrorStatus;
}
/**********************************************************************************/
