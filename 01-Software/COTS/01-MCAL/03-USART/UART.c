/*
 * UART.c
 *
 *  Created on: 18 Jun 2023
 *      Author: HP
 */

#include "Std_Types.h"
#include "Bit_Math.h"

#include "UART.h"
#include "UART_Cfg.h"
/******************************************************************************************************************/

#define THRESHOLD_VALUE  9000000UL
#define IDLE 0
#define BUSY 1
#define NOT_INIT 2

#define TX_COMPLETE_INTERRUPT_ENABLE 0x00000040
#define RX_COMPLETE_INTERRUPT_ENABLE 0x00000020
/******************************************************************************************************************/
typedef struct{

	volatile u32 SR;
	volatile u32 DR;
	volatile u32 BRR;
	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 CR3;
	volatile u32 GTPR;

}UART_Type;
/******************************************************************************************************************/

#define MUART1 ( ( volatile UART_Type* ) 0x40013800 )

#define MUART2 ( ( volatile UART_Type* ) 0x40004400 )

#define MUART3 ( ( volatile UART_Type* ) 0x40004800 )
/******************************************************************************************************************/

void (*MUART1_CallBack)(void);
void (*MUART2_CallBack)(void);
void (*MUART3_CallBack)(void);

/*Global variables for sending*/
static u8 Tx_State[3] = {NOT_INIT,NOT_INIT,NOT_INIT};
static u8 * Tx_Buffer[3] = {NULL_PTR,NULL_PTR,NULL_PTR};
static u32 Tx_Size[3] = {0,0,0};
static u32 Tx_Idx[3] = {0,0,0};
//static CBF_t Tx_CBF[3] = {NULL_PTR,NULL_PTR,NULL_PTR};


/*Global variables for recieveing*/
static u8 Rx_State[3] = {NOT_INIT,NOT_INIT,NOT_INIT};
static u8 * Rx_Buffer[3] = {NULL_PTR,NULL_PTR,NULL_PTR};
static u32 Rx_Size[3] = {0,0,0};
static u32 Rx_Idx[3] = {0,0,0};
//static CBF_t Rx_CBF[3] = {NULL_PTR,NULL_PTR,NULL_PTR};

/******************************************************************************************************************/
static void UART_HANDLER(UART_CHANNELS_t Cpy_Channel)
{
	switch(Cpy_Channel)
	{
		case UART_1:
		{
			if(((MUART1->SR >> 6) & 0x1) && (Tx_State[Cpy_Channel] == BUSY))
			{
				if(Tx_Idx[Cpy_Channel] < Tx_Size[Cpy_Channel])
				{
					MUART1->DR = Tx_Buffer[Cpy_Channel][Tx_Idx[Cpy_Channel]];
					Tx_Idx[Cpy_Channel]++;
				}
				else
				{
					Tx_State[Cpy_Channel] = IDLE;
					MUART1->CR1 &= ~(TX_COMPLETE_INTERRUPT_ENABLE);

				}

			}



			//if(((UART[Cpy_Channel]->SR >> 5) & 0x1) && )
			//else if((Rx_State[Cpy_Channel] == BUSY))
			if(((MUART1->SR >> 5) & 0x1) && (Rx_State[Cpy_Channel] == BUSY))
			{
				if(Rx_Idx[Cpy_Channel] < (Rx_Size[Cpy_Channel]))
				{
					Rx_Buffer[Cpy_Channel][Rx_Idx[Cpy_Channel]] = (u8)MUART1->DR;
					Rx_Idx[Cpy_Channel]++;
				}
				if(Rx_Idx[Cpy_Channel] == (Rx_Size[Cpy_Channel]))
				{
					Rx_State[Cpy_Channel] = IDLE;
					MUART1->CR1 &= ~(RX_COMPLETE_INTERRUPT_ENABLE);

				}

			}
			break;
		}

		case UART_2:
		{
			if(((MUART2->SR >> 6) & 0x1) && (Tx_State[Cpy_Channel] == BUSY))
			{
				if(Tx_Idx[Cpy_Channel] < Tx_Size[Cpy_Channel])
				{
					MUART2->DR = Tx_Buffer[Cpy_Channel][Tx_Idx[Cpy_Channel]];
					Tx_Idx[Cpy_Channel]++;
				}
				else
				{
					Tx_State[Cpy_Channel] = IDLE;
					MUART2->CR1 &= ~(TX_COMPLETE_INTERRUPT_ENABLE);

				}

			}



			//if(((UART[Cpy_Channel]->SR >> 5) & 0x1) && )
			//else if((Rx_State[Cpy_Channel] == BUSY))
			if(((MUART2->SR >> 5) & 0x1) && (Rx_State[Cpy_Channel] == BUSY))
			{
				if(Rx_Idx[Cpy_Channel] < (Rx_Size[Cpy_Channel]))
				{
					Rx_Buffer[Cpy_Channel][Rx_Idx[Cpy_Channel]] = (u8)MUART2->DR;
					Rx_Idx[Cpy_Channel]++;
				}
				if(Rx_Idx[Cpy_Channel] == (Rx_Size[Cpy_Channel]))
				{
					Rx_State[Cpy_Channel] = IDLE;
					MUART2->CR1 &= ~(RX_COMPLETE_INTERRUPT_ENABLE);

				}

			}
			break;
		}

		case UART_3:
		{
			if(((MUART3->SR >> 6) & 0x1) && (Tx_State[Cpy_Channel] == BUSY))
			{
				if(Tx_Idx[Cpy_Channel] < Tx_Size[Cpy_Channel])
				{
					MUART3->DR = Tx_Buffer[Cpy_Channel][Tx_Idx[Cpy_Channel]];
					Tx_Idx[Cpy_Channel]++;
				}
				else
				{
					Tx_State[Cpy_Channel] = IDLE;
					MUART3->CR1 &= ~(TX_COMPLETE_INTERRUPT_ENABLE);

				}

			}
			//if(((UART[Cpy_Channel]->SR >> 5) & 0x1) && )
			//else if((Rx_State[Cpy_Channel] == BUSY))
			if(((MUART3->SR >> 5) & 0x1) && (Rx_State[Cpy_Channel] == BUSY))
			{
				if(Rx_Idx[Cpy_Channel] < (Rx_Size[Cpy_Channel]))
				{
					Rx_Buffer[Cpy_Channel][Rx_Idx[Cpy_Channel]] = (u8)MUART3->DR;
					Rx_Idx[Cpy_Channel]++;
				}
				if(Rx_Idx[Cpy_Channel] == (Rx_Size[Cpy_Channel]))
				{
					Rx_State[Cpy_Channel] = IDLE;
					MUART3->CR1 &= ~(RX_COMPLETE_INTERRUPT_ENABLE);

				}
			}
			break;
		}

	}
}
/******************************************************************************************************************/
void MUART_VidInit(void)
{
	u32 LOC_u64Mantissa1 = ( F_CPU ) / ( 16 * UART1_BAUD_RATE ) ;

	u32 LOC_u64Fraction1 = ( ( ( F_CPU * 100 ) / ( 16 * UART1_BAUD_RATE )  ) % 100 ) * 16 ;

	if( LOC_u64Fraction1 > 1500 ){ LOC_u64Mantissa1 += 1 ; LOC_u64Fraction1  = 0 ; }


	u32 LOC_u64Mantissa2 = ( F_CPU ) / ( 16 * UART2_BAUD_RATE ) ;

	u32 LOC_u64Fraction2 = ( ( ( F_CPU * 100 ) / ( 16 * UART2_BAUD_RATE )  ) % 100 ) * 16 ;

	if( LOC_u64Fraction2 > 1500 ){ LOC_u64Mantissa2 += 1 ; LOC_u64Fraction2  = 0 ; }


	u32 LOC_u64Mantissa3 = ( F_CPU ) / ( 16 * UART3_BAUD_RATE ) ;

	u32 LOC_u64Fraction3 = ( ( ( F_CPU * 100 ) / ( 16 * UART3_BAUD_RATE )  ) % 100 ) * 16 ;

	if( LOC_u64Fraction3 > 1500 ){ LOC_u64Mantissa3 += 1 ; LOC_u64Fraction3  = 0 ; }

#if UART1_STATUS == 1

		MUART1 -> SR = 0 ;

		#if   UART1_WORD_LENGTH == _8BIT_WORD_LENGTH

					CLR_BIT( MUART1 -> CR1 , 12 );

		#elif UART1_WORD_LENGTH == _9BIT_WORD_LENGTH

					SET_BIT( MUART1 -> CR1 , 12 );

		#endif

		#if   UART1_PARITY == PARITY_DISABLE

					CLR_BIT( MUART1 -> CR1 , 10 );

		#elif UART1_PARITY == EVEN_PARITY

					SET_BIT( MUART1 -> CR1 , 10 );
					CLR_BIT( MUART1 -> CR1 , 11 );

		#elif UART1_PARITY == ODD_PARITY

					SET_BIT( MUART1 -> CR1 , 10 );
					SET_BIT( MUART1 -> CR1 , 11 );

		#endif

		#if  UART1_INTERRUPT == INT_DISABLE

					CLR_BIT( MUART1 -> CR1 , 5 );
					CLR_BIT( MUART1 -> CR1 , 6 );
					CLR_BIT( MUART1 -> CR1 , 7 );

		#elif UART1_INTERRUPT == TXE_INT_ENABLE

					SET_BIT( MUART1 -> CR1 , 7 );

		#elif UART1_INTERRUPT == TCE_INT_ENABLE

					SET_BIT( MUART1 -> CR1 , 6 );

		#elif UART1_INTERRUPT == RXNE_INT_ENABLE

					SET_BIT( MUART1 -> CR1 , 5 );

		#endif

		#if   UART1_TRANSMITTER == TRANSMITTER_ENABLE

					SET_BIT( MUART1 -> CR1 , 3 );

		#elif UART1_TRANSMITTER == TRANSMITTER_DISABLE

					CLR_BIT( MUART1 -> CR1 , 3 );

		#endif

		#if   UART1_RECEIVER == RECEIVER_ENABLE

					SET_BIT( MUART1 -> CR1 , 2 );

		#elif UART1_RECEIVER == RECEIVER_DISBLE

					CLR_BIT( MUART1 -> CR1 , 2 );

		#endif

		#if   UART1_STOP_BITS == ONE_STOP_BIT

					CLR_BIT( MUART1 -> CR2 , 12 ); CLR_BIT( MUART1 -> CR2 , 13 );

		#elif UART1_STOP_BITS == HALF_STOP_BIT

					SET_BIT( MUART1 -> CR2 , 12 ); CLR_BIT( MUART1 -> CR2 , 13 );

		#elif UART1_STOP_BITS == TWO_STOP_BIT

					CLR_BIT( MUART1 -> CR2 , 12 ); SET_BIT( MUART1 -> CR2 , 13 );

		#elif UART1_STOP_BITS == ONE_AND_HALF_STOP_BIT

					SET_BIT( MUART1 -> CR2 , 12 ); SET_BIT( MUART1 -> CR2 , 13 );


		#endif

		MUART1 -> BRR = ( LOC_u64Mantissa1 << 4  ) | ( LOC_u64Fraction1 / 100 ) ;
		SET_BIT( MUART1 -> CR1 , 13 );

	#elif UART1_STATUS == UART1_DISABLE
		CLR_BIT( MUART1 -> CR1 , 0 );

	#endif

#if UART2_STATUS == UART2_ENABLE

		MUART2 -> SR = 0 ;

		#if   UART2_WORD_LENGTH == _8BIT_WORD_LENGTH

					CLR_BIT( MUART2 -> CR1 , 12 );

		#elif UART2_WORD_LENGTH == _9BIT_WORD_LENGTH

					SET_BIT( MUART2 -> CR1 , 12 );

		#endif

		#if   UART2_PARITY == PARITY_DISABLE

					CLR_BIT( MUART2 -> CR1 , 10 );

		#elif UART2_PARITY == EVEN_PARITY

					SET_BIT( MUART2 -> CR1 , 10 );
					CLR_BIT( MUART2 -> CR1 , 11 );

		#elif UART2_PARITY == ODD_PARITY

					SET_BIT( MUART2 -> CR1 , 10 );
					SET_BIT( MUART2 -> CR1 , 11 );

		#endif

		#if  UART2_INTERRUPT == INT_DISABLE

					CLR_BIT( MUART2 -> CR1 , 5 );
					CLR_BIT( MUART2 -> CR1 , 6 );
					CLR_BIT( MUART2 -> CR1 , 7 );

		#elif UART2_INTERRUPT == TXE_INT_ENABLE

					SET_BIT( MUART2 -> CR1 , 7 );

		#elif UART2_INTERRUPT == TCE_INT_ENABLE

					SET_BIT( MUART2 -> CR1 , 6 );

		#elif UART2_INTERRUPT == RXNE_INT_ENABLE

					SET_BIT( MUART2 -> CR1 , 5 );

		#endif

		#if   UART2_TRANSMITTER == TRANSMITTER_ENABLE

					SET_BIT( MUART2 -> CR1 , 3 );

		#elif UART2_TRANSMITTER == TRANSMITTER_DISABLE

					CLR_BIT( MUART2 -> CR1 , 3 );

		#endif

		#if   UART2_RECEIVER == RECEIVER_ENABLE

					SET_BIT( MUART2 -> CR1 , 2 );

		#elif UART2_RECEIVER == RECEIVER_DISBLE

					CLR_BIT( MUART2 -> CR1 , 2 );

		#endif

		#if   UART2_STOP_BITS == ONE_STOP_BIT

					CLR_BIT( MUART2 -> CR2 , 12 ); CLR_BIT( MUART2 -> CR2 , 13 );

		#elif UART2_STOP_BITS == HALF_STOP_BIT

					SET_BIT( MUART2 -> CR2 , 12 ); CLR_BIT( MUART2 -> CR2 , 13 );

		#elif UART2_STOP_BITS == TWO_STOP_BIT

					CLR_BIT( MUART2 -> CR2 , 12 ); SET_BIT( MUART2 -> CR2 , 13 );

		#elif UART2_STOP_BITS == ONE_AND_HALF_STOP_BIT

					SET_BIT( MUART2 -> CR2 , 12 ); SET_BIT( MUART2 -> CR2 , 13 );


		#endif

		MUART2 -> BRR = ( LOC_u64Mantissa2 << 4  ) | ( LOC_u64Fraction2 / 100 ) ;
		SET_BIT( MUART2 -> CR1 , 13 );

	#elif UART2_STATUS == UART2_DISABLE
		CLR_BIT( MUART2 -> CR1 , 0 );

	#endif

#if UART3_STATUS == UART3_ENABLE

		MUART3 -> SR = 0 ;

		#if   UART3_WORD_LENGTH == _8BIT_WORD_LENGTH

					CLR_BIT( MUART3 -> CR1 , 12 );

		#elif UART3_WORD_LENGTH == _9BIT_WORD_LENGTH

					SET_BIT( MUART3 -> CR1 , 12 );

		#endif

		#if   UART3_PARITY == PARITY_DISABLE

					CLR_BIT( MUART3 -> CR1 , 10 );

		#elif UART3_PARITY == EVEN_PARITY

					SET_BIT( MUART3 -> CR1 , 10 );
					CLR_BIT( MUART3 -> CR1 , 11 );

		#elif UART3_PARITY == ODD_PARITY

					SET_BIT( MUART3 -> CR1 , 10 );
					SET_BIT( MUART3 -> CR1 , 11 );

		#endif

		#if  UART3_INTERRUPT == INT_DISABLE

					CLR_BIT( MUART3 -> CR1 , 5 );
					CLR_BIT( MUART3 -> CR1 , 6 );
					CLR_BIT( MUART3 -> CR1 , 7 );

		#elif UART3_INTERRUPT == TXE_INT_ENABLE

					SET_BIT( MUART3 -> CR1 , 7 );

		#elif UART3_INTERRUPT == TCE_INT_ENABLE

					SET_BIT( MUART3 -> CR1 , 6 );

		#elif UART3_INTERRUPT == RXNE_INT_ENABLE

					SET_BIT( MUART3 -> CR1 , 5 );

		#endif

		#if   UART3_TRANSMITTER == TRANSMITTER_ENABLE

					SET_BIT( MUART3 -> CR1 , 3 );

		#elif UART3_TRANSMITTER == TRANSMITTER_DISABLE

					CLR_BIT( MUART3 -> CR1 , 3 );

		#endif

		#if   UART3_RECEIVER == RECEIVER_ENABLE

					SET_BIT( MUART3 -> CR1 , 2 );

		#elif UART3_RECEIVER == RECEIVER_DISBLE

					CLR_BIT( MUART3 -> CR1 , 2 );

		#endif

		#if   UART3_STOP_BITS == ONE_STOP_BIT

					CLR_BIT( MUART3 -> CR2 , 12 ); CLR_BIT( MUART3 -> CR2 , 13 );

		#elif UART3_STOP_BITS == HALF_STOP_BIT

					SET_BIT( MUART3 -> CR2 , 12 ); CLR_BIT( MUART3 -> CR2 , 13 );

		#elif UART3_STOP_BITS == TWO_STOP_BIT

					CLR_BIT( MUART3 -> CR2 , 12 ); SET_BIT( MUART3 -> CR2 , 13 );

		#elif UART3_STOP_BITS == ONE_AND_HALF_STOP_BIT

					SET_BIT( MUART3 -> CR2 , 12 ); SET_BIT( MUART3 -> CR2 , 13 );


		#endif

		MUART3 -> BRR = ( LOC_u64Mantissa3 << 4  ) | ( LOC_u64Fraction3 / 100 ) ;
		SET_BIT( MUART3 -> CR1 , 13 );

	#elif UART3_STATUS == UART3_DISABLE
		CLR_BIT( MUART3 -> CR1 , 0 );

	#endif


}
/******************************************************************************************************************/
void MUART_VidSendCharSync(u8 Copy_u8Char , UART_CHANNELS_t Channel_No)
{
	switch(Channel_No)
	{
		case UART_1:
			MUART1 -> DR = Copy_u8Char ;
			while( GET_BIT( MUART1 -> SR , 6 ) == 0 );
			CLR_BIT( MUART1 -> SR , 6 );
			break;

		case UART_2:
			MUART2 -> DR = Copy_u8Char ;
			while( GET_BIT( MUART2 -> SR , 6 ) == 0 );
			CLR_BIT( MUART2 -> SR , 6 );
			break;

		case UART_3:
			MUART3 -> DR = Copy_u8Char ;
			while( GET_BIT( MUART3 -> SR , 6 ) == 0 );
			CLR_BIT( MUART3 -> SR , 6 );
			break;
	}
}
/******************************************************************************************************************/
void MUART_VidSendStringSynch(u8 * Copy_ptrString , UART_CHANNELS_t Channel_No)
{

	u8 LOC_u8Iterator = 0 ;
	while ( Copy_ptrString[ LOC_u8Iterator ] != '\0' ){

		MUSART_VidSendCharSync( Copy_ptrString[ LOC_u8Iterator ] , Channel_No);
		LOC_u8Iterator++ ;

	}
}
/******************************************************************************************************************/
u8 MUART_u8RecCharSynch(UART_CHANNELS_t Channel_No)
{
	u8  LOC_u8Data  = 0 ;
	u32 LOC_TimeOut = 0 ;

	switch(Channel_No)
	{
		case UART_1:
			CLR_BIT ( MUART1 -> SR, 5);

			while( ( GET_BIT ( MUART1 -> SR, 5) == 0 ) && ( LOC_TimeOut < THRESHOLD_VALUE ) )
			{
				LOC_TimeOut++;
			}

			if( LOC_TimeOut == THRESHOLD_VALUE )
			{
				LOC_u8Data = 255;
			}
			else
			{

				LOC_u8Data = MUART1 -> DR;
			}
			break;

		case UART_2:
			CLR_BIT ( MUART2 -> SR, 5);

			while( ( GET_BIT ( MUART2 -> SR, 5) == 0 ) && ( LOC_TimeOut < THRESHOLD_VALUE ) )
			{
				LOC_TimeOut++;
			}

			if( LOC_TimeOut == THRESHOLD_VALUE )
			{
				LOC_u8Data = 255;
			}
			else
			{

				LOC_u8Data = MUART2 -> DR;
			}
			break;

		case UART_3:
			CLR_BIT ( MUART3 -> SR, 5);

			while( ( GET_BIT ( MUART3 -> SR, 5) == 0 ) && ( LOC_TimeOut < THRESHOLD_VALUE ) )
			{
				LOC_TimeOut++;
			}

			if( LOC_TimeOut == THRESHOLD_VALUE )
			{
				LOC_u8Data = 255;
			}
			else
			{

				LOC_u8Data = MUART3 -> DR;
			}
			break;

	}
	return LOC_u8Data;
}
/******************************************************************************************************************/
u8 String[20];
u8 * MUART_PtrReadStringSynch(UART_CHANNELS_t Channel_No)
{
	u8 LOC_Iterator = 0 , LOC_u8DataCome ;

	while( ( LOC_u8DataCome = MUART_u8RecCharSynch(Channel_No) ) != 13 ){

		String[ LOC_Iterator ] = LOC_u8DataCome ;
		LOC_Iterator++;
	}

	String[LOC_Iterator] = '\0';

	return ( String );
}
/******************************************************************************************************************/
void MUART_VidSetCallBack( void (*ptr) (void) , UART_CHANNELS_t Channel_No)
{
	switch(Channel_No)
	{
		case UART_1:
			MUART1_CallBack = ptr ;
			break;

		case UART_2:
			MUART2_CallBack = ptr ;
			break;

		case UART_3:
			MUART3_CallBack = ptr ;
			break;
	}
}
/******************************************************************************************************************/
void UART_SendAsynchZeroCpy(UART_CHANNELS_t Cpy_Channel, u8 * buffer, u32 size, void (*ptr) (void))
{
	if(Tx_State[Cpy_Channel] == IDLE)
	{
		Tx_State[Cpy_Channel] = BUSY;
		Tx_Buffer[Cpy_Channel] = buffer;
		Tx_Size[Cpy_Channel] = size;
		Tx_Idx[Cpy_Channel] = 0;
		if(ptr != NULL_PTR)
		{
			MUART_VidSetCallBack( ptr , Cpy_Channel);
		}

		switch(Cpy_Channel)
		{
			case UART_1:
				MUART1->DR = Tx_Buffer[Cpy_Channel][Tx_Idx[Cpy_Channel]];
				MUART1->CR1 |= TX_COMPLETE_INTERRUPT_ENABLE;
				break;

			case UART_2:
				MUART2->DR = Tx_Buffer[Cpy_Channel][Tx_Idx[Cpy_Channel]];
				MUART2->CR1 |= TX_COMPLETE_INTERRUPT_ENABLE;
				break;

			case UART_3:
				MUART3->DR = Tx_Buffer[Cpy_Channel][Tx_Idx[Cpy_Channel]];
				MUART3->CR1 |= TX_COMPLETE_INTERRUPT_ENABLE;
				break;
		}
		Tx_Idx[Cpy_Channel]++;
	}
}
/******************************************************************************************************************/
void UART_ReceiveAsynchZeroCpy(UART_CHANNELS_t Cpy_Channel, u8 * buffer, u32 size, void (*ptr) (void))
{
	if(Rx_State[Cpy_Channel] == IDLE)
	{

		Rx_Buffer[Cpy_Channel] = buffer;
		Rx_Size[Cpy_Channel] = size;
		Rx_Idx[Cpy_Channel] = 0;
		Rx_State[Cpy_Channel] = BUSY;
		if(ptr != NULL_PTR)
		{
			MUART_VidSetCallBack( ptr , Cpy_Channel);
		}

		switch(Cpy_Channel)
		{
			case UART_1:
				MUART1->CR1 |= RX_COMPLETE_INTERRUPT_ENABLE;
				break;

			case UART_2:
				MUART2->CR1 |= RX_COMPLETE_INTERRUPT_ENABLE;
				break;

			case UART_3:
				MUART3->CR1 |= RX_COMPLETE_INTERRUPT_ENABLE;
				break;
		}

	}
}
/******************************************************************************************************************/
void USART1_IRQHandler(void){

	UART_HANDLER(UART_1);

	MUART1 -> SR = 0 ;
	MUART1_CallBack();
}
/******************************************************************************************************************/
void USART2_IRQHandler(void){

	UART_HANDLER(UART_2);

	MUART2 -> SR = 0 ;
	MUART2_CallBack();
}
/******************************************************************************************************************/
void USART3_IRQHandler(void){

	UART_HANDLER(UART_3);
	MUART3 -> SR = 0 ;
	MUART3_CallBack();
}
/******************************************************************************************************************/
