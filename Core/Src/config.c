/*
 * config.c
 *
 *  Created on: Oct 8, 2021
 *      Author: Michal Makowka
 */
#include "config.h"


void SystemCFG (void) {

	// RCC clock EN configuration
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOBEN | RCC_AHBENR_GPIOCEN;	// GPIO Clk Enable
	RCC->APB1ENR |= RCC_APB1ENR_CANEN;												// CAN Clk Enable

	// Status LEDs GPIO config
	GPIOC->MODER |= GPIO_MODER_MODER6_0 | GPIO_MODER_MODER7_0 | GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0;	// GPIO Output mode
	// CAN bus GPIO config
	GPIOA->MODER |= GPIO_MODER_MODER11_1 | GPIO_MODER_MODER12_1;	// GPIO Alternative Mode (CANbx)
	GPIOA->AFR[1] |= (0b1001 << 12) | (0b1001 << 16);	// PA11 and PA12 AF set to CAN_Tx and CAN_Rx

}

