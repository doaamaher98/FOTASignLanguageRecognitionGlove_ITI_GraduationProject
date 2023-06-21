/*
 * UART_Cfg.h
 *
 *  Created on: 18 Jun 2023
 *      Author: HP
 */

#ifndef UART_CFG_H_
#define UART_CFG_H_

#include "UART.h"

/* System Clock */

#define F_CPU                    8000000UL

/* UART1_Configuration */
#define UART1_STATUS            UART_ENABLE
#define UART1_BAUD_RATE         (u32)9600

#define UART1_WORD_LENGTH       _8BIT_WORD_LENGTH
#define UART1_PARITY            PARITY_DISABLE
#define UART1_INTERRUPT         INT_DISABLE

#define UART1_TRANSMITTER       TRANSMITTER_ENABLE
#define UART1_RECEIVER          RECEIVER_ENABLE

#define UART1_STOP_BITS         ONE_STOP_BIT



/* UART2_Configuration */
#define UART2_STATUS            UART_DISABLE
#define UART2_BAUD_RATE         (u32)9600

#define UART2_WORD_LENGTH       _8BIT_WORD_LENGTH
#define UART2_PARITY            PARITY_DISABLE
#define UART2_INTERRUPT         INT_DISABLE

#define UART2_TRANSMITTER       TRANSMITTER_ENABLE
#define UART2_RECEIVER          RECEIVER_ENABLE

#define UART2_STOP_BITS         ONE_STOP_BIT



/* UART3_Configuration */
#define UART3_STATUS            UART_ENABLE
#define UART3_BAUD_RATE         (u32)9600

#define UART3_WORD_LENGTH       _8BIT_WORD_LENGTH
#define UART3_PARITY            PARITY_DISABLE
#define UART3_INTERRUPT         INT_DISABLE

#define UART3_TRANSMITTER       TRANSMITTER_ENABLE
#define UART3_RECEIVER          RECEIVER_ENABLE

#define UART3_STOP_BITS         ONE_STOP_BIT



#endif /* UART_CFG_H_ */
