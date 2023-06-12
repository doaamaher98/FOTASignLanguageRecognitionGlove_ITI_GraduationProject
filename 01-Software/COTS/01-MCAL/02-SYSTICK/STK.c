/* ================================================================= */
/* Author 	: Karim Mourad											 */
/* Date		: 10 Jun 2023											 */
/* Target 	: ARM Cortex M3											 */
/* Version  : V1.0													 */
/* Descip. 	: SysTick main program									 */
/* ================================================================= */

#include "Bit_Math.h"

#include "STK.h"


/* ======================================= Global pointer to function (Callback Functions) ======================================= */
void (*STK_CallBack) (void);



/***************************************************************************************/
void STK_voidSetCallBack(void (*ptr)(void))
{
	STK_CallBack = ptr;
}
/***************************************************************************************/
STK_tenuErrorStatus STK_enuInit(void)
{
	STK_tenuErrorStatus LocalErrorStatus = STK_enuOK;

	/* Enable Systick Interrupt  -  Clock = AHB / 8 - Stop STK */
	STK->STK_CTRL = 0x00000002;

	return LocalErrorStatus;
}
/***************************************************************************************/

STK_tenuErrorStatus STK_enuStart(u32 Cpy_u32PreloadValue)
{
	STK_tenuErrorStatus LocalErrorStatus = STK_enuOK;

	/* AHB = EXT = 8MHZ & CLOCK OF MSTK = AHB / 8 = 8MHZ / 8 = 1MHZ = 1u For Each Count */

	/* Load Reload Value */
	STK->STK_LOAD = Cpy_u32PreloadValue - 1;

	/* Clear Val Register */
	STK->STK_VAL  = 0 ;

	/* Enable Systick */
	SET_BIT( STK->STK_CTRL , 0 );

	return LocalErrorStatus;
}
/***************************************************************************************/
STK_tenuErrorStatus STK_enuINTStatus(u8 Cpy_u8Status)
{
	STK_tenuErrorStatus LocalErrorStatus = STK_enuOK;

	 STK->STK_CTRL &= ~( 1 << 1 );
	 STK->STK_CTRL |=  ( Cpy_u8Status << 1 );

	 return LocalErrorStatus;
}
/***************************************************************************************/
u8 STK_u8ReadFlag( void )
{
	return ( GET_BIT( STK->STK_CTRL , 16 ) );
}
/***************************************************************************************/
void SysTick_Handler(void)
{
	STK_CallBack();
}
/***************************************************************************************/
