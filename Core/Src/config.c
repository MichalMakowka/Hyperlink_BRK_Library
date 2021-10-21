/*
 * config.c
 *
 *  Created on: Oct 8, 2021
 *      Author: Michal Makowka
 */
#include "config.h"


void SystemCFG (void) {


	// *** Configure System Clock (36MHz for each system BUS) ***
	RCC->CFGR |= RCC_CFGR_PLLMUL9;		// PLL Mult = X9
	RCC->CFGR |= RCC_CFGR_SW_PLL;				// System Clock MUX switched to PLL
	RCC->CFGR |= RCC_CFGR_HPRE_DIV2;		// AHB DIV = /2
	RCC->CFGR |= (RCC_CFGR_PPRE1_DIV1 << RCC_CFGR_PPRE1_Pos);	// PLL PPRE1 = /1
	RCC->CFGR |= (RCC_CFGR_SW_PLL << RCC_CFGR_SW_Pos);
	RCC->CFGR |= (RCC_CFGR_PLLSRC_HSE_PREDIV);
	RCC->CR |= RCC_CR_HSEON;	// HSE ON
	while (!(RCC->CR & RCC_CR_HSERDY)); // Wait for HSE ON
	RCC->CR |= RCC_CR_PLLON;	// PLL ON
	while ((RCC->CR & RCC_CR_PLLRDY)); // Check if PLL not locked
	FLASH->ACR = FLASH_ACR_PRFTBE | FLASH_ACR_LATENCY_1;
	while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);	// Check for a correct source set
	RCC->CR &= ~RCC_CR_HSION;	// 8MHz HSI OFF


	// RCC clock EN configuration
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOBEN | RCC_AHBENR_GPIOCEN;	// GPIO Clk Enable
	RCC->APB1ENR |= RCC_APB1ENR_CANEN;												// CAN Clk Enable

	// Status LEDs GPIO config
	GPIOC->MODER |= GPIO_MODER_MODER6_0 | GPIO_MODER_MODER7_0 | GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0;	// GPIO Output mode
	// CAN bus GPIO config
	GPIOA->MODER |= GPIO_MODER_MODER11_1 | GPIO_MODER_MODER12_1;	// GPIO Alternative Mode (CANbx)
	GPIOA->AFR[1] |= (0b1001 << 12) | (0b1001 << 16);	// PA11 and PA12 AF set to CAN_Tx and CAN_Rx

}

