/*
 * ultrasonic.c

 *  Created on: Jul 5, 2023
 *      Author: yassmin
 */

#include "ultrasonic.h"
#include "icu.h"
#include <util/delay.h>

uint8 g_edgeCount = 0;
uint16 g_time=0;

/*void Ultrasonic_edgeProcessing(void):
 * Description
 * This is the call back function called by the ICU driver.
 * This is used to calculate the high time (pulse time) generated by the ultrasonic sensor.
 * Inputs: None
 * Return: None*/
void Ultrasonic_edgeProcessing(void)
{
	g_edgeCount++;
		if(g_edgeCount==1)
		{
			ICU_clearTimerValue();
			ICU_setEdgeDetectionType(FALLING);
		}
		else if(g_edgeCount==2)
		{
			g_time =ICU_getInputCaptureValue();
			ICU_deInit(); /* Disable ICU Driver */
		}
}

/*void Ultrasonic_init(void):
 * Description:
 * Initialize the ICU driver as required.
 * Setup the ICU call back function.
 * Setup the direction for the trigger pin as output pin through the GPIO driver.
 * Inputs: None
 * Return: None*/
void Ultrasonic_init(void)
{
	/*determine the data of the struct of configration edge and clock*/
		ICU_ConfigType ICU_Configurations={F_CPU_8,RISING};

		ICU_init(&ICU_Configurations);

		ICU_setCallBack(Ultrasonic_edgeProcessing);

		GPIO_setupPinDirection(PORTB_ID, PIN5_ID,Pin_OUTPUT);
}


/*void Ultrasonic_Trigger(void):
 *  Description:
 *  Send the Trigger pulse to the ultrasonic.
 *  Inputs: None
 *  Return: None
 *  */
void Ultrasonic_Trigger(void)
{
	GPIO_writePin(PORTB_ID,PIN5_ID,LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(PORTB_ID,PIN5_ID,LOGIC_LOW);
}

/*uint16 Ultrasonic_readDistance(void):
 * Description:
 * Send the trigger pulse by using Ultrasonic_Trigger function.
 * Start the measurements by the ICU from this moment.
 * Inputs: None
 * Return: The measured distance in Centimeter.
 * */
uint16 Ultrasonic_readDistance(void)
{
	uint16 g_distance=0;
	Ultrasonic_Trigger();
	while(g_edgeCount!=2){};
	g_distance =(float)(g_time/58.8);
	g_edgeCount = 0;
	return g_distance;
}



