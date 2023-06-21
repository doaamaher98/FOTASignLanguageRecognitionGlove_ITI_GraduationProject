/*
 * UART.h
 *
 *  Created on: 18 Jun 2023
 *      Author: HP
 */

#ifndef UART_H_
#define UART_H_

#include "Std_Types.h"


#define UART_DISABLE          0
#define UART_ENABLE           1

#define _8BIT_WORD_LENGTH       0
#define _9BIT_WORD_LENGTH       1

#define PARITY_DISABLE          0
#define EVEN_PARITY             1
#define ODD_PARITY              2

#define INT_DISABLE             0
#define TXE_INT_ENABLE          1
#define TCE_INT_ENABLE          3
#define RXNE_INT_ENABLE         5

#define TRANSMITTER_DISABLE     0
#define TRANSMITTER_ENABLE      1

#define RECEIVER_DISBLE         0
#define RECEIVER_ENABLE         1

#define ONE_STOP_BIT            0
#define HALF_STOP_BIT           1
#define TWO_STOP_BIT            2
#define ONE_AND_HALF_STOP_BIT   3


typedef enum
{
	UART_1,
	UART_2,
	UART_3
}UART_CHANNELS_t;

void MUART_VidInit(void);

void MUART_VidSendCharSync(u8 Copy_u8Char , UART_CHANNELS_t Channel_No);

void MUART_VidSendStringSynch(u8 * Copy_ptrString , UART_CHANNELS_t Channel_No);

u8 MUART_u8RecCharSynch(UART_CHANNELS_t Channel_No);

u8 * MUART_PtrReadStringSynch(UART_CHANNELS_t Channel_No);

void MUART_VidSetCallBack( void (*ptr) (void) , UART_CHANNELS_t Channel_No);

void UART_SendAsynchZeroCpy(UART_CHANNELS_t Cpy_Channel, u8 * buffer, u32 size, void (*ptr) (void));

void UART_ReceiveAsynchZeroCpy(UART_CHANNELS_t Cpy_Channel, u8 * buffer, u32 size, void (*ptr) (void));




#endif /* UART_H_ */
