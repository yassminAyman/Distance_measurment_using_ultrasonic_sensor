/*
 * ex1_icu.c
 *
 *  Created on: Jun 26, 2023
 *      Author: yassmin
 */
#include <avr/io.h>
#include "icu.h"
#include <avr/interrupt.h>

/*pointer to function which store the address of the required function to be processed
 *to not to take alot of time at the ISR
 * -static as i dont need anyone to change it
 * -volatile for no optimization as it has null value at the beginning
 * */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;

ISR(TIMER1_CAPT_vect)
{
	if(g_callBackPtr != NULL_PTR)
		{
			/* Call the Call Back function in the application after the edge is detected */
			(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
		}
}

void ICU_init(const ICU_ConfigType * Config_Ptr)
{
	/*PD6 is input*/
	DDRD &= ~(1<<PD6);
	/*TCCR1A:
	 * bits 7->4:	clear for normal
	 * bits 3,2:	clear for non-pwm
	 * bits 1,0:	clear for normal mode
	 * */

	/*TCCR1B:
	 * bit 7:		set noise bs optional
	 * BIT 6:		dynamic config
	 * bit 5:		reserved
	 * bits 3,4:	clear for normal mode
	 * bits 2->0:	set CS10 for N=1
	 * */
	/*dynamic config for edge type:*/
	TCCR1B=(TCCR1B&0xBF)|((Config_Ptr->edge)<<6);

	/*dynamic config for edge type:*/
	TCCR1B=(TCCR1B&0xF8)|(Config_Ptr->clock);

	/*the start of counting*/
	TCNT1=0;

	ICR1 = 0;

	/*enable interrupt of the icu*/
	TIMSK|=1<<TICIE1;
}

/*the address of the fun that will be processed*/
void ICU_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr = a_ptr;
}

/*to change the edge during the program*/
void ICU_setEdgeDetectionType(const ICU_EdgeType a_edgeType)
{

	TCCR1B = (TCCR1B & 0xBF) | (a_edgeType<<6);
}

/*To get the required value(the time taken by the falling or rising edge):*/
uint16 ICU_getInputCaptureValue(void)
{
	return ICR1;
}


void ICU_clearTimerValue(void)
{
	TCNT1 = 0;
}

/*to restart the ICU*/
void ICU_deInit(void)
{
	/* Clear All Timer1/ICU Registers */
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	ICR1 = 0;

	/* Disable the Input Capture interrupt */
	TIMSK &= ~(1<<TICIE1);

	/* Reset the global pointer value */
	g_callBackPtr = NULL_PTR;
}
