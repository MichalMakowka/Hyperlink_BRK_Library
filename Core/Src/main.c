/*
 * main.c
 *
 *	Hyperlink Braking System Library
 *
 *  Created on: 8 Oct 2021
 *  Author: Michal Makowka
 *
 *  v1.0
 *
 *  (C) All rights reserved.
 *
 *  https://mmttechnologies.com/
 */
#include <stdio.h>
#include <string.h>
#include "stm32f303x8.h"
#include "config.h"
#include "can.h"





int main(void)
{

	CAN_MESSAGE brkon;
		strcpy(brkon.data, "br_b_50");
		brkon.format = STANDARD_FORMAT;
		brkon.id = 0x01;
		brkon.len = sizeof(brkon.data);
		brkon.type = DATA_FRAME;

	CAN_MESSAGE brkoff;
		strcpy(brkoff.data, "br_b_00");
		brkoff.format = STANDARD_FORMAT;
		brkoff.id = 0x01;
		brkoff.len = sizeof(brkoff.data);
		brkoff.type = DATA_FRAME;


	SystemCFG();	// Configure essential registers
	CanInit();


	Can_Set_Filter(0x02, STANDARD_FORMAT);



	int idx = 0;;

  while (1)
  {




	  if (!strcmp(can_rx_message.data, "mb_b_50")) {
		  memset(can_rx_message.data, 0, sizeof(can_rx_message.data));

		  // LEDs
		  GPIOC->ODR |= GPIO_ODR_6;
		  GPIOC->ODR &= ~GPIO_ODR_9;
		  idx=0;
		  while(idx < 102) {


			  // Motor


			  GPIOA->ODR |=  GPIO_ODR_7;
			  GPIOB->ODR &= ~GPIO_ODR_0;
			  GPIOB->ODR &= ~GPIO_ODR_1;
			  GPIOB->ODR &= ~GPIO_ODR_13;
			  delay_ms(35);
			  GPIOA->ODR &= ~GPIO_ODR_7;
			  GPIOB->ODR &= ~GPIO_ODR_0;
			  GPIOB->ODR &= ~GPIO_ODR_1;
			  GPIOB->ODR |=  GPIO_ODR_13;
			  delay_ms(35);
			  GPIOA->ODR &= ~GPIO_ODR_7;
			  GPIOB->ODR |=  GPIO_ODR_0;
			  GPIOB->ODR &= ~GPIO_ODR_1;
			  GPIOB->ODR &= ~GPIO_ODR_13;
			  delay_ms(35);
			  GPIOA->ODR &= ~GPIO_ODR_7;
			  GPIOB->ODR &= ~GPIO_ODR_0;
			  GPIOB->ODR |=  GPIO_ODR_1;
			  GPIOB->ODR &= ~GPIO_ODR_13;
			  delay_ms(35);
			  idx++;
		  }
		  GPIOB->ODR &= ~ GPIO_ODR_1;
		  Can_Tx_Msg(&brkon);



	  } else if (!strcmp(can_rx_message.data, "mb_b_00")) {
		  memset(can_rx_message.data, 0, sizeof(can_rx_message.data));
		  // LEDs
		  GPIOC->ODR |= GPIO_ODR_9;
		  GPIOC->ODR &= ~GPIO_ODR_6;
		  idx=0;
		  while(idx < 102) {
		  // Motor


			  GPIOA->ODR |=  GPIO_ODR_7;
			  GPIOB->ODR &= ~GPIO_ODR_0;
			  GPIOB->ODR &= ~GPIO_ODR_1;
			  GPIOB->ODR &= ~GPIO_ODR_13;
			  delay_ms(7);
			  GPIOA->ODR &= ~GPIO_ODR_7;
			  GPIOB->ODR &= ~GPIO_ODR_0;
			  GPIOB->ODR |=  GPIO_ODR_1;
			  GPIOB->ODR &= ~GPIO_ODR_13;
			  delay_ms(7);
			  GPIOA->ODR &= ~GPIO_ODR_7;
			  GPIOB->ODR |=  GPIO_ODR_0;
			  GPIOB->ODR &= ~GPIO_ODR_1;
			  GPIOB->ODR &= ~GPIO_ODR_13;
			  delay_ms(7);
			  GPIOA->ODR &= ~GPIO_ODR_7;
			  GPIOB->ODR &= ~GPIO_ODR_0;
			  GPIOB->ODR &= ~GPIO_ODR_1;
			  GPIOB->ODR |=  GPIO_ODR_13;
			  delay_ms(7);
			  idx++;
		  }
		  GPIOB->ODR &= ~GPIO_ODR_13;
		  Can_Tx_Msg(&brkoff);
	  }

  }

}

