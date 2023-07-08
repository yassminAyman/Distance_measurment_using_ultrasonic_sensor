/*
 * common_macros.h
 *
 *  Created on: Jun 15, 2023
 *      Author: yassmin
 */

#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_

#define SET_BIT(REG,BIT_NUM) (REG|=(1<<BIT_NUM))

#define CLEAR_BIT(REG,BIT_NUM) (REG&=~(1<<BIT_NUM))

#define TOGGLE_BIT(REG,BIT_NUM) (REG^=(1<<BIT_NUM))

#define SHIFT_RIGHT(REG,BIT_NUM) (REG=((REG>>BIT_NUM) | (REG<<(8-BIT_NUM)))

#define SHIFT_LEFT(REG,BIT_NUM) (REG=((REG<<BIT_NUM) | (REG>>(8-BIT_NUM)))

//check bit status and return true or false, if set
#define BIT_IS_SET(REG,BIT_NUM) (REG&(1<<BIT_NUM))
//if clear
#define BIT_IS_CLEAR(REG,BIT_NUM) (!(REG&(1<<BIT_NUM)))
//return the bit itself
#define GET_BIT(REG,BIT_NUM) ((REG&(1<<BIT_NUM)) >>BIT_NUM)

#endif /* COMMON_MACROS_H_ */
