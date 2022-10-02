/*
 * delay.cpp
 *
 *  Created on: Oct 1, 2022
 *      Author: Łukasz
 */

#include "tim.h"



void delay_us(uint16_t us)
{
	htim3.Instance->CNT = 0;
	while(htim3.Instance->CNT <= us);
}

