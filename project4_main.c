/*
 * project3_main.c
 *
 *  Created on: Jun 22, 2023
 *      Author: yassmin
 */

#include "lcd.h"
#include "ultrasonic.h"
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	/*****************************variables:*****************************/
	uint16 distance=0;

	/*********************initialization functions:*********************/
	SREG |= (1<<7);
	LCD_init();
	Ultrasonic_init();
	distance=Ultrasonic_readDistance();

	LCD_displayString("Dist =");
	LCD_intgerToString(distance);
	moveCursor(0,14);
	LCD_displayString("cm");


	while(1)
	{

	}

}
