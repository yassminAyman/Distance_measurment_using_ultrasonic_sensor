/*
 * general_gpio.h
 *
 *  Created on: Jun 15, 2023
 *      Author: yassmin
 */

#ifndef GENERAL_GPIO_H_
#define GENERAL_GPIO_H_

#include "std_types.h"

#define NUM_OF_PORTS		4
#define NUM_OF_PINS			8

#define PORTA_ID			0
#define PORTB_ID			1
#define PORTC_ID			2
#define PORTD_ID			3

#define PIN0_ID                0
#define PIN1_ID                1
#define PIN2_ID                2
#define PIN3_ID                3
#define PIN4_ID                4
#define PIN5_ID                5
#define PIN6_ID                6
#define PIN7_ID                7

typedef enum {
	Pin_INPUT,Pin_OUTPUT
}GPIO_Pin_Direction;

typedef enum {
	PORT_INPUT,PORT_OUTPUT=0xFF
}GPIO_PORT_Direction;

/*****************************Prototypes of functions******************************/
void GPIO_setupPinDirection(uint8 port_num,uint8 pin_num,GPIO_Pin_Direction direction);

void GPIO_writePin(uint8 port_num,uint8 pin_num,uint8 value);

uint8 GPIO_readPin(uint8 port_num,uint8 pin_num);

void GPIO_setupPortDirection(uint8 port_num, GPIO_PORT_Direction direction);

void GPIO_writePort(uint8 port_num, uint8 value);

uint8 GPIO_readPort(uint8 port_num);

#endif /* GENERAL_GPIO_H_ */
