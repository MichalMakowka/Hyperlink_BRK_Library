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
#include <stdlib.h>
#include "config.h"
#include "can.h"





int main(void)
{

	CAN_MESSAGE can_status_ok;
		strcpy(can_status_ok.data, "br_0000");
		can_status_ok.format = STANDARD_FORMAT;
		can_status_ok.id = 0x01;
		can_status_ok.len = sizeof(can_status_ok.data);
		can_status_ok.type = DATA_FRAME;

	CAN_MESSAGE can_status_fault;
		strcpy(can_status_fault.data, "br_1111");
		can_status_fault.format = STANDARD_FORMAT;
		can_status_fault.id = 0x01;
		can_status_fault.len = sizeof(can_status_fault.data);
		can_status_fault.type = DATA_FRAME;

	CAN_MESSAGE can_ack;
		strcpy(can_ack.data, "br_b_xx");
		can_ack.format = STANDARD_FORMAT;
		can_ack.id = 0x01;
		can_ack.len = sizeof(can_ack.data);
		can_ack.type = DATA_FRAME;


	SystemCFG();	// Configure essential registers
	CanInit();

	Can_Set_Filter(0x00, STANDARD_FORMAT);
	Can_Set_Filter(0x02, STANDARD_FORMAT);



	int idx = 0;
	char brk_val_tab[2];
	uint8_t brk_val;	// 7 to 35

  while (1)
  {




	  if (!strncmp(can_rx_message.data, "mb_b_xx", 5)) {
		  brk_val_tab[0] = can_rx_message.data[5];
		  brk_val_tab[1] = can_rx_message.data[6];
		  brk_val = atoi(brk_val_tab);
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
			  delay_ms(brk_val);
			  GPIOA->ODR &= ~GPIO_ODR_7;
			  GPIOB->ODR &= ~GPIO_ODR_0;
			  GPIOB->ODR &= ~GPIO_ODR_1;
			  GPIOB->ODR |=  GPIO_ODR_13;
			  delay_ms(brk_val);
			  GPIOA->ODR &= ~GPIO_ODR_7;
			  GPIOB->ODR |=  GPIO_ODR_0;
			  GPIOB->ODR &= ~GPIO_ODR_1;
			  GPIOB->ODR &= ~GPIO_ODR_13;
			  delay_ms(brk_val);
			  GPIOA->ODR &= ~GPIO_ODR_7;
			  GPIOB->ODR &= ~GPIO_ODR_0;
			  GPIOB->ODR |=  GPIO_ODR_1;
			  GPIOB->ODR &= ~GPIO_ODR_13;
			  delay_ms(brk_val);
			  idx++;
		  }
		  GPIOB->ODR &= ~ GPIO_ODR_1;
		  Can_Tx_Msg(&can_ack);

	  }

	  else if (!strcmp(can_rx_message.data, "mb_1010")) {
		  memset(can_rx_message.data, 0, sizeof(can_rx_message.data));
		  delay_ms(100);
		  // Perform status check here
		  Can_Tx_Msg(&can_status_ok);

	  }
/*
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
*/
  }

}

