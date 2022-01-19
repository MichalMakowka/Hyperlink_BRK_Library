/*
 * config.h
 *
 *  Created on: Oct 8, 2021
 *      Author: user
 */

#ifndef INC_CONFIG_H_
#define INC_CONFIG_H_

#include <stdio.h>
#include <string.h>
#include "stm32f303x8.h"

volatile uint16_t delay;
void delay_ms(uint16_t ms);






void SystemCFG (void);


#endif /* INC_CONFIG_H_ */
