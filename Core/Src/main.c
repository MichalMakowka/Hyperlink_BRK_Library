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

	SystemCFG();	// Configure essential registers
	CanInit();


  while (1)
  {



  }

}

