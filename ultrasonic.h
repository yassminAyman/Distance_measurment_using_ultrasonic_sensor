/*
 * ultrasonic.h
 *
 *  Created on: Jul 5, 2023
 *      Author: yassmin
 */

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "std_types.h"
#include "general_gpio.h"


void Ultrasonic_init(void);
void Ultrasonic_Trigger(void);
uint16 Ultrasonic_readDistance(void);
void Ultrasonic_edgeProcessing(void);


#endif /* ULTRASONIC_H_ */
