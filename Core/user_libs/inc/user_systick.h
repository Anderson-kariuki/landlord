/*
 * user_systick.h
 *
 *  Created on: Oct 25, 2018
 *      Author: ZBook
 */

#ifndef INC_USER_SYSTICK_H_
#define INC_USER_SYSTICK_H_


#include "user_systick.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "stm32f1xx_hal.h"

void delay(uint32_t delay_ms);
void user_systic_handler();


extern __IO uint32_t ms_tick;
extern __IO uint32_t lcd_led_ticks;
extern __IO uint32_t button_press_ticks;
extern __IO uint32_t button_handler_ticks;


#endif /* INC_USER_SYSTICK_H_ */
