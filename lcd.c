/*
 * lcd_.c
 *
 *  Created on: Jun 17, 2023
 *      Author: yassmin
 */

#include <util/delay.h>
#include "common_macros.h"
#include "general_gpio.h"
#include "lcd.h"


void LCD_init(void)
{
	/*directions*/
	GPIO_setupPinDirection(LCD_RS_PORT_ID,LCD_RS_PIN_ID,Pin_OUTPUT);
	GPIO_setupPinDirection(LCD_E_PORT_ID,LCD_E_PIN_ID,Pin_OUTPUT);
	/*wait:*/
	_delay_ms(20);
#if (LCD_DATA_BITS_MODE==8)
	GPIO_setupPortDirection(LCD_DATA_PORT_ID,PORT_OUTPUT);

	LCD_sendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE);
#elif (LCD_DATA_BITS_MODE==4)
	GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID, Pin_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_DB5_PIN_ID, Pin_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_DB6_PIN_ID, Pin_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_DB7_PIN_ID, Pin_OUTPUT);

	/*start sending initialitzation commands:*/
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT1);
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT2);
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE);
#endif


	LCD_sendCommand(LCD_CURSOR_OFF);

	/*clear:*/
	LCD_sendCommand(LCD_CLEAR_COMMAND);
}

void LCD_sendCommand(uint8 command)
{
	GPIO_writePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOGIC_LOW);
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);
	_delay_ms(1);
#if (LCD_DATA_BITS_MODE==8)

	GPIO_writePort(LCD_DATA_PORT_ID, command);


#elif (LCD_DATA_BITS_MODE==4)
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(command,4));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(command,5));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(command,6));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(command,7));

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */

	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(command,0));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(command,1));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(command,2));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(command,3));
#endif
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
	_delay_ms(1);
}

void LCD_displayCharacter(uint8 data)
{
	GPIO_writePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOGIC_HIGH);
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH);
	_delay_ms(1);
#if (LCD_DATA_BITS_MODE==8)
	GPIO_writePort(LCD_DATA_PORT_ID,data);
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);
	_delay_ms(1);
#elif (LCD_DATA_BITS_MODE==4)
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(data,4));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(data,5));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(data,6));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(data,7));
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH);
	_delay_ms(1);
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(data,0));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(data,1));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(data,2));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(data,3));
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);
#endif

}

void LCD_displayString(const char *Str)
{
	uint8 i=0;
	while(Str[i] != '\0'){
		LCD_displayCharacter(Str[i]);
		i++;
	}
}

void moveCursor(uint8 row,uint8 col)
{
	uint8 address;
	switch(row)
	{
	case 0:
		address=col;
		break;
	case 1:
		address=col+(0x40);
		break;
	case 2 :
		address=col+(0x10);
		break;
	case 3 :
		address=col+(0x50);
		break;
	}
	LCD_sendCommand(address | LCD_SET_CURSOR_LOCATION);
}

void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str)
{
	moveCursor(row,col);
	LCD_displayString(Str);
}

void LCD_intgerToString(int data)
{
	char buff[16];
	itoa(data,buff,10);
	LCD_displayString(buff);
}

void LCD_clearScreen(void)
{
	LCD_sendCommand(LCD_CLEAR_COMMAND);
}
