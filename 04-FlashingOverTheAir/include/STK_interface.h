#ifndef SYSTICK_INTERFACE_H
#define SYSTICK_INTERFACE_H

void MSTK_voidInit(void);
void MSTK_voidSetBusyWait(u32 Copy_u32Ticks);
void MSTK_voidSetIntervalSingle  (u32 Copy_u32Ticks , void (*Copy_ptr) (void));
void MSTK_voidSetIntervalPeriodic(u32 Copy_u32Ticks , void (*Copy_ptr) (void));
void MSTK_voidStopInterval(void);
u32 MSTK_u32GetElapseTime(void);
u32 MSTK_u32GetRemainingTime(void);

#endif
