/* ================================================================= */
/* Author 	: Karim Mourad											 */
/* Date		: 10 Jun 2023											 */
/* Target 	: ARM Cortex M3											 */
/* Version  : V1.0													 */
/* Descip. 	: Delay Program											 */
/* ================================================================= */

#include "STK.h"
#include "Delay.h"


void _delay_ms(u32 Cpy_u32Time)
{
	STK_enuInit();

	/* Disable INT */
	STK_enuINTStatus(STK_INT_DIS);

	STK_enuStart(Cpy_u32Time * 1000);

	/* Polling for the Flag */
	while( STK_u8ReadFlag() == 0 );
}
