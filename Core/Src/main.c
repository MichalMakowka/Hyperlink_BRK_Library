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
		strcpy(brkon.data, "br_0000");
		brkon.format = STANDARD_FORMAT;
		brkon.id = 0x03;
		brkon.len = sizeof(brkon.data);
		brkon.type = DATA_FRAME;

	CAN_MESSAGE brkoff;
		strcpy(brkoff.data, "br_0001");
		brkoff.format = STANDARD_FORMAT;
		brkoff.id = 0x04;
		brkoff.len = sizeof(brkoff.data);
		brkoff.type = DATA_FRAME;


	SystemCFG();	// Configure essential registers
	CanInit();

	Can_Set_Filter(0x01, STANDARD_FORMAT);
	Can_Set_Filter(0x02, STANDARD_FORMAT);

	Can_Tx_Msg(&brkon);

  while (1)
  {


	  if (!strcmp(can_rx_message.data, "mb_0000")) {
		  GPIOC->ODR |= GPIO_ODR_6;
//		  Can_Tx_Msg(&brkon);
	  } else if (!strcmp(can_rx_message.data, "mb_0001")) {
		  GPIOC->ODR &= ~GPIO_ODR_6;
//		  Can_Tx_Msg(&brkoff);
	  }

  }

}

