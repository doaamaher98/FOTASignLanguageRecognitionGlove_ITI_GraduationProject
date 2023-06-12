/* ================================================================= */
/* Author 	: Karim Mourad											 */
/* Date		: 10 Jun 2023											 */
/* Target 	: ARM Cortex M3											 */
/* Version  : V1.0													 */
/* Descip. 	: SysTick interface file								 */
/* ================================================================= */

#include "Std_Types.h"

#ifndef STK_H_
#define STK_H_

/* ================================================ User Defined Types ================================================ */

/* Error Status */
typedef enum
{
	STK_enuOK=0,
	STK_enuNOK,
}STK_tenuErrorStatus;

/* STK Registers */
typedef struct
{
	volatile u32 STK_CTRL ;
	volatile u32 STK_LOAD ;
	volatile u32 STK_VAL  ;
	volatile u32 STK_CALIB;
}SYSTICK_tstrRegisters;


/* ======================================= Definitions ======================================= */
#define 				STK_INT_EN  				 1
#define 				STK_INT_DIS 				 0


#define 				STK 						((volatile SYSTICK_tstrRegisters*)0xE000E010)

/* =============================================== APIs ============================================================= */
STK_tenuErrorStatus STK_enuInit(void);

STK_tenuErrorStatus STK_enuStart(u32 Cpy_u32PreloadValue);

STK_tenuErrorStatus STK_enuINTStatus(u8 Cpy_u8Status);

u8 STK_u8ReadFlag(void);


/* ================================== CallBack Function ================================== */
void STK_voidSetCallBack(void (*ptr)(void));




#endif /* SYSTICK_H_ */
