/* ================================================================= */
/* Author 	: Doaa Maher											 */
/* Date		: 8 Jun 2023											 */
/* Target 	: ARM Cortex M3											 */
/* Version  : V1.0													 */
/* Descip. 	: RCC configurations file								 */
/* ================================================================= */

#ifndef RCC_CONFIG_H
#define RCC_CONFIG_H

/* ===================== Clock Source Selection ===================== */
/* Options :-
   ==========
   1- RCC_enuHSI
   2- RCC_enuHSE_CRYSTAL
   3- RCC_enuHSE_RC
   4- RCC_enuPLL
*/
#define						RCC_SYSCLK_SRC					RCC_enuHSI			

#if RCC_SYSCLK_SRC == RCC_enuPLL
	/* ===================== PLL Input Source ===================== */
	/* Options :-
	   ==========
	   1- RCC_enuIN_PLL_HSI_DIV2
	   2- RCC_enuIN_PLL_HSE_DIV2
	   3- RCC_enuIN_PLL_HSE
	*/
	#define					RCC_PLL_INPUT				RCC_enuIN_PLL_HSI_DIV2
	
	/* ===================== PLL Multiplication Factor ===================== */
	/* Options :-
	   ==========
	   1- RCC_enuPLL_2
	   2- RCC_enuPLL_3
	   3- RCC_enuPLL_4
	   4- RCC_enuPLL_5
	   5- RCC_enuPLL_6
	   6- RCC_enuPLL_7
	   7- RCC_enuPLL_8
	   8- RCC_enuPLL_9
	   9- RCC_enuPLL_10
	   10- RCC_enuPLL_11
	   11- RCC_enuPLL_12
	   12- RCC_enuPLL_13
	   13- RCC_enuPLL_14
	   14- RCC_enuPLL_15
	   15- RCC_enuPLL1_16
	   16- RCC_enuPLL2_16
	*/
	#define					RCC_PLL_FACTOR				RCC_enuPLL1_16
#endif




























/* ===================== APB2 Prescaler ===================== */
/* Options :-
   ==========
   1- RCC_enuAPB2_NOT_DIVIDED
   2- RCC_enuAPB2_DIV_BY_2
   3- RCC_enuAPB2_DIV_BY_4
   4- RCC_enuAPB2_DIV_BY_8
   5- RCC_enuAPB2_DIV_BY_16
*/
#define					RCC_APB2_PRESCALER			RCC_enuAPB2_DIV_BY_2


/* ===================== APB1 Prescaler ===================== */
/* Options :-
   ==========
   1- RCC_enuAPB1_NOT_DIVIDED
   2- RCC_enuAPB1_DIV_BY_2
   3- RCC_enuAPB1_DIV_BY_4
   4- RCC_enuAPB1_DIV_BY_8
   5- RCC_enuAPB1_DIV_BY_16
*/
#define					RCC_APB1_PRESCALER			RCC_enuAPB1_DIV_BY_4


/* ===================== AHB Prescaler ===================== */
/* Options :-
   ==========
   1- RCC_enuAHB_NOT_DIVIDED
   2- RCC_enuAHB_DIV_BY_2
   3- RCC_enuAHB_DIV_BY_4
   4- RCC_enuAHB_DIV_BY_8
   5- RCC_enuAHB_DIV_BY_16
   6- RCC_enuAHB_DIV_BY_64
   7- RCC_enuAHB_DIV_BY_128
   8- RCC_enuAHB_DIV_BY_256
   9- RCC_enuAHB_DIV_BY_512
*/
#define					RCC_AHB_PRESCALER			RCC_enuAHB_DIV_BY_64








#endif